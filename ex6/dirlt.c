// 19. 打印输出函数 dirlt() (文件名 dirlt. c)
#include <stdio.h>
#include "filesys.h"
void dirlt(int j)
{
 int i;
printf("dir. size=%d\n", dir. size);
for(i=0; i<dir. size+j;i++)
{
printf("i=%d, d_name=%s, d_ino=%dn", i, dir. direct[i] . d_name, dir. direct[i].d_ino) ;
}
}