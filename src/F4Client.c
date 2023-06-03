#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include"../inc/F4Client.h"
#include"../inc/client.h"

int main(int argc, char *argv[]) {
	// TODO: Controllo argomenti

	// Inizializzazione
	initMessageQueue();

	// Gioco
	sendRequestJoin(argv[1]);
}