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
#include "../include/libSemaphore.h"
#include <time.h>

pid_t *tabPid = NULL;
int isPartyStarted = 0;
int partyState = 0;
int pidTabLen = 0;
serverData serveurDatas, sharedMemory;
int sharedMemoryId;
sem_t *semResultDraw, *semStartBet, *semFile;
void betThreadHandler(void *arg);



int main(int argc, char *argv[]){
    serveurDatas.pid = getpid();
    printf("The table is open ! It's time to gain !\n");
    serveurDatas.nbClient = 0;
    sharedMemoryId = createSharedMemory();
    writeSharedMemory(serveurDatas, sharedMemoryId);
    initSignalHandler(serverSignalHandler);
    initAllSemaphore(&semResultDraw, &semStartBet, &semFile);
    while(1);
    return 0;
}

void*serverSignalHandler(int signal, siginfo_t *info){
    switch(signal){
        case SIGINT:
            printf("Server is shutting down !\n");
            killAllClient(tabPid, pidTabLen);
            eraseAllSemaphore();
            exit(0);
            break;
        case SIGUSR1:
            printf("A new player have join the table, n° %d.\n", info->si_pid);
            addMemoryTab(&tabPid, &pidTabLen, info->si_pid);
            serveurDatas.nbClient++;
            writeSharedMemory(serveurDatas, sharedMemoryId);
            if(isPartyStarted == 0){
                isPartyStarted = 1;
                partyState = STATE_NEW_ROUND;
                alarm(WAIT_NEW_ROUND);
            }
            break;
        case SIGUSR2:
            printf("Client %d is leaving\n", info->si_pid);
            serveurDatas.nbClient--;
            eraseClient(&tabPid, &pidTabLen, info->si_pid);
            writeSharedMemory(serveurDatas, sharedMemoryId);
            break;
        case SIGALRM:
            runGame();
            break;
        default:
            printf("Unknown signal %d\n", info->si_pid);
            break;
    }
    return NULL;
}


void runGame(){
    if(serveurDatas.nbClient == 0){
        isPartyStarted = 0;
    }
    else if(partyState == STATE_NEW_ROUND){
        clearTerminal();
        printf("New round, go to bet now !\n");
        partyState = STATE_BET;
        postStartBet(semStartBet, serveurDatas.nbClient);
        alarm(WAIT_BET);
    }
    else if(partyState == STATE_BET){
        printf("Time is up, go wait for the draw now !\n");
        partyState = STATE_DRAW;
        alarm(WAIT_DRAW);
    }
    else if(partyState == STATE_DRAW){
        printf("Time is up, we have the result now !\n");
        srand(time(NULL));
        serveurDatas.client.gain = -1;
        serveurDatas.client.username[0] = '\0';
        serveurDatas.resultNumber = rand()%37;
        printf("the value is %d\n",serveurDatas.resultNumber);
        writeSharedMemory(serveurDatas, sharedMemoryId);
        postDrawResult(semResultDraw ,serveurDatas.nbClient);
        partyState = STATE_NEW_ROUND;
        alarm(WAIT_NEW_ROUND);

    }
}