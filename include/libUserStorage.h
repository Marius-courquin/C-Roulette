#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define USER_STORAGE_PATH "userStorage"
#define STARTING_MONEY 1000

FILE *openFile(char *fileName, char *mode);
int readUserInformation(char *name);
int userAlreadyExist();
void addUserInformation(char *name, int money);
void updateUserInformation(char *name, int money);
int userOnboarding(char *name, int *money);
int getUserMoney(char *name);
int userIsAlreadyConnected(char *name);
void connectUser(char *name);
void disconnectUser(char *name);
