
#ifndef ROULETTE
#include "roulette.h"
#define ROULETTE 1
#endif

int createSharedMemory();
void writeSharedMemory(serverData data, int sharedMemoryId);
serverData readSharedMemory(int sharedMemoryId);