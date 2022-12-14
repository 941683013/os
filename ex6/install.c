// 5. 进入文件系统程序 install() (文件名 install. c)
#include <stdio.h>
#include <string.h>
#include "filesys.h"
void install() {
int i, j;
//1. read the filsys from the superblock
fseek(fd, BLOCKSIZ, SEEK_SET) ;
fread(&filsys, 1, sizeof(struct filsys) , fd) ;
//2. initialize the inode hash chain
for(i=0;i<NHINO; i++) {
hinode[i] . i_forw=NULL;
}
//3. initialize the sys_file
for(i=0;i<SYSOPENFILE; i++) {
sys_ofile[i] . f_count=0;
sys_ofile[i] . f_inode=NULL;
}
// 4. initialize the user
for(i=0;i<USERNUM; i++) {
user[i] . u_uid=0;
user[i] . u_gid=0;
for(j=0;j<NOFILE;j++) user[i]. u_ofile[j] =SYSOPENFILE+1;
}
// 5 read the main directory to initialize the dir
cur_path_inode=iget(1);
dir. size=cur_path_inode->di_size/(DIRSIZ+2) ;
for(i=0;i<DIRNUM;i++) {
strcpy(dir. direct[i]. d_name, " ") ;
dir. direct[i]. d_ino=0;
}
    for(i=0;i<dir. size/(BLOCKSIZ/(DIRSIZ+2) ) ;i++) {
    fseek(fd, DATASTART+BLOCKSIZ*cur_path_inode->di_addr[i] , SEEK_SET) ;
    fread(&dir. direct[(BLOCKSIZ/(DIRSIZ+2) ) *i] , 1, BLOCKSIZ, fd) ;
    }
    fseek(fd, DATASTART+BLOCKSIZ*cur_path_inode->di_addr[i] , SEEK_SET) ;
    fread(&dir. direct[(BLOCKSIZ) /(DIRSIZ+2)*i] , 1, cur_path_inode->di_size%BLOCKSIZ, fd) ;
}