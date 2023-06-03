#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include "../inc/error_exit.h"
#include "../inc/shared_memory.h"

int shmid;
char* shm_pointer;

void genereteServerSharedMemory(unsigned short fieldHight, unsigned short fieldWidth) {
	printf("[DEBUG] Inizializzo la crezione della memoria condivisa... ");

	key_t key_shm = ftok("LICENSE", 's');
	if(key_shm == (key_t)-1) {
		errExit("ftok() failed");
	}

	int shmid_temp = shmget(key_shm, sizeof(char) * fieldHight * fieldWidth, IPC_CREAT | S_IRUSR | S_IWUSR);
	if(shmid_temp == -1) {
		errExit("shmget() failed");
	}
	
	shmid = shmid_temp;

	// Usa direttamente la varibile dichiarata nel .h
	shm_pointer = attachSharedMemory(shmid);
	for(int i=0; i<fieldHight*fieldWidth; i++) {
		shm_pointer[i] = '\0';
	}

	printf("Fatto\n");
}

void removeServerSharedMemory() {
	printf("[DEBUG] Rimozione memoria condivisa... ");

	if (shmdt(shm_pointer) == -1)
		errExit("shmdt failed");

	printf("Fatto\n");
}


char* attachSharedMemory(int _shmid) {
	char* pointerToMemory;
	
	pointerToMemory = shmat(_shmid, NULL, 0);
	if(pointerToMemory == (void*)(-1)) {
		errExit("shmget() failed");
	}

	return pointerToMemory;
}	