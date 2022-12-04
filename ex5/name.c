#include<string.h>
#include<stdio.h>
#include"filesys.h"
unsigned int namei(char *name)
{
    int i,notfound=1;
    for(i=0;((i<dir.size)&&(notfound));i++)
    if((!strcmp(dir.direct[i].d_name,name))&&(dir.direct[i].d_ino!=0))
    return dir.direct[i].d_ino;
    return 0;
}

unsigned int iname(char *name)
{
    int i,notfound=1;
    for(i=0;((i<DIRNUM)&&(notfound));i++)
    if(dir.direct[i].d_ino==0)
    {
        notfound=0;
        break;
    }
    if(notfound)
    {
        printf("\n The current directory is full!\n");
        return 0;
    }
    else
    {
        strcpy(dir.direct[i].d_name,name);
        dir.direct[i].d_ino=1;
        return i;
    }
}