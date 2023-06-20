#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<sys/stat.h>
#include<sys/types.h>

#include "../inc/error_exit.h"
#include "../inc/shared_memory.h"

int shmid;
int8_t* shm_pointer;

void genereteServerSharedMemory(u_int16_t fieldHight, u_int16_t fieldWidth) {
	printf("[DEBUG] Inizializzo la crezione della memoria condivisa... ");

	key_t key_shm = ftok("LICENSE", 's');
	if(key_shm == (key_t)-1) {
		errExit("ftok() failed");
	}

	int shmid_temp = shmget(key_shm, sizeof(__int8_t) * fieldHight * fieldWidth, IPC_CREAT | S_IRUSR | S_IWUSR);
	if(shmid_temp == -1) {
		errExit("shmget() failed");
	}
	
	shmid = shmid_temp;

	// Usa direttamente la varibile dichiarata nel .h
	shm_pointer = attachSharedMemory(shmid);
	
	/* for(int i=0; i<fieldHight*fieldWidth; i++) {
		shm_pointer[i] = '\0';
	} */

	printf("Fatto\n");
}

void detachSharedMemory() {
	printf("[DEBUG] Disconnesine dalla memoria condivisa... ");
	
	if(shmdt(shm_pointer) == -1)
		errExit("shmdt failed");

	printf("Fatto\n");
}

void removeServerSharedMemory() {
	
	detachSharedMemory();

	printf("[DEBUG] Rimozione memoria condivisa... ");

	if(shmctl(shmid, IPC_RMID, NULL) == -1)
		errExit("shmctl(IPC_RMID):");

	printf("Fatto\n");
}


int8_t* attachSharedMemory(int _shmid) {
	int8_t* pointerToMemory;
	
	pointerToMemory = shmat(_shmid, NULL, 0);
	if(pointerToMemory == (int8_t*)(-1)) {
		errExit("shmget() failed");
	}

	return pointerToMemory;
}	