#include "stdio.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/msg.h"
#include "sys/ipc.h"
#include "sys/wait.h"
#include "stdlib.h"

#define MSGKEY 75

struct msgform {
    long mtype;
    char mtrex[1030]; 
} msg;

int msgqid, i;
/**
 * 客户端进程传输mtype和mtrex, mtype控制是否结束
*/
void client() {
    int i;
    msgqid = msgget(MSGKEY, 0777);
    for(i = 3; i >= 1; i--) {
        msg.mtype = i;
        sleep(0.5);
        printf("enter message:\n");
        scanf("%s", msg.mtrex);
        printf("(client)sent\n");
        msgsnd(msgqid, &msg, 1024, 0);
    }
    exit(0);
}
/**
 * 服务端进程接收客户端发送的消息
*/
void server() {
    msgqid = msgget(MSGKEY, 0777|IPC_CREAT);
    do {
        msgrcv(msgqid, &msg, 1030, 0, 0);
        printf("(server)received: %s\n", msg.mtrex);
    } while(msg.mtype != 1);
    msgctl(msgqid, IPC_RMID, 0);
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