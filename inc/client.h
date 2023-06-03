#ifndef CLIENT_H_
#define CLIENT_H_

/// @brief Inizializzazione della message queue
void initMessageQueue();

/// @brief Invio di una richiesta di collegamento al server (partita)
/// @param username Username for the request
void sendRequestJoin(char username[50]);

#endif