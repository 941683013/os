#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "signal.h"
#include "sys/wait.h"
int pid1, pid2;
int main() {
    int fd[2];
    char OutPipe[100], InPipe[100];
    pipe(fd);
    while((pid1 = fork()) == -1);
    if(pid1 == 0) {
        lockf(fd[1], 1, 0);
        sprintf(OutPipe, "child 1 process is sending a message! \n");
        write(fd[1], OutPipe, 50);
        sleep(1);
        lockf(fd[1], 0, 0);
        exit(0);
    }
    else {
        while((pid2 = fork()) == -1);
        if(pid2 == 0) {
            lockf(fd[1], 1, 0);
            sprintf(OutPipe, "child 2 process is sending a message! \n");
            write(fd[1], OutPipe, 50);
            sleep(1);
            exit(0);
        }
        else {
            wait(0);
            read(fd[0], InPipe, 50);
            printf("InPipe = %s \n", InPipe);
            wait(0);
            read(fd[0], InPipe, 50);
            printf("InPipe = %s \n", InPipe);
            exit(0);
        }
    }
    return 0;
}