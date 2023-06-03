#ifndef SEMAPHORE_H_
#define SEMAPHORE_H_

extern int semid;

/// @brief Generate a new set of semaphore and set all 0
/// @param number_semaphore Number of rhe semphore for this set 
void genereteSemaphore(int number_semaphore);

/// @brief Rimuovo il set di semafori
void removeSetSemaphore();

/// @brief Set all values of the set of semaphore
/// @param semid Id of the set of semaphore
/// @param semArray Array of the values of semaphore
void setSemaphoreArrat(int semid, unsigned short semArray[]);

/// @brief Single operation with one semaphore
/// @param semid Id of the set of semaphore
/// @param sem_num Number of the semaphore
/// @param sem_op What operation do whit sempaphore
void semaphoreOperation(int semid, unsigned short sem_num, short sem_op);

#endif