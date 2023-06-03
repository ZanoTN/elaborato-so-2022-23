#ifndef SERVER_H_
#define SERVER_H_

#include<sys/types.h>

struct player_struct {
	pid_t pid;
	char username[];
};

extern struct player_struct player[];

/// @brief Init Shared Memory
void initSharedMemory(unsigned short hight, unsigned short whith);

/// @brief Init Semaphore
void intiSemaphore();

/// @brief Init Message queue
void intiMessageQueue();

/// @brief Rimozione della message queue
void delMessageQueue();

/// @brief Rimozione della memoria condivisa
void delSharedMemory();

/// @brief Rimozione set semafori
void delSemaphore();

/// @brief Attende il collegamento dei due utenti
void getUser();

#endif