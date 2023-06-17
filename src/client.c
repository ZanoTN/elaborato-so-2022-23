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


global_var_t global_var_data;

time_t timeLastSIGINT = 0;

// TO Remove
pid_t pidServer = 0;
int8_t client_id = -1;


void sigHandlerClose(int signum) {
	if(!(signum == SIGINT || signum == SIGHUP)) {
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

void sigHandlerStatusCode(int signum) {
	printf("here");
	if(signum != SIGUSR2) {
		return;
	}

	// status_t buf;
	//reciveMsg(100, &buf, sizeof(buf));
	//printf("[DEBUG] Recive status code: %d from pid: %d", buf.statusCode, buf.pidClient);

}

void initClient() {
	system("clear");

	if (signal(SIGINT, sigHandlerClose) == SIG_ERR) {
		errExit("signal(SIGINT, sigHandlerClose)");
	}
	if (signal(SIGHUP, sigHandlerClose) == SIG_ERR) {
		errExit("signal(SIGHUP, sigHandlerCloseServer)");
	}

	if (signal(SIGTERM, sigHandlerTerm) == SIG_ERR) {
		errExit("signal(SIGTERM, sigHandlerTerm)");
	}

	if (signal(SIGUSR2, sigHandlerStatusCode) == SIG_ERR) {
		errExit("signal(SIGUSR2, sigHandlerStatusCode)");
	}

	connectToMessageQueue();

}

void requestJoin(char username[50]) {
	printf("[DEBUG] Send request to join\n");
	requestJoinToMatch_t buf;
	
	buf.mtype = 1;
	buf.pidClient = getpid();
	strcpy(buf.userName, username);
	sendMsg(&buf, sizeof(buf));
	
	respodeToRequest_t buf2;
	reciveMsg(200000 + getpid(), &buf2, sizeof(buf2));
	printf("[DEBUG] Recice responde { approved: %d, nrClient: %d }\n",buf2.approved, buf2.nrClient);

	if(buf2.approved == 1) {
		client_id = buf2.nrClient;
		global_var_data.pid_server = buf2.pidServer;
		semid = buf2.semaphoreId;
		shmid = buf2.sharedMemoryId;
		shm_pointer = attachSharedMemory(shmid);
		passVariableToF4Lib(
			shm_pointer, buf2.field_hight,
			buf2.field_width, buf2.symbols[0],
			buf2.symbols[1]
		);
	}
}

void game() {
	int end_game = 0;
	int end_turn = 0;
	int retAddCoin, retCheckWin;
	char enemy_username[50];
	char number[10];
	int8_t number_int;

	puts("[DEGUB] In attesa inizio partita");

	semaphoreOperation(client_id, -1);
	
	startGame_t buf;	
	reciveMsg(3, &buf, sizeof(buf));
	strcpy(enemy_username, buf.usernames[((client_id == 0) ? 1 : 0)]);

	semaphoreOperation((client_id == 0) ? 1 : 0, 1);

	if(client_id == 1) {
		printGame();
		printf("E' il turno di %s\n", enemy_username);
	}

	while(!end_game) {
		semaphoreOperation(client_id, -1);
		end_turn = 0;

		printGame();
		printf("E' il tuo turno!\nInserisci colonna: ");

		do{
			fgets(number, 10, stdin);
			number_int = atoi(number);

			retAddCoin = addCoin(client_id, number_int);
			switch(retAddCoin) {
			case -1:
				printf("Colonna piena, ritenta: ");
				break;
			case -2:
				printf("Colonna invalida, ritenta: ");
				break;
			default:
				end_turn = 1;
				break;
			}
		} while (!end_turn);

		printGame();

		retCheckWin = checkWin(retAddCoin, number_int);
		if(retCheckWin == 1 || retCheckWin == -1) {

			if(retCheckWin == 1) {
				printf("Vittoria!\n");
			} else if(retCheckWin == -1) {
				printf("parità!\n");
			}

			sendStatus(retCheckWin);

		}else{
			printf("E' il turno di %s\n", enemy_username);
		}

		semaphoreOperation((client_id == 0) ? 1 : 0, 1);
	}
}

void closeClient() {
	// disconectFromMessageQueue(); only server can remove it

	if(shmid != 0) {
		detachSharedMemory();
	}
}

void printGame() {
	system("clear");
	printGameFieldFormatted();
}

void sendStatus(int statusCode) {
	status_t buf_status;
	
	buf_status.mtype = 100;
	buf_status.pidClient = getpid();
	buf_status.statusCode = statusCode;

	kill(global_var_data.pid_server, SIGUSR2);
	sendMsg(&buf_status, sizeof(buf_status));
	
	kill(global_var_data.pid_other_client, SIGUSR2);
	sendMsg(&buf_status, sizeof(buf_status));
}