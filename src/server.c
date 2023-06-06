#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<signal.h>

#include"../inc/server.h"
#include"../inc/error_exit.h"
#include"../inc/shared_memory.h"
#include"../inc/semaphore.h"
#include"../inc/message_queue.h"
#include"../inc/forza4.h"

struct player_struct player[2];
time_t timeLastSIGINT = 0;

void sigHandlerInt(int signum) {
	time_t now = time(NULL);

	if(now - timeLastSIGINT <= 5) { // Esco dal programma
		printf("\033[0;31m[DEBUG] Avvio chiusura forzata!\033[0m\n");
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

	// TODO: kill and wait for all client terminate

	disconectFromMessageQueue();
	removeServerSharedMemory();
	removeSetSemaphore();
}


void getUser() {
	printf("[DEBUG] In attesa dei due utenti...\n");

	for(u_int8_t i=0; i<2; i++) {
		
		struct RequestJoinToMatch buffer;
		reciveMsg(1, &buffer);
		
		player[i].pid = buffer.pidClient;
		strcpy(player[i].username, buffer.userName);

		printf("[DEBUG] New request to join { pid: %d, username: \"%s\" }\n", player[i].pid, player[i].username);
		buffer.mtype = 1;
		buffer.nrClient = i;
		buffer.approved = 1;
		buffer.sharedMemoryId = shmid;
		sendMsg(buffer.mtype, &buffer);
	}
}
