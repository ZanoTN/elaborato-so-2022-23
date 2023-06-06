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

void initClient(char *argv[]) {
	if (signal(SIGINT, sigHandlerInt) == SIG_ERR) {
		errExit("signal(SIGINT, sigHandlerInt)");
	}

	connectToMessageQueue();

}

void sendRequestJoin(char username[50]) {
	printf("[DEBUG] Send request to join");
	RequestJoinToMatch_t buf;
	
	buf.mtype = 1;
	buf.pidClient = getgid();
	strcpy(buf.userName, username);
	sendMsg(buf.mtype, &buf);
}

void closeClient() {
	// detachSharedMemory();
}