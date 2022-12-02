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

int readUserInformation(char *name);
int userAlreadyExist();
void addUserInformation(char *name, int money);
void updateUserInformation(char *name, int money);


int main(int argc, char *argv[])
{
    printf("mon pid est : %d\n",getpid());
    kill(atoi(argv[1]),SIGUSR1);

    if (argc != 2)
    {
        printf("Usage: %s name", argv[0]);
    }

    return 0;
}

int readUserInformation(char *name) {
    FILE *file = fopen("../userStorage", "r");
    if (file == NULL) {
        printf("Error opening file");
        exit(1);
    }
    char line[256];
    while(fgets(line, sizeof(line), file) != NULL) {
        char *nameFromStorage = strtok(line, ":");
        char *moneyFromStorage = strtok(NULL, ":");
        moneyFromStorage[strlen(moneyFromStorage) - 1] = '\0';
        if (strcmp(nameFromStorage, name) == 0) {
            printf("User %s has %s money \n", nameFromStorage, moneyFromStorage);
            return (int)moneyFromStorage;
        }
    }
    fclose(file);
    return -1;
}

int userAlreadyExist(char *name) {
    FILE *file = fopen("../userStorage", "r");
    if (file == NULL) {
        printf("Error opening file");
        exit(1);
    }
    char line[256];
    while(fgets(line, sizeof(line), file) != NULL) {
        char *nameFromStorage = strtok(line, ":");
        if (strcmp(nameFromStorage, name) == 0) {
            printf("User already exist !\n");
            return 1;
        }
    }
    fclose(file);
    return 0;
}

void addUserInformation(char *name, int money) {
    FILE *file = fopen("../userStorage", "a");
    if (file == NULL) {
        printf("Error opening file");
        exit(1);
    }
    file = fopen("../userStorage", "a");
    fseek(file, 0, SEEK_END);
    fprintf(file, "%s:%d\n", name, money);
    fclose(file);
}

void updateUserInformation(char *name, int money) {
    FILE *file = fopen("../userStorage", "r");
    FILE *tempFile = fopen("../tempUserStorage", "w");

    if (file == NULL) {
        printf("Error opening file");
        exit(1);
    } else {
        char line[256];
        while(fgets(line, sizeof(line), file) != NULL) {
            char *token = strtok(line, ":");
            char *token2 = strtok(NULL, ":");
            printf("%s:%s\n", token, token2);
            if (strcmp(token, name) == 0) {
                fprintf(tempFile, "%s:%d\n", name, money);
                
            }else{
                fprintf(tempFile, "%s:%s", token, token2);
            }
        }
        fclose(file);
        fclose(tempFile);
        remove("../userStorage");
        rename("../tempUserStorage", "../userStorage");
    }
}