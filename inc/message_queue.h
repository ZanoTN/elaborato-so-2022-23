#ifndef MESSAGE_QUEUE_H_
#define MESSAGE_QUEUE_H_

#include<sys/types.h>

extern int msqid;

// Struct per la richiesta di accedere ad una partita
struct RequestJoinToMatch {
	long mtype;
	pid_t pidClient;					// Client & Server: pid_t del client
	char userName[50];				// Client: Unsername del client
	int sharedMemoryId;				// Server: ID della memoria condivisa
	unsigned short approved;	// Server: Richiesta approvata
	unsigned short nrClient;	// Server: Numero del client
};


typedef struct RequestJoinToMatch RequestJoinToMatch_t;
extern size_t size[];

/// @brief Connessione alla message queue con key generata da ftok; 
void connectToMessageQueue();

/// @brief Disconnessione dalla message queue
void disconectFromMessageQueue();

/// @brief Inviare un messaggio
/// @param mType Tipo del messaggio
/// @param buf Buffer del messaggio
void sendMsg(long mType, void* buf);

/// @brief Ricezione di un messaggio
/// @param mType Tipo del messaggio
void reciveMsg(long mType, void* buf);


#endif
