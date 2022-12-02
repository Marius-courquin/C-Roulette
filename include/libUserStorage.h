#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define USER_STORAGE_PATH "userStorage"

FILE *openFile(char *fileName, char *mode);
int readUserInformation(char *name);
int userAlreadyExist();
void addUserInformation(char *name, int money);
void updateUserInformation(char *name, int money);
int userOnboarding(char *name, int money);
