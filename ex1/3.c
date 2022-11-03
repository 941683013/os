#include "stdio.h"
#include "unistd.h"
#include "signal.h"
#include "stdlib.h"
#include "sys/wait.h"
int isKill;
void stop() {
    isKill = 1;
}
int main() {
    int p1, p2;
    while((p1 = fork()) == -1);
    
    if(p1 > 0) {
        while((p2 = fork()) == -1);
        if(p2 > 0) {
            printf("parent\n");
            isKill = 0;
            signal(SIGINT, stop);
            while(!isKill);
            kill(p1, 16);
            kill(p2, 17);
            wait(0);
            wait(0);
            printf("parent process is kill!\n");
            exit(0); 
        }
        else {
            printf("p2\n");
            isKill = 0;
            signal(SIGINT, SIG_IGN);
            signal(17, stop);
            while(!isKill);
            printf("child process 2 is kill by parent!\n");
            exit(0);
        }
    }
    else {
        printf("p1\n");
        isKill = 0;
        signal(SIGINT, SIG_IGN);
        signal(16, stop);
        while(!isKill);
        printf("child process 1 is kill by parent!\n");
        exit(0);
    }
    return 0;
}