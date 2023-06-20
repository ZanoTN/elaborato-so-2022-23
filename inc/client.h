#ifndef CLIENT_H_
#define CLIENT_H_

#include<sys/types.h>
#include<time.h>


typedef struct player {
	pid_t pid;
	char username[50];
} player_t;

typedef struct var{
	pid_t pid_server;
	int8_t client_id;
	player_t enemy_player;
	int end_match;
} var_t;


extern time_t timeLastSIGINT;

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
void sendStatus(u_int16_t statusCode);

/// @brief loop of the game
void loop();

#endif