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
	printf("[DEBUG] Send request to join");
	requestJoinToMatch_t buf;
	
	buf.mtype = 1;
	buf.pidClient = getpid();
	strcpy(buf.userName, username);
	sendMsg(buf.mtype, &buf);
	
	respodeToRequest_t buf2;
	reciveMsg(2, &buf2);
	printf("[DEBUG] Recice responde { approved: %d, nrClient: %d }\n",buf2.approved, buf2.nrClient);

	if(buf2.approved == 1) {
		shmid = buf2.sharedMemoryId;
		shm_pointer = attachSharedMemory(shmid);
	}
}

void playGame() {
	while(1==1) {}
}

void closeClient() {
	// disconectFromMessageQueue(); only server can remove it

	if(shmid != 0) {
		detachSharedMemory();
	}
}