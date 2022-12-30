#ifndef ROULETTE
#include "roulette.h"
#define ROULETTE 1
#endif


#define WAIT_DRAW 5//10
#define WAIT_BET 10//20
#define WAIT_NEW_ROUND 5//10
#define STATE_NEW_ROUND 3
#define STATE_BET 1
#define STATE_DRAW 2
void*serverSignalHandler(int signal, siginfo_t *info);
void runGame();