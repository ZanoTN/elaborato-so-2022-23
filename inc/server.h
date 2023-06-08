#ifndef SERVER_H_
#define SERVER_H_

#include<sys/types.h>
#include<time.h>

struct player_struct {
	pid_t pid;
	char symbol;
	char username[50];
};

extern struct player_struct player[];
extern time_t timeLastSIGINT;


/// @brief Handler for SIGINT
void sigHandlerInt(int signum);

/// @brief Initialize all connection for server
void initServer();

/// @brief Close alla connection all connection of the server
void closeServer();

/// @brief Attende il collegamento dei due utenti
void getUser();

/// @brief @brief Play game 
void game();

#endif