#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include<sys/shm.h>
#include<sys/stat.h>

#include"../inc/F4Server.h"
#include"../inc/server.h"
#include"../inc/error_exit.h"
#include"../inc/printlog.h"


int main(int argc, char *argv[]) {

	if(checkArguments(argc, argv) == -1) {
		printf("Argomenti non validi\n");
		return -1;
	}

	// Inizializzatione del server
	initServer();

	initSharedMemory(atoi(argv[1]), atoi(argv[2]));
	intiMessageQueue();
	intiSemaphore();

	// Esecuzione del server
	getUser();



	// Chiusura del programma
	delSemaphore();
	delMessageQueue();
	delSharedMemory();

	return 0;
}	


int checkArguments(int argc, char* argv[]) {
	if(argc <= 1 || argc > 5) {
		return -1;
	}

	char *symbols[2];
	int dim[2];

	dim[0] = atoi(argv[1]);
	dim[1] = atoi(argv[2]);
	symbols[0] = argv[3];
	symbols[1] = argv[4];
	
	if(dim[0] < 5 || dim[1] < 5) {
		return -1;
	}

	if(strlen(argv[3]) > 1 || strlen(argv[4]) > 1) {
		return -1;
	}

	if(symbols[0] == symbols[1]) {
		return -1;
	}

	if(dim[0] < 5 && dim[0] > 20) {
		return -1;
	}
	
	if(dim[1] < 5 && dim[1] > 20) {
		return -1;
	}

	return 0;
}