#include "../include/libUserStorage.h"


FILE *openFile(char *fileName, char *mode){
    FILE *file = fopen(fileName, mode);
    if(file == NULL){
        perror("Error while opening file");
        exit(EXIT_FAILURE);
    }
    return file;
}

int readUserInformation(char *name) {
    FILE *file = openFile(USER_STORAGE_PATH,"r");
    char line[256];
    char *nameFromStorage;
    char *moneyFromStorage;
    while(fgets(line, sizeof(line), file) != NULL) {
        nameFromStorage = strtok(line, ":");
        moneyFromStorage = strtok(NULL, ":");
        moneyFromStorage[strlen(moneyFromStorage) - 1] = '\0';
        if (strcmp(nameFromStorage, name) == 0) {
            return atoi(moneyFromStorage);
        }
    }
    fclose(file);
    return -1;
}

int userAlreadyExist(char *name) {
    FILE *file = openFile(USER_STORAGE_PATH,"r");

    char line[256];
    char *nameFromStorage;
    while(fgets(line, sizeof(line), file) != NULL) {
        nameFromStorage = strtok(line, ":");
        if (strcmp(nameFromStorage, name) == 0) {
            return 1;
        }
    }

    fclose(file);
    return 0;
}

void addUserInformation(char *name, int money) {
    FILE *file = openFile(USER_STORAGE_PATH,"a");
    fseek(file, 0, SEEK_END);
    fprintf(file, "%s:%d\n", name, money);
    fclose(file);
}

void updateUserInformation(char *name, int money) {
    FILE *file = openFile(USER_STORAGE_PATH,"r");
    FILE *tempFile = openFile("userStorageTemp","w");

    char line[256];
    char *nameFromStorage;
    char *moneyFromStorage;
    char *userState;
    while(fgets(line, sizeof(line), file) != NULL) {
        nameFromStorage = strtok(line, ":");
        moneyFromStorage = strtok(NULL, ":");
        userState = strtok(NULL, ":");
        userState[strlen(userState) - 1] = '\0';
        if (strcmp(nameFromStorage, name) == 0) {
            fprintf(tempFile, "%s:%d:%s\n", name, money, userState);
        }else{
            fprintf(tempFile, "%s:%s:%s\n", nameFromStorage, moneyFromStorage, userState);
        }
    }

    fclose(file);
    fclose(tempFile);
    remove(USER_STORAGE_PATH);
    rename("userStorageTemp", USER_STORAGE_PATH);
}

int userOnboarding(char *name, int *money) {
    printf("Connecting to the C-Roulette... \n");
    if (userAlreadyExist(name) == 0) {
            addUserInformation(name, STARTING_MONEY);
            *money = STARTING_MONEY;
            connectUser(name);
            return 1;
    } else {
        if (userIsAlreadyConnected(name) == 1) {
            printf("This user is already connected ! \n");
            return -1;
        } else {
            int userActualMoney = readUserInformation(name);
            if (userActualMoney != -1) {
                connectUser(name);
                *money = userActualMoney;
                return 1;
            } else {
                printf("Error while reading user information");
                return -1;
            }
        } 
    }
}

int getUserMoney(char *name) {
    FILE *file = openFile(USER_STORAGE_PATH,"r");

    char line[256];
    char *nameFromStorage;
    char *moneyFromStorage;
    while(fgets(line, sizeof(line), file) != NULL) {
        nameFromStorage = strtok(line, ":");
        moneyFromStorage = strtok(NULL, ":");
        if (strcmp(nameFromStorage, name) == 0) {
            return atoi(moneyFromStorage);
        }
    }
    fclose(file);
    return -1;
}

int userIsAlreadyConnected(char *name) {
    char line[256];
    char *nameFromStorage;
    char *moneyFromStorage;
    char *isUserConnected;
    FILE *file = openFile(USER_STORAGE_PATH,"r");

    while(fgets(line, sizeof(line), file) != NULL) {
        nameFromStorage = strtok(line, ":");
        moneyFromStorage = strtok(NULL, ":");
        isUserConnected = strtok(NULL, ":");
        isUserConnected[strlen(isUserConnected) - 1] = '\0';
        if (strcmp(nameFromStorage, name) == 0) {
            if (strcmp(isUserConnected, "connected") == 0) {
                return 1;
            } else {
                return 0;
            }
        }
    }
    fclose(file);
    return 0;
}

void connectUser(char *name) {
    FILE *file = openFile(USER_STORAGE_PATH,"r");
    FILE *tempFile = openFile("userStorageTemp","w");

    char line[256];
    char *nameFromStorage;
    char *moneyFromStorage;
    char *userState;
    while(fgets(line, sizeof(line), file) != NULL) {
        nameFromStorage = strtok(line, ":");
        moneyFromStorage = strtok(NULL, ":");
        userState = strtok(NULL, ":");
        if (strcmp(nameFromStorage, name) == 0) {
            if (userState == NULL) {
                moneyFromStorage[strlen(moneyFromStorage) - 1] = '\0';
            }
            fprintf(tempFile, "%s:%s:connected\n", nameFromStorage, moneyFromStorage);
        } else if (userState != NULL) {
            userState[strlen(userState) - 1] = '\0';
            fprintf(tempFile, "%s:%s:%s\n", nameFromStorage, moneyFromStorage, userState);
        } else {
            fprintf(tempFile, "%s:%s\n", nameFromStorage, moneyFromStorage);
        }
    }

    fclose(file);
    fclose(tempFile);
    remove(USER_STORAGE_PATH);
    rename("userStorageTemp", USER_STORAGE_PATH);
}

void disconnectUser(char *name) {
    FILE *file = openFile(USER_STORAGE_PATH,"r");
    FILE *tempFile = openFile("userStorageTemp","w");

    char line[256];
    char *nameFromStorage;
    char *moneyFromStorage;
    char *userState;
    while(fgets(line, sizeof(line), file) != NULL) {
        nameFromStorage = strtok(line, ":");
        moneyFromStorage = strtok(NULL, ":");
        userState = strtok(NULL, ":");
        userState[strlen(userState) - 1] = '\0';
        if (strcmp(nameFromStorage, name) == 0) {
            fprintf(tempFile, "%s:%s:disconnected\n", name, moneyFromStorage);
        } else {
            fprintf(tempFile, "%s:%s:%s\n", nameFromStorage, moneyFromStorage, userState);
        }
    }

    fclose(file);
    fclose(tempFile);
    remove(USER_STORAGE_PATH);
    rename("userStorageTemp", USER_STORAGE_PATH);
}
