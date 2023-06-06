#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

#include"../inc/client.h"
#include"../inc/error_exit.h"
#include"../inc/message_queue.h"
#include"../inc/shared_memory.h"

time_t timeLastSIGINT = 0;

void sigHandlerInt(int signum) {
	if(signum != SIGINT) {
		return;
	}

	time_t now = time(NULL);

	if(now - timeLastSIGINT <= 5) { // Esco dal programma
		printf("\033[0;31m[DEBUG] Avvio chiusura forzata!\033[0m\n");
		closeClient();
		// TODO: Send signale to server
		exit(0);
	} else {
		timeLastSIGINT = now;
	}
}

void initClient() {
	system("clear");

	if (signal(SIGINT, sigHandlerInt) == SIG_ERR) {
		errExit("signal(SIGINT, sigHandlerInt)");
	}

	connectToMessageQueue();

}

void requestJoin(char username[50]) {
	printf("[DEBUG] Send request to join");
	requestJoinToMatch_t buf;
	
	buf.mtype = 1;
	buf.pidClient = getpid();
	strcpy(buf.userName, username);
	sendMsg(buf.mtype, &buf);
	
	respodeToRequest_t buf2;
	reciveMsg(2, &buf2);
	if(buf2.approved == 1) {
		attachSharedMemory(buf2.sharedMemoryId);
		printf("[DEBUG] Recice responde { nrClient: %d }\n", buf2.nrClient);
	}

}

void closeClient() {
	// detachSharedMemory();
}