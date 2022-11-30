/*
*@name : server.c
*@brief : This file contains the server code
*
*
*
*/



#include "../include/server.h"
#include "../include/libSharedMemory.h"
#include "../include/libUtils.h"
#include <time.h>

pid_t *tabPid = NULL;
int isPartyStarted = 0;
int lenTabPid = 0;
serverData serveurDatas;
serverData sharedMemory;
int sharedMemoryId;
//thread
pthread_t thread[2];



int main(int argc, char *argv[]){
    serveurDatas.pid = getpid();
    printf("mon pid est : %d\n",serveurDatas.pid);
    serveurDatas.nbUserInGame = 0;
    sharedMemoryId = createSharedMemory();
    writeSharedMemory(serveurDatas,sharedMemoryId);
    initSignalHandler(serverSignalHandler);
    while(1){
        pause();
        writeSharedMemory(serveurDatas,sharedMemoryId);
        sleep(1);
        sharedMemory = readSharedMemory(sharedMemoryId);
        printf("nbUserInGame : %d\n",sharedMemory.nbUserInGame);
        printf("pid : %d\n",sharedMemory.pid);
        printf("result : %d\n",sharedMemory.resultNumber);
    }
    return 0;
}

void*serverSignalHandler(int signal, siginfo_t *info){

    //printf all sig_info
    switch(signal){
        case SIGINT:
            printf("Server is shutting down\n");
            killAllClient(tabPid,lenTabPid);
            exit(0);
            break;
        case SIGUSR1:
            printf("new Client , pid : %d\n",info->si_pid);
            addMemoryTab(&tabPid,&lenTabPid,info->si_pid);
            serveurDatas.nbUserInGame++;
            if(isPartyStarted == 0){
                isPartyStarted = 1;
                alarm(WAIT_DRAW);
            }
            break;
        case SIGUSR2:
            printf("Client %d is leaving\n",info->si_pid);
            serveurDatas.nbUserInGame--;
            eraseClient(&tabPid,&lenTabPid,info->si_pid);
            break;
        case SIGALRM:
            printf("Time is up\n");
            srand(time(NULL));
            serveurDatas.resultNumber = rand()%37;
            writeSharedMemory(serveurDatas,sharedMemoryId);
            if(serveurDatas.nbUserInGame > 0)
                alarm(WAIT_DRAW);
            else
                isPartyStarted = 0;
           break;
        default:
            printf("Unknown signal %d\n",info->si_pid);
            break;
    }
    return NULL;
}
