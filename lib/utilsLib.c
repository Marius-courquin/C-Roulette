#include "../include/utilsLib.h"
#include "../include/server.h"


void initSignalHandler(){
    struct sigaction serverAction;
    serverAction.sa_handler = serverSignalHandler;
    sigemptyset(&serverAction.sa_mask);
    sigprocmask(SIG_SETMASK, &serverAction.sa_mask,NULL); 
    sigaction(SIGUSR1, &serverAction, NULL);
    sigaction(SIGUSR2, &serverAction, NULL);
    sigaction(SIGINT, &serverAction, NULL);
}


void _addMemoryTab(pid_t **tabPid, int *lenTabPid, pid_t pid){
    *lenTabPid = *lenTabPid + 1;
    *tabPid = (pid_t*)realloc(tabPid,sizeof(pid_t)*(*lenTabPid));
    *tabPid[*lenTabPid-1] = pid;
}
void _eraseClient(pid_t **tabPid, int *lenTabPid, pid_t pid){
    int i;
    for(i = 0; i < *lenTabPid; i++){
        if(*tabPid[i] == pid){
           break;
        }
    }
    *lenTabPid = *lenTabPid -1;
    for(i; i < *lenTabPid; i++){
        *tabPid[i] = *tabPid[i+1];
    }
    *tabPid = (pid_t*)realloc(tabPid,sizeof(pid_t)*(*lenTabPid));
}

void _killAllClient(pid_t *tabPid, int lenTabPid){
    for(int i = 0; i <  lenTabPid; i++){
        kill(tabPid[i],SIGKILL);
    }
}