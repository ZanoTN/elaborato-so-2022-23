#ifndef F4SERVER_H_ 
#define F4SERVER_H_ 

#include<unistd.h>
#include <sys/types.h>

/// @brief Exit from program with error
/// @param msg Specific error string
/// @return If the arguments is not valid return -1
int checkArguments(int argc, char* argv[]);

/// @brief Start the server "Forza 4"
/// @param shmData Pointer to shared memory
/// @param semid Id of the set of semaphore
/// @param pathFIFO Path for the FIFO
void startServer(const void* shmData, int semid, char* pathFIFO);

void waitForClient(char* pathFIFO, unsigned short client_nr, pid_t* pid, char* name);

#endif