#include "../include/libUtils.h"
#include "../include/server.h"



void initSignalHandler(void *handlerFunction(int,siginfo_t*)){
    struct sigaction serverAction;
    serverAction.sa_handler = (void*)handlerFunction;
    serverAction.sa_flags = SA_SIGINFO;
    sigemptyset(&serverAction.sa_mask);
    sigprocmask(SIG_SETMASK, &serverAction.sa_mask,NULL); 
    sigaction(SIGUSR1, &serverAction, NULL);
    sigaction(SIGUSR2, &serverAction, NULL);
    sigaction(SIGINT, &serverAction, NULL);
    sigaction(SIGALRM, &serverAction, NULL);
}


int _searchClient(pid_t *tabPid, int lenTabPid, pid_t pid){
    int i;
    for(i = 0; i < lenTabPid; i++){
        if(tabPid[i] == pid){
            return i;
        }
    }
    return -1;
}

void addMemoryTab(pid_t **tabPid, int *pidTabLen, pid_t pid){
    if(_searchClient(*tabPid,*pidTabLen,pid) == -1){
        *pidTabLen += 1;
        *tabPid = realloc(*tabPid,sizeof(pid_t)*(*pidTabLen));
        (*tabPid)[ *pidTabLen-1] = pid;
    }
}

void eraseClient(pid_t **tabPid, int *lenTabPid, pid_t pid){
    int i = _searchClient(*tabPid,*lenTabPid,pid);
    if(i == -1){
        perror("Client not found");
    }
    *lenTabPid = *lenTabPid -1;
    for(i; i < *lenTabPid; i++){
        (*tabPid)[i] = (*tabPid)[i+1];
    }
    printf("ok we changed the tab : %d\n",*lenTabPid);
    *tabPid = realloc(*tabPid, sizeof(pid_t)*(*lenTabPid));
    printf("successful realloc\n");
}

void killAllClient(pid_t *tabPid, int lenTabPid){
    for(int i = 0; i <  lenTabPid; i++){
        kill(tabPid[i], SIGKILL);
    }
}

void clearTerminal(){
    system("clear");
}