//4.初始化磁盘格式程序 format()(文件名 format. c)
#include <stdio.h>
#include "filesys.h"
#include "stdlib.h"
#include "string.h"

void format() {
struct inode *inode;
struct direct dir_buf[BLOCKSIZ/(DIRSIZ+2) ] ;
struct filsys;
unsigned int block_buf[BLOCKSIZ/sizeof(int) ];
char *buf;
int i, j;
//creat the file system
fd=fopen("filesystem", "r+w+b") ;
buf=(char*) malloc((DINODEBLK+FILEBLK+2) *BLOCKSIZ*sizeof(char) ) ;
if(buf==NULL) {
printf("\nfile system file cEeat failed! \n") ;
exit(0) ;
}
fseek(fd, 0, SEEK_SET) ;
fwrite(buf, 1, (DINODEBLK+FILEBLK+2) *BLOCKSIZ*sizeof(char), fd);
// 0. initialize the password
pwd[0] . p_uid=2116;
pwd[0] . p_gid=03;
strcpy(pwd[0]. password, "dddd") ;
pwd[1] . p_uid=2117;
pwd[1] . p_gid=03;
strcpy(pwd[1]. password, "bbbb") ;
pwd[2] . p_uid=2118;
pwd[2] . p_gid=04;
strcpy(pwd[2]. password, "abcd") ;
pwd[3] . p_uid=2119;
pwd[3] . p_gid=04;
strcpy(pwd[3]. password, "cccc") ;
pwd[4] . p_uid=2220;
pwd[4] . p_gid=05;
strcpy(pwd[4]. password, "eeee") ;
// 1 Creat the main directory & its sub dir etc and the file password
inode=iget(0) ; // 0 empty dinode id
inode->di_mode=DIEMPTY;
iput(inode) ;
inode=iget(1); // 1 main dir id
inode->di_number=1;
inode->di_mode=DEFAULTMODE| DIDIR;
inode->di_size=3*(DIRSIZ+2) ;
inode->di_addr[0]=0; //block 0# is used by the main directory
strcpy(dir_buf[0]. d_name, "..") ;
dir_buf[0]. d_ino=1;
strcpy(dir_buf[1]. d_name, ".") ;
dir_buf[1]. d_ino=1;
strcpy(dir_buf[2]. d_name, "etc") ;
dir_buf[2]. d_ino=2;
fseek(fd, DATASTART, SEEK_SET) ;
fwrite(dir_buf, 1, 3*(DIRSIZ+2), fd) ;
iput(inode) ;
inode=iget(2) ; // 2 etc dir id
inode->di_number=1;
inode->di_mode=DEFAULTMODE| DIDIR;
inode->di_size=3*(DIRSIZ+2) ;
inode->di_addr[0]=1; //block 0#is used by the etc directory
strcpy(dir_buf[0]. d_name, "..") ;
dir_buf[0]. d_ino=1;
strcpy(dir_buf[1]. d_name, "..") ;
dir_buf[1]. d_ino=2;
strcpy(dir_buf[2]. d_name, "password") ;
dir_buf[2]. d_ino=3;
fseek(fd, DATASTART+BLOCKSIZ*1, SEEK_SET);
fwrite(dir_buf, 1, 3*(DIRSIZ+2) , fd) ;
iput(inode) ;
inode=iget(3) ; //3 password id
inode->di_number=1;
inode->di_mode=DEFAULTMODE| DIDIR;
inode->di_size=BLOCKSIZ;
inode->di_addr[0]=2; //block 2#is used by the password file
for(i=5;i<PWDNUM;i++) {
pwd[i] . p_uid=0;
pwd[i] . p_gid=0;
strcpy(pwd[i]. password, " ") ;
}
fseek(fd, DATASTART+2*BLOCKSIZ, SEEK_SET);
fwrite(pwd, 1, BLOCKSIZ, fd) ;
iput(inode) ;
//2. initialize the superblock
filsys. s_isize=DINODEBLK;
filsys. s_fsize=FILEBLK;
filsys. s_ninode=DINODEBLK*BLOCKSIZ/DINODESIZ-4;
filsys. s_nfree=FILEBLK-3;
for(i=0;i<NICINOD; i++) {
// begin with 4, 0, 1, 2, 3, is used by main, etc, password
filsys. s_inode[i]=4+i;
}
filsys. s_pinode=0;
filsys. s_rinode=NICINOD+4;
block_buf[NICFREE-1]=FILEBLK+1; //FILEBLK+1 is a flag of end
for(i=0;i<NICFREE-1;i++)
 block_buf[NICFREE-2-i]=FILEBLK-i;
fseek(fd, DATASTART+BLOCKSIZ*(FILEBLK-NICFREE-1) , SEEK_SET) ;
fwrite(block_buf, 1, BLOCKSIZ, fd) ;
for(i=FILEBLK-NICFREE-1; i>2; i-=NICFREE) {
for(j=0;j<NICFREE; j++) {
block_buf[j] =i-j;
}
block_buf[j] =50;
fseek(fd, DATASTART+BLOCKSIZ*(i-1) , SEEK_SET) ;
fwrite(block_buf, 1, BLOCKSIZ, fd) ;
}
j=i+NICFREE;
for(i=j;i>2; i--) {
filsys. s_free[NICFREE-1+i-j] =i;
}
filsys. s_pfree=NICFREE-1-j+3;
filsys. s_pinode=0;
fseek(fd, BLOCKSIZ, SEEK_SET) ;
fwrite(&filsys. s_isize, 1, sizeof(filsys), fd) ;
fseek(fd, BLOCKSIZ, SEEK_SET) ;
fread(&filsys. s_isize, 1, sizeof(filsys) , fd) ;
}