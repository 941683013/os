#include "stdio.h"
#include "unistd.h"
#include "signal.h"
#include "stdlib.h"
#include "sys/wait.h"

int pid1, pid2;
int EndFlag = 0, pf1 = 0, pf2 = 0;

void IntDelete() {
    kill(pid1, 16);
    kill(pid2, 17);
    EndFlag = 1;
}

void Int1() {
    printf("child process 1 is killed by parent \n");
    exit(0);
}

void Int2() {
    printf("child process 2 is killed by parent \n");
    exit(0);
}

/**
 * 实验现象：
 *          由于程序中忽略了del和终止所以程序进入死循环
*/
int main() {

    int exitpid;
    signal(SIGINT, SIG_IGN);
    signal(SIGINT, SIG_IGN);

    while((pid1 = fork()) == -1);
    if(pid1 == 0) {
        printf("p1 \n");
        signal(SIGUSR1, Int1);
        signal(16, SIG_IGN);
        pause();
        exit(0);
    }
    else {
        while((pid2 = fork()) == -1);
        if(pid2 == 0) {
            printf("p2\n");
            signal(SIGUSR1, Int2);
            signal(17, SIG_IGN);
            pause();
            exit(0);
        }
        else {
            printf("parent \n");
            signal(SIGINT, IntDelete);
            waitpid(-1, &exitpid, 0);
            printf("parent process is killed \n");
            exit(0);
        }

    }

    return 0;
}