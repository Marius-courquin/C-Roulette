#include "../include/libUtils.h"
#include "../include/server.h"




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