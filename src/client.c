#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

#include"../inc/client.h"
#include"../inc/error_exit.h"
#include"../inc/message_queue.h"
#include"../inc/shared_memory.h"
#include"../inc/semaphore.h"
#include"../inc/forza4.h"

time_t timeLastSIGINT = 0;
int8_t client_id = -1;


void sigHandlerInt(int signum) {
	if(signum != SIGINT) {
		return;
	}

	time_t now = time(NULL);

	if(now - timeLastSIGINT <= 5) { // Esco dal programma
		printf("\033[0;31m[DEBUG] Avvio chiusura! [SIGINT]\033[0m\n");
		closeClient();
		// TODO: Send signale to server
		exit(0);
	} else {
		timeLastSIGINT = now;
	}
}

void sigHandlerTerm(int signum) {
	if(signum != SIGTERM) {
		return;
	}

	printf("\033[0;31m[DEBUG] Avvio chiusura! [SIGTERM]\033[0m\n");
	closeClient();
	exit(0);
}

void initClient() {
	system("clear");

	if (signal(SIGINT, sigHandlerInt) == SIG_ERR) {
		errExit("signal(SIGINT, sigHandlerInt)");
	}

	if (signal(SIGTERM, sigHandlerTerm) == SIG_ERR) {
		errExit("signal(SIGTERM, sigHandlerTerm)");
	}

	connectToMessageQueue();

}

void requestJoin(char username[50]) {
	printf("[DEBUG] Send request to join\n");
	requestJoinToMatch_t buf;
	
	buf.mtype = 1;
	buf.pidClient = getpid();
	strcpy(buf.userName, username);
	sendMsg(buf.mtype, &buf);
	
	respodeToRequest_t buf2;
	reciveMsg(2, &buf2);
	printf("[DEBUG] Recice responde { approved: %d, nrClient: %d }\n",buf2.approved, buf2.nrClient);

	if(buf2.approved == 1 && buf2.pidClient == getpid()) {
		client_id = buf2.nrClient;
		semid = buf2.semaphoreId;
		shmid = buf2.sharedMemoryId;
		shm_pointer = attachSharedMemory(shmid);
		passVariableToF4Lib(shm_pointer, buf2.field_hight, buf2.field_width, buf2.symbols[0], buf2.symbols[1]);
	}
}

void game() {
	int end_game = 0;
	char enemy_username[50];
	puts("[DEGUB] In attesa inizio partita");

	semaphoreOperation(client_id, -1);
	startGame_t buf;
	reciveMsg(10, &buf);
	printf("[DEBUG] game start: %s\n", buf.enemy_username);
	strcpy(enemy_username, buf.enemy_username);
	printf("- %s --", buf.enemy_username);
	semaphoreOperation((client_id == 0) ? 1 : 0, 1);

	char number[10];
	int8_t number_int;

	while(!end_game) {
		semaphoreOperation(client_id, -1);	

		do{
			system("clear");
			printGameFieldFormatted();
			printf("E' il tuo turno!\nInserisci colonna: ");
			fgets(number, 10, stdin);

			number_int = atoi(number);
		} while (addCoin(client_id, number_int));

		system("clear");
		printGameFieldFormatted();
		printf("E' il turno di %s\n", enemy_username);
		semaphoreOperation((client_id == 0) ? 1 : 0, 1);
	}
}

void closeClient() {
	// disconectFromMessageQueue(); only server can remove it

	if(shmid != 0) {
		detachSharedMemory();
	}
}