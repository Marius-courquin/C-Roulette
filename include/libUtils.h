
#ifndef ROULETTE
    #include "roulette.h"
#define ROULETTE 1
#endif

void initSignalHandler(void *handlerFunction(int,siginfo_t*));
void addMemoryTab(pid_t **tabPid, int *lenTabPid,pid_t pid);
void eraseClient(pid_t **tabPid, int *lenTabPid,pid_t pid);
void killAllClient(pid_t *tabPid, int lenTabPid);
int _searchClient(pid_t *tabPid, int lenTabPid, pid_t pid);
