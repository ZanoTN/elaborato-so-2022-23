#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<signal.h>

#include <sys/wait.h>

#include"../inc/server.h"
#include"../inc/error_exit.h"
#include"../inc/shared_memory.h"
#include"../inc/semaphore.h"
#include"../inc/message_queue.h"
#include"../inc/forza4.h"


struct player_struct player[2];
time_t timeLastSIGINT = 0;

void sigHandlerInt(int signum) {
	if(signum != SIGINT) {
		return;
	}

	time_t now = time(NULL);

	if(now - timeLastSIGINT <= 5) { // Esco dal programma
		printf("\033[0;31m[DEBUG] Avvio chiusura! [SIGINT]\033[0m\n");
		closeServer();
		exit(0);
	} else {
		timeLastSIGINT = now;
	}
}

void initServer(char *argv[]) {
	int hight = atoi(argv[1]);
	int whith = atoi(argv[2]);

	player[0].symbol = argv[3][0];
	player[1].symbol = argv[3][0];

	if (signal(SIGINT, sigHandlerInt) == SIG_ERR) {
		errExit("signal(SIGINT, sigHandlerInt)");
	}

	connectToMessageQueue();
	genereteServerSharedMemory(hight, whith);
	genereteSemaphore(3);

	// forza4 lib
	passVariableToF4Lib(shm_pointer, hight, whith);
	generateGameField();
	// printGameFieldFormatted(char_player_1, char_player_2);
	// printGameFieldRaw();

}

void closeServer() {
	printf("[DEBUG] Terminazione dei client... ");
	if(player[0].pid > 0) {
		kill(player[0].pid, SIGTERM);
	}
	if(player[1].pid > 0) {
		kill(player[1].pid, SIGTERM);
	}

	if(player[0].pid > 0) {
		while(waitpid(player[0].pid, 0, 0) == 0);
	}
	if(player[1].pid > 0) {
		while(waitpid(player[1].pid, 0, 0) == 0);
	}
	printf("Fatto\n");

	disconectFromMessageQueue();
	removeServerSharedMemory();
	removeSetSemaphore();
}


void getUser() {
	printf("[DEBUG] In attesa dei due utenti...\n");

	for(u_int8_t i=0; i<2; i++) {
		
		requestJoinToMatch_t buffer;
		reciveMsg(1, &buffer);
		
		player[i].pid = buffer.pidClient;
		strcpy(player[i].username, buffer.userName);
		printf("[DEBUG] New request to join { pid: %d, username: \"%s\" }\n", player[i].pid, player[i].username);
		
		
		respodeToRequest_t buffer2;
		buffer2.mtype = 2;
		buffer2.nrClient = i;
		buffer2.approved = 1;
		buffer2.sharedMemoryId = shmid;
		sendMsg(buffer2.mtype, &buffer2);
	}
}

void game() {
	puts("[DEBUG] play game");

	// Unclok sempaphore
}
