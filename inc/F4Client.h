#ifndef F4CLIENT_H_ 
#define F4SERVERF4CLIENT_H__H_ 


/// @brief Exit from program with error
/// @param msg Specific error string
/// @return If the arguments is not valid return -1
int checkArguments(int argc, char* argv[]);

/// @brief Start the server "Forza 4"
/// @param shmData Pointer to shared memory
/// @param semid Id of the set of semaphore
/// @param pathFIFO Path for the FIFO
void startClient(char* pathFIFO);

#endif