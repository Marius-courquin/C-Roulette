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
#include <pthread.h>
#include <stdlib.h>
#include "../include/libUserStorage.h"
#include "../include/libSharedMemory.h"
#include "../include/libUtils.h"
#include "../include/libSemaphore.h"
#include "../include/libClient.h"

int sharedMemoryId;
serverData sharedMemoryContent;
int clientMoney = 0;
clientData client;
sem_t *semResultDraw, *semStartBet, *semFile;
betData *betList;
int nbOfBetInProgress = 0;
pthread_t betThread;

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
    client.money = userOnboarding(argv[1], STARTING_MONEY);
    sem_post(semFile);
    printf("You have %d$ to play with !\n", client.money);
    sharedMemoryId = createSharedMemory();
    sharedMemoryContent = readSharedMemory(sharedMemoryId);   
    kill(sharedMemoryContent.pid, SIGUSR1);
    initSignalHandler(clientSignalHandler);
    pthread_create(&betThread, NULL, betThreadHandler, NULL);
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



void bet() {
    betData newBet;
    displayRouletteTable();
    if (nbOfBetInProgress > 0) {
        displayBetInProgress(betList, nbOfBetInProgress);
    }
    printf("Available money : %d$\n", client.money);
    printf("What do you want to bet on ? ( END to stop the bet )\n");
    newBet.bet = malloc(sizeof(char) * 100);
    scanf("%s", newBet.bet);
    printf("Bet : %s \n", newBet.bet);
    if (strcmp(newBet.bet, "END") == 0) {
        system("clear");
        if (nbOfBetInProgress > 0) {
            displayBetInProgress(betList, nbOfBetInProgress);
        }
        printf("End of the bet !\n");
        printf("Waiting for the draw !\n");
    } else {
        printf("How much do you want to bet ?\n");
        scanf("%d", &newBet.amount);
        if (newBet.amount > client.money) {
            system("clear");
            printf("You don't have enough money to bet that much !\n");    
            bet();
        } else {
            client.money -= newBet.amount;
            betList = (betData*)realloc(betList, sizeof(betData) * (nbOfBetInProgress + 1));
            betList[nbOfBetInProgress] = newBet;
            nbOfBetInProgress++;
            system("clear");
            bet();
        }
    }
}

void *betThreadHandler(void *arg) {
    bet();
}

void displayBetInProgress(betData *betList, int betInProgress) {
    printf("Bet in progress : ");
    for (int i = 0; i < betInProgress; i++) {
        printf("%d. %d$ on %s   ", i + 1, betList[i].amount, betList[i].bet);
    }
    printf("\n");
}