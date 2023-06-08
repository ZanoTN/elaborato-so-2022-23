#ifndef MESSAGE_QUEUE_H_
#define MESSAGE_QUEUE_H_

#include<sys/types.h>



// client: Richiesta di accedere ad una partita
struct requestJoinToMatch {
	long mtype;
	pid_t pidClient;					// Client & Server: pid_t del client
	char userName[50];				// Client: Unsername del client
};

// server: Risposta del server al client
struct respodeToRequest {
	long mtype;
	pid_t pidClient;					// Client & Server: pid_t del client
	int sharedMemoryId;				// Server: ID della memoria condivisa
	int semaphoreId;
	int8_t approved;					// Server: Richiesta approvata
	int8_t nrClient;					// Server: Numero del client
	char symbols[2];					// Server: Send two symbols for user
	u_int16_t field_hight;		// Server: hight of field
	u_int16_t field_width;		// Server: width of field
};

struct startGame {
	long mtype;
	pid_t pidClient;					// Client & Server: pid_t del client
	char enemy_username[50];			// Server: two username
};

typedef struct startGame startGame_t;
typedef struct respodeToRequest respodeToRequest_t;
typedef struct requestJoinToMatch requestJoinToMatch_t;


extern int msqid;
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
