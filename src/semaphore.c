#include<stdio.h>
#include<sys/sem.h>
#include<sys/stat.h>

#include"../inc/semaphore.h"
#include"../inc/error_exit.h"

int semid;

void genereteSemaphore(int number_semaphore) {
	printf("[DEBUG] Inizializzo la creazione dei semafori... ");

	if(semid != 0) {
		return;
	}

	key_t key_sem = ftok("LICENSE", 'r');
	if(key_sem == (key_t)-1) {
		errExit("ftok()");
	}

	int semid_tmp = semget(key_sem, number_semaphore, IPC_CREAT | S_IRUSR | S_IWUSR);
	if(semid_tmp == -1) {
		errExit("semget() failed");
	}

	semid = semid_tmp;
	printf("Fatto\n");
}

void removeSetSemaphore() {
	printf("[DEBUG] Rimozione set semafori... ");

	if(semctl(semid, 0/*ignored*/, IPC_RMID, 0/*ignored*/) == -1) {
		errExit("semctl failed");
	}

	semid = 0;

	printf("Fatto\n");
}

void setSemaphoreArray(u_int16_t semArray[]) {
	union semnum {
		int val;
		struct semid_ds *buf;
		u_int16_t *array;
	} arg;

	arg.array = semArray;

	if(semctl(semid, 0 /*ignored*/, SETALL, arg) == -1) {
		errExit("semctl() failded");
	}
}

void semaphoreOperation(unsigned short sem_num, short sem_op) {
	struct sembuf sop = {.sem_num = sem_num, .sem_op = sem_op, .sem_flg = IPC_NOWAIT};
	
	while(semop(semid, &sop, 1) == -1);
}

int semGetVal(int semNumb) {
	int val = semctl(semid, semNumb, GETVAL, 0);
	if (val == -1) {
		errExit("semctl GETVAL");
	}

	return val;
}