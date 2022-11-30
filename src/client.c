#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char *argv[]){
    printf("mon pid est : %d\n",getpid());
    kill(atoi(argv[1]),SIGUSR1);
}