#ifndef ROULETTE
#include "roulette.h"
#define ROULETTE 1
#endif


#define WAIT_DRAW 10
void*serverSignalHandler(int signal, siginfo_t *info);
void initSignalHandler();
void *drawNumber();