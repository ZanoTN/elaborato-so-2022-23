#ifndef CLIENT_H_
#define CLIENT_H_

#include<sys/types.h>
#include<time.h>


extern time_t timeLastSIGINT;
extern int8_t client_id;

/// @brief Handler for SIGINT
void sigHandlerInt(int signum);

/// @brief Handler for SIGTERM
void sigHandlerTerm(int signum);

/// @brief Inizializzazione del client
void initClient();

/// @brief Invio di una richiesta di collegamento al server (partita)
/// @param username Username for the request
void requestJoin(char username[50]);

/// @brief Close server
void closeClient();

/// @brief Run game
void game();

#endif