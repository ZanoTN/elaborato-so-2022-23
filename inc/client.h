#ifndef CLIENT_H_
#define CLIENT_H_

#include<sys/types.h>
#include<time.h>

typedef struct global_var{
	pid_t pid_server;
	pid_t pid_other_client;
	int8_t client_id;
} global_var_t;


extern time_t timeLastSIGINT;
extern pid_t pidServer;
extern int8_t client_id;

/// @brief Handler for SIGINT SIGHUP
void sigHandlerClose(int signum);

/// @brief Handler for SIGTERM
void sigHandlerTerm(int signum);

/// @brief Handler for SIGUSR1
void sigHandlerStatusCode(int signum);

/// @brief Inizializzazione del client
void initClient();

/// @brief Invio di una richiesta di collegamento al server (partita)
/// @param username Username for the request
void requestJoin(char username[50]);

/// @brief Close server
void closeClient();

/// @brief Run game
void game();

/// @brief Print game field and info
void printGame();

/// @brief Send status to a server
/// @param statusCode code
void sendStatus(int statusCode);

#endif