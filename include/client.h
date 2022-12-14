#ifndef ROULETTE
#include "roulette.h"
#define ROULETTE 1
#endif

#define BLCK   "\x1B[30m"
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

typedef struct {
    char *name;
    int money;
    int pid;
} clientData ;

typedef struct {
    char bet[30];
    int amount;
    int multiplicator;
} betData;



void *clientSignalHandler(int signal, siginfo_t *info);
void *betThreadHandler(void *arg);
void *resultThreadHandler(void *arg);
void clientExit(int status);