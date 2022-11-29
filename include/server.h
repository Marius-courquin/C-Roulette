#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


typedef struct {
    int resultNumber;
    pid_t pid;
    int nbUserInGame;
} serverData;

void serverSignalHandler(int signal, siginfo_t *info);
void initSignalHandler();