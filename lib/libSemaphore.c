#include "../include/roulette.h"
#include "../include/libSemaphore.h"
#include <fcntl.h>




//only for the server
void initAllSemaphore(sem_t **semResultDraw, sem_t **semStartBet, sem_t** semFile){
    *semResultDraw = sem_open(SEMAPHORE_DRAW_RESULT, O_CREAT, 0666, 0);
    *semStartBet = sem_open(SEMAPHORE_START_BET, O_CREAT, 0666, 0);
    *semFile = sem_open(SEMAPHORE_FILE, O_CREAT, 0666, 0);
}

//only for Clients
void openAllSemaphore(sem_t **semResultDraw, sem_t **semStartBet, sem_t **semFile){
    *semResultDraw = sem_open(SEMAPHORE_DRAW_RESULT, O_RDWR);
    *semStartBet = sem_open(SEMAPHORE_START_BET, O_RDWR);
    *semFile = sem_open(SEMAPHORE_FILE, O_RDWR);
}
//only for the server
void eraseAllSemaphore(){
    sem_unlink(SEMAPHORE_DRAW_RESULT);
    sem_unlink(SEMAPHORE_START_BET);
    sem_unlink(SEMAPHORE_FILE);
}

void postDrawResult(sem_t *semResultDraw , int nbClient){
    for(int i = 0; i < nbClient; i++){
        sem_post(semResultDraw);
    }
}

void postStartBet(sem_t *semStartBet, int nbClient){
    for(int i = 0; i < nbClient; i++){
        sem_post(semStartBet);
    }
}