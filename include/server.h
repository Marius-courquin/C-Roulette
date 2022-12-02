#ifndef ROULETTE
#include "roulette.h"
#define ROULETTE 1
#endif


#define WAIT_DRAW 10
#define WAIT_BET 20
#define STATE_BET 1
#define STATE_DRAW 2
void*serverSignalHandler(int signal, siginfo_t *info);
void initSignalHandler();
void runGame();