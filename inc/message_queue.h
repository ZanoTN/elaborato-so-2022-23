#ifndef MESSAGE_QUEUE_H_
#define MESSAGE_QUEUE_H_

#include<sys/types.h>



// client: Richiesta di accedere ad una partita
typedef struct requestJoinToMatch {
	long mtype;
	pid_t pidClient;					// Client & Server: pid_t del client
	char userName[50];				// Client: Unsername del client
} requestJoinToMatch_t;

// server: Risposta del server al client
typedef struct respodeToRequest {
	long mtype;
	pid_t pidServer;					// Client & Server: pid_t del client
	int sharedMemoryId;				// Server: ID della memoria condivisa
	int semaphoreId;
	int8_t approved;					// Server: Richiesta approvata
	int8_t nrClient;					// Server: Numero del client
	char symbols[2];					// Server: Send two symbols for user
	u_int16_t field_hight;		// Server: hight of field
	u_int16_t field_width;		// Server: width of field
} respodeToRequest_t;

// Start game message queue
typedef struct startGame {
	long mtype;
	char usernames[2][100];		// Server: two username
	pid_t pid_player[2];
} startGame_t;

// End game
typedef struct status {
	long mtype;
	pid_t pidClient;
	u_int16_t statusCode;
} status_t;


extern int msqid;


/// @brief Connessione alla message queue con key generata da ftok; 
void connectToMessageQueue();

/// @brief Disconnessione dalla message queue
void disconectFromMessageQueue();

/// @brief Inviare un messaggio
/// @param mType Tipo del messaggio
/// @param buf Buffer del messaggio
void sendMsg(void* buf, size_t size);

/// @brief Ricezione di un messaggio
/// @param mType Tipo del messaggio
void reciveMsg(long mType, void* buf, size_t size);


#endif
