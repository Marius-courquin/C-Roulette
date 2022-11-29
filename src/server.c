/*
*@name : server.c
*@brief : This file contains the server code
*
*
*
*/



#include "../include/roulette.h"
#include "../include/sharedMemoryLib.h"
#include "../include/utilsLib.h"

static pid_t *tabPid;
static int lenTabPid = 0;
serverData serveurDatas;
int sharedMemoryId;
int main(int argc, char *argv[]){
    serveurDatas.pid = getpid();
    serveurDatas.nbUserInGame = 0;
    sharedMemoryId = createSharedMemory();
    initSignalHandler();



    return 0;
}


void serverSignalHandler(int signal,siginfo_t *info){

    switch(signal){
        case SIGINT:
            printf("Server is shutting down\n");
            _killAllClient(tabPid,lenTabPid);
            exit(0);
            break;
        case SIGUSR1:
            printf("new Client , pid : %d\n",info->si_pid);
            _addMemoryTab(&tabPid,&lenTabPid,info->si_pid);
            serveurDatas.nbUserInGame++;
            break;
        case SIGUSR2:
            printf("Client %d is leaving\n",info->si_pid);
            serveurDatas.nbUserInGame--;
            _eraseClient(&tabPid,&lenTabPid,info->si_pid);
            break;
        default:
            printf("Unknown signal\n");
            break;
    }
}
