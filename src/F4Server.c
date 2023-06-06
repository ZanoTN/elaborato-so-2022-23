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
		return -1;
	}

	// Inizializzatione del server
	initServer(argv);

	// Esecuzione del server
	getUser();

	while(1==1){}

	// Chiusura del programma
	closeServer();

	return 0;
}	


int checkArguments(int argc, char* argv[]) {
	char *symbols[2];
	int dim[2];
	
	if(argc <= 1 || argc > 5) {
		puts("ERROR: Expected 5 arguments: F4Server [0] [1] [2] [3]");
		puts("- [0]: nr. line of the grid");
		puts("- [1]: nr. columns of the grid");
		puts("- [2]: symbol player 1");
		puts("- [3]: symbol player 2");
		return -1;
	}

	if(strlen(argv[3]) > 1 || strlen(argv[4]) > 1) {
		puts("ERROR: Expected symbol of one char");
		return -1;
	}

	dim[0] = atoi(argv[1]);
	dim[1] = atoi(argv[2]);
	symbols[0] = argv[3];
	symbols[1] = argv[4];

	if(dim[0] < 5 || dim[1] < 5) {
		puts("ERROR: Expected minium field size of 5x5");
		return -1;
	}

	if(dim[0] > 20 || dim[1] > 20) {
		puts("ERROR: Expected maximum field size of 25x25");
		return -1;
	}

	if(*symbols[0] == *symbols[1]) {
		puts("ERROR: Same symbol is not a good choice");
		return -1;
	}

	return 0;
}