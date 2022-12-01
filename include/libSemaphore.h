#include <semaphore.h>


void initAllSemaphore(sem_t **semResultDraw, sem_t **semStartBet, sem_t** semFile);
void openAllSemaphore(sem_t **semResultDraw, sem_t **semStartBet, sem_t** semFile);
void eraseAllSemaphore();
void postDrawResult(sem_t *semResultDraw , int nbClient);
void postStartBet(sem_t *semStartBet, int nbClient);