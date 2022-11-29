#include "../include/sharedMemoryLib.h"



int createSharedMemory(){
    key_t key = ftok("../userStorage",1111);
    int sharedMemoryId;
    sharedMemoryId = shmget(key, sizeof(serverData), IPC_CREAT | 0666);
    if(sharedMemoryId < 0){
        perror("Error in creating shared memory");
        exit(1);
    }
    return sharedMemoryId;
}


void writeSharedMemory(serverData data,int sharedMemoryId){
    int key = ftok("../userStorage",1111);
    serverData *sharedMemory = (serverData*)shmat(sharedMemoryId, NULL, 0);
    *sharedMemory = data;
    shmdt(sharedMemory);
}

void eraseSharedMemory(int sharedMemoryId){
    shmctl(sharedMemoryId, IPC_RMID, NULL);
}

serverData readSharedMemory(int sharedMemoryId){
    serverData *sharedMemory = (serverData*)shmat(sharedMemoryId, NULL, 0);
    serverData data = *sharedMemory;
    shmdt(sharedMemory);
    return data;
}