#include <unistd.h>



void initSignalHandler();

void killAllClient(pid_t *tabPid, int lenTabPid);
void _addMemoryTab(pid_t **tabPid, int *lenTabPid,pid_t pid);
void _eraseClient(pid_t **tabPid, int *lenTabPid,pid_t pid);
void _killAllClient(pid_t *tabPid, int lenTabPid);