
#include <unistd.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#define SEMAPHORE_DRAW_RESULT "roulette-draw-result"
#define SEMAPHORE_START_BET "roulette-start-bet"
#define SEMAPHORE_FILE "roulette-file"

typedef struct {
    int resultNumber;
    pid_t pid;
    int nbClient;
} serverData;
