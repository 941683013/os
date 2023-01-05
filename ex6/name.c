// 10. 搜索函数 namei() 和 iname() (文件名 name. c)
#include <string.h>
#include <stdio.h>
#include "filesys.h"
unsigned int namei(char *name) //namei
{
int i, notfound=1;
for(i=0;((i<dir. size) &&(notfound) ) ; i++)
if((!strcmp(dir. direct[i]. d_name, name) )&&(dir. direct[i] . d_ino!=0) )
return dir. direct[i]. d_ino; // find
return 0; // not find
}
unsigned int iname(char *name) //iname
{
int i, notfound=1;
for(i=0;((i<DIRNUM) &&(notfound) ); i++)
if(dir. direct[i] . d_ino==0) {
notfound=0;
break;
}
if(notfound) {
printf("\n The current directory is full!\n") ;
return 0;
}
else {
strcpy(dir. direct[i]. d_name, name) ;
dir. direct[i]. d_ino=1;
return i;
}
}