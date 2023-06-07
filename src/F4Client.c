#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include"../inc/F4Client.h"
#include"../inc/client.h"


int main(int argc, char *argv[]) {

	if(checkArguments(argc, argv) == -1) {
		return -1;
	}

	// Inizializzazione del client
	initClient();

	// Gioco
	requestJoin(argv[1]);
	game();

	closeClient();
}

int checkArguments(int argc, char* argv[]) {
	
	if(argc <= 1 || argc > 2) {
		puts("ERROR: Expected 1 arguments: F4Client [0]");
		puts("- [0]: your nickname");
		return -1;
	}

	if(strlen(argv[1]) > 50) {
		puts("ERROR: Expected maximun lenght of username of 50 charter");
		return -1;
	}

	return 0;
}