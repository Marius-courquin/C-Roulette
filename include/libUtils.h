
#ifndef ROULETTE
    #include "roulette.h"
#define ROULETTE 1
#endif

void initSignalHandler(void *handlerFunction(int,siginfo_t*));
void addMemoryTab(pid_t **tabPid, int *pidTabLen,pid_t pid);
void eraseClient(pid_t **tabPid, int *pidTabLen,pid_t pid);
void killAllClient(pid_t *tabPid, int pidTabLen);
int _searchClient(pid_t *tabPid, int pidTabLen, pid_t pid);
void clearTerminal();
