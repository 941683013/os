// 15. 关闭文件系统函数 close() (文件名 close. c)
#include <stdio.h>
#include "filesys.h"
void close(unsigned int user_id,unsigned short cfd) //close
{
struct inode *inode;
inode=sys_ofile[user[user_id]. u_ofile[cfd] ] . f_inode;
iput(inode) ;
sys_ofile[user[user_id] . u_ofile[cfd]] . f_count--;
user[user_id]. u_ofile[cfd] =SYSOPENFILE+1;
}