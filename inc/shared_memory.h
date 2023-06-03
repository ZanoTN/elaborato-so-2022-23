#ifndef SHARED_MEMORY_H_
#define SHARED_MEMORY_H_

extern int shmid;
extern char* shm_pointer;

/// @brief Generate shared memory for the server
/// @param size Set the size of the shared memory
/// @return shmid (id of the shared memory)
void genereteServerSharedMemory(unsigned short fieldHight, unsigned short fieldWidth);

/// @brief Rimozione della memoria condivisa
void removeServerSharedMemory();

/// @brief Collegamento alla memoria condivisa
/// @param _shmid Id della memoria condivisa
/// @return Puntatore alla memoria
char* attachSharedMemory(int _shmid);

#endif