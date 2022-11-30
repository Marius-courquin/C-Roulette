
#include <unistd.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


typedef struct {
    int resultNumber;
    pid_t pid;
    int nbUserInGame;
} serverData;
