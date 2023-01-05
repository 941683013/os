// 11. 访问控制函数 access()(文件名 access. c)
#include <stdio.h>
#include "filesys.h"
unsigned int access(unsigned int user_id,struct inode *inode,unsigned short mode)
{
switch(mode) {
case READ:
if(inode->di_mode&ODIREAD) return 1;
if((inode->di_mode&GDIREAD)
&&(user[user_id] . u_gid==inode->di_gid) ) return 1;
if((inode->di_mode&UDIREAD)
&&(user[user_id] . u_uid==inode->di_uid) )return 1;
return 0;
case WRITE:
if(inode->di_mode&ODIWRITE) return 1;
if((inode->di_mode&GDIWRITE)
&&(user[user_id] . u_gid==inode->di_gid) ) return 1;
if((inode->di_mode&UDIWRITE)
&&(user[user_id] . u_uid==inode->di_uid) ) return 1;
return 0;
case EXECUTE:
if(inode->di_mode&ODIEXECUTE) return 1;
if((inode->di_mode&GDIEXICUTE)
&&(user[user_id] . u_gid==inode->di_gid) ) return 1;
if((inode->di_mode&UDIEXICUTE)
 &&(user[user_id] . u_uid==inode->di_uid) ) return 1;
return 0;
case DEFAULTMODE:
return 1;
default:
return 0;
}
}