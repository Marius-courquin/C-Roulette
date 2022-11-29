#include "server.h"


int createSharedMemory();
void writeSharedMemory(serverData data, int sharedMemoryId);
serverData readSharedMemory(int sharedMemoryId);