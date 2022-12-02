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
    while(fgets(line, sizeof(line), file) != NULL) {
        char *nameFromStorage = strtok(line, ":");
        char *moneyFromStorage = strtok(NULL, ":");
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
    while(fgets(line, sizeof(line), file) != NULL) {
        char *nameFromStorage = strtok(line, ":");
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
    FILE *tempFile = openFile("../userStorageTemp","w");

    char line[256];
    while(fgets(line, sizeof(line), file) != NULL) {
        char *nameFromStorage = strtok(line, ":");
        char *moneyFromStorage = strtok(NULL, ":");
        moneyFromStorage[strlen(moneyFromStorage) - 1] = '\0';
        if (strcmp(nameFromStorage, name) == 0) {
            fprintf(tempFile, "%s:%d\n", name, money);
        }else{
            fprintf(tempFile, "%s:%s\n", nameFromStorage, moneyFromStorage);
        }
    }

    fclose(file);
    fclose(tempFile);
    remove(USER_STORAGE_PATH);
    rename("../userStorageTemp", "../userStorage");
}

int userOnboarding(char *name, int money) {
    if (userAlreadyExist(name) == 0) {
        addUserInformation(name, money);
    } else {
        int userActualMoney = readUserInformation(name);
        if (userActualMoney != -1) {
            return userActualMoney;
        }
    }
}
