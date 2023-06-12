#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/stat.h>

#include"../inc/message_queue.h"
#include"../inc/error_exit.h"

int msqid = 0;


void connectToMessageQueue() {
	printf("[DEBUG] Inizializzo la connessione o la creazione della message queue... ");

	if(msqid != 0) {
		return;
	}

	key_t key = ftok("LICENSE", 'q');
	if(key == -1) {
		errExit("msq: ftok()");
	}

	int msqid_tmp = msgget(key, IPC_CREAT | S_IRUSR | S_IWUSR);
	if(msqid_tmp == -1) {
		errExit("msq: msgget()");
	}

	if(msqid_tmp == 0) {
		errExit("msq: msgget() == 0");
	}

	msqid = msqid_tmp;
	printf("ID: %d  Fatto\n",msqid);
}

void disconectFromMessageQueue() {
	printf("[DEBUG] Rimozione message queue... ");

	if(msqid == 0) {
		return;
	}

	if(msgctl(msqid, IPC_RMID, NULL) == -1) {
		errExit("msq: msgctl(IPC_REMOVE)");
	}

	msqid = 0;

	printf("Fatto\n");
}

void sendMsg(void* buf, size_t size) {
	if(msqid == 0) {
		errExit("sendMsg msqid undefined");
	}

	size = size - sizeof(long);
	while(msgsnd(msqid, buf, size, IPC_NOWAIT) == -1) {}
}

void reciveMsg(long mType, void* buf, size_t size) {
	if(msqid == 0) {
		errExit("reciveMsg msqid undefined");
	}

	size = size - sizeof(long);
	while(msgrcv(msqid, buf, size, mType, IPC_NOWAIT) == -1) {}
}