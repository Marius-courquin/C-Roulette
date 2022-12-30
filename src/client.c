/*
*@name : client.c
*@brief : This file contains the client code
*/
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <semaphore.h>
#include <stdlib.h>
#include <pthread.h>
#include "../include/libUserStorage.h"
#include "../include/libSharedMemory.h"
#include "../include/libSemaphore.h"
#include "../include/libClient.h"
#include "../include/libUtils.h"

int sharedMemoryId;
serverData sharedMemoryContent;
int clientMoney = 0;
sem_t *semResultDraw, *semStartBet, *semFile;
int nbOfBetInProgress = 0;
pthread_t betThread;
pthread_t resultThread;
clientData client;
betData *betList;
pthread_mutex_t endOfBetMutex = PTHREAD_MUTEX_INITIALIZER ;
pthread_cond_t endOfBetCondition = PTHREAD_COND_INITIALIZER;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s name \n", argv[0]);
        exit(EXIT_FAILURE);
    }
    client.name = argv[1];
    system("clear");
    printf("Welcome %s to the C-Roulette Game !\n", argv[1]);
    openAllSemaphore(&semResultDraw, &semStartBet, &semFile);
    sem_wait(semFile);
    client.money = userOnboarding(client.name, STARTING_MONEY);
    sem_post(semFile);
    printf("You have %d$ to play with !\n", client.money);
    sharedMemoryId = createSharedMemory();
    sharedMemoryContent = readSharedMemory(sharedMemoryId);   
    kill(sharedMemoryContent.pid, SIGUSR1);
    initSignalHandler(clientSignalHandler);
    pthread_create(&betThread, NULL, betThreadHandler, NULL);
    pthread_create(&resultThread, NULL, resultThreadHandler, NULL);
    while(1);
    return 0;
}

void *clientSignalHandler(int signal, siginfo_t *info){
    switch(signal){
        case SIGINT:
            printf("Client is shutting down !\n");
            sem_wait(semFile);
            updateUserInformation(client.name, client.money);
            sem_post(semFile);
            kill(sharedMemoryContent.pid, SIGUSR2);
            exit(0);
            break;
        default:
            printf("Unknown signal %d\n",info->si_pid);
            break;
    }
    return NULL;
}

void *betThreadHandler(void *arg) { 
    sem_wait(semFile);
    client.money = userOnboarding(client.name, STARTING_MONEY);
    sem_post(semFile);
    printf("Waiting for the bet to start ...\n");
    sem_wait(semStartBet);
    clearTerminal();
    bet(&client,&betList,&nbOfBetInProgress);
}

void *resultThreadHandler(void *arg) {
    int gain = 0;
    while(1){
        sem_wait(semResultDraw);
        pthread_cancel(betThread);
        clearTerminal();
        printf("Let's check the result !\n");
        printf("Drum roll ...\n");
        sleep(1);
        sharedMemoryContent = readSharedMemory(sharedMemoryId);
        displayBetResult(sharedMemoryContent.resultNumber);
        gain = computeGain(sharedMemoryContent.resultNumber,betList,nbOfBetInProgress);
        writeBestBet(gain,client.name);

        sem_wait(semFile);
        updateUserInformation(client.name, client.money + gain);
        sem_post(semFile);
        
        displayBestBet();
        if(nbOfBetInProgress > 0){
            free(betList);
            nbOfBetInProgress = 0;
        }
        pthread_create(&betThread, NULL, betThreadHandler, NULL);
    }
}
