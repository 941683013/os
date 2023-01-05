// 6. 退出程序 halt()(文件名 halt. c)
#include <stdio.h>
#include "filesys.h"
#include "stdlib.h"
void halt() {
struct inode *inode;
int i, j;
// 1. write back the current dir
chdir("..") ;
iput(cur_path_inode) ;
// 2. free the u_ofile and sys_ofile and inode
for(i=0;i<USERNUM; i++) {
if(user[i]. u_uid!=0) {
for(j=0;j<NOFILE;j++) {
if(user[i]. u_ofile[j] !=SYSOPENFILE+1) {
close(i, j);
user[i] . u_ofile[j] =SYSOPENFILE+1;
}
}
}
}
// 3. write back the filesys to the disk
fseek(fd, BLOCKSIZ, SEEK_SET) ;
fwrite(&filsys, 1, sizeof(struct filsys) , fd) ;
// 4. close the file system column
fclose(fd) ;
// 5. say GOODBYE to all the user
printf("\nGood bye. See you Next Time. \n") ;
exit(0) ;
}