#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

#include <sys/wait.h>

#include"../inc/server.h"
#include"../inc/error_exit.h"
#include"../inc/shared_memory.h"
#include"../inc/semaphore.h"
#include"../inc/message_queue.h"
#include"../inc/forza4.h"


struct player_struct player[2];
time_t timeLastSIGINT = 0;

void sigHandlerClose(int signum) {
	if(!(signum == SIGINT || signum == SIGHUP)) {
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
	player[1].symbol = argv[4][0];

	if (signal(SIGINT, sigHandlerClose) == SIG_ERR) {
		errExit("signal(SIGINT, sigHandlerCloseServer)");
	}

	if (signal(SIGHUP, sigHandlerClose) == SIG_ERR) {
		errExit("signal(SIGHUP, sigHandlerCloseServer)");
	}

	connectToMessageQueue();
	genereteServerSharedMemory(hight, whith);
	genereteSemaphore(2);

	// Semaphore
	u_int16_t arr[2] = {0, 0};
	setSemaphoreArray(arr);

	// forza4 lib
	passVariableToF4Lib(shm_pointer, hight, whith, player[0].symbol, player[1].symbol);
	generateGameField();	
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
	requestJoinToMatch_t buffer_request;
	
	
	printf("[DEBUG] In attesa dei due utenti...\n");

	for(u_int8_t i=0; i<2; i++) {
		
		reciveMsg(1, &buffer_request, sizeof(buffer_request));
		player[i].pid = buffer_request.pidClient;
		strcpy(player[i].username, buffer_request.userName);
		printf("[DEBUG] New request to join { pid: %d, username: \"%s\" }\n", player[i].pid, player[i].username);	
		
		respodeToRequest_t buf_request_responde;
		buf_request_responde.pidClient = buffer_request.pidClient;
		buf_request_responde.mtype = 2 + buffer_request.pidClient;
		buf_request_responde.nrClient = i;
		buf_request_responde.approved = 1;
		buf_request_responde.sharedMemoryId = shmid;
		buf_request_responde.semaphoreId = semid;
		buf_request_responde.field_hight = field_hight;
		buf_request_responde.field_width = field_width;
		buf_request_responde.symbols[0] = player[0].symbol;
		buf_request_responde.symbols[1] = player[1].symbol;
		sendMsg(&buf_request_responde, sizeof(buf_request_responde));
	}
}

void game() {
	startGame_t buf;	

	puts("[DEBUG] Start game");

	strcpy(buf.usernames[0], player[0].username);
	strcpy(buf.usernames[1], player[1].username);
	
	for(int i=0; i<2; i++) {
		buf.mtype = 3;
		sendMsg(&buf, sizeof(buf));
	}

	semaphoreOperation(0, 1);


	puts("[DEBUG] Send messages to start game");
	


	while(1);	
}
