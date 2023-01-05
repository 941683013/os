// 16. 删除文件函数 delete() (文件名 delete. c)
#include <stdio.h>
#include "filesys.h"
#include "string.h"
void delete(char *filename)
{
unsigned int dinodeid, i;
 struct inode *inode;
dinodeid=namei(filename) ;
if(dinodeid!=0)
inode=iget(dinodeid) ;
inode->di_number--;
for(i=0; i<dir. size;i++)
if(dir. direct[i] . d_ino==dinodeid) break;
i++;
while(dir. direct[i] . d_ino!=0) {
strcpy(dir. direct[i-1]. d_name, dir. direct[i] . d_name) ;
dir. direct[i-1]. d_ino=dir. direct[i] . d_ino;
i++;
}
dir. direct[i+1]. d_ino=0;
dir. size=i-1;
iput(inode) ;
printf("\ndir. size=%d\n", dir. size);
}