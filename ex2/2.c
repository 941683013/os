#include "stdio.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/msg.h"
#include "sys/ipc.h"
#include "sys/wait.h"
#include "stdlib.h"
#include "sys/shm.h"

#define MSGKEY 75

int shmid, i;
int *addr;
/**
 * 客户端进程发送信息到服务端进程
*/
void client() {
    int i;
    shmid = shmget(MSGKEY,1024, 0777);
    addr = shmat(shmid, 0, 0);
    for(i = 9; i >= 0; i--) {
        while(*addr != -1);
        printf("(client)sent: %d\n", i);
        *addr = i;
    }
    exit(0);
}
/**
 * 服务端接收消息并打印收到的结果
*/
void server() {
    shmid = shmget(MSGKEY, 1024,0777|IPC_CREAT);
    addr = shmat(shmid, 0, 0);
    do {
        *addr = -1;
        while (*addr == -1);
        printf("(server)received: %d\n", *addr);
    } while(*addr);
    shmctl(shmid, IPC_RMID, 0);
    exit(0);
}

int main() {

    while((i = fork()) == -1);
    if(!i) server();
    while((i = fork()) == -1);
    if(!i) client();
    wait(0);
    wait(0);
    return 0;
}