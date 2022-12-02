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
#include <sys/ipc.h>
#include "../include/libUserStorage.h"
#include "../include/client.h"





int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s name \n", argv[0]);
        exit(EXIT_FAILURE);
    }

    printf("Welcome %s to the C-Roulette Game !\n", argv[1]);
    userOnboarding(argv[1], STARTING_MONEY);
    return 0;
}

