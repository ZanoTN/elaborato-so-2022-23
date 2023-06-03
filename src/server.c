#include <stdio.h>
#include<string.h>

#include"../inc/server.h"
#include"../inc/shared_memory.h"
#include"../inc/semaphore.h"
#include"../inc/fifo.h"
#include"../inc/message_queue.h"

struct player_struct player[2];

void intiMessageQueue() {
	connectToMessageQueue();
}

void initSharedMemory(unsigned short hight, unsigned short whith) {
	// Solo per server
	genereteServerSharedMemory(hight, whith);
}

void intiSemaphore() {
	genereteSemaphore(3);
}

void delMessageQueue() {
	disconectFromMessageQueue();
}

void delSharedMemory() {
	removeServerSharedMemory();
}

void delSemaphore() {
	removeSetSemaphore();
}

void getUser() {
	printf("[DEBUG] In attesa dei due utenti...\n");
	printf("[DEBUG] shmid: %d\n", shmid);

	for(unsigned short i=0; i<2; i++) {
		
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
