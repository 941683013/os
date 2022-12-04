// (7)获取释放索引结点内容iget()/iput()(文件名igetput.c)
#include<stdio.h>
#include"filesys.h"
#include"malloc.h"
#include <linux/module.h>
struct inode *iget(unsigned int dineodeid) {   /*iget()*/
    int existed = 0,inodeid;
    long addr;
    struct inode *temp,*newinode;

    inodeid = dineodeid % NHINO;
    if(hinode[inodeid].i_forw == NULL)
        existed = 0;
    else{
        temp = hinode[inodeid].i_forw;
        while(temp){
            if(temp->i_ino == inodeid){
                /*existed*/
                existed = 1;
                temp->i_count++;
                return temp;
            }
            /*not existed*/
            else
                temp=temp->i_forw;
        }
    }
    addr = DINODESTART + dineodeid * DINODESIZ;

    newinode = (struct inode *)malloc(sizeof(struct inode));

    fseek(fd,addr,SEEK_SET);
    fread(&(newinode->di_number),DINODESIZ,1,fd);

    newinode->i_forw = hinode[inodeid].i_forw;
    newinode->i_back = newinode;
    if(newinode->i_forw != NULL)
        newinode->i_forw->i_back = newinode;
    hinode[inodeid].i_forw = newinode;

    newinode->i_count = 1;
    newinode->i_flag = 0;
    newinode->i_ino = dineodeid;

    newinode->di_size = 3*(DIRSIZ+2);
    if(dineodeid == 3)
        newinode->di_size = BLOCKSIZ;
    return newinode;
}

void iput(struct inode *pinode)    /*iput()*/
{
    long addr;
    unsigned int block_num;
    int i;

    if(pinode->i_count > 1){
        pinode->i_count--;
        return;
    }
    else{
        if(pinode->di_number!=0){
            addr = DINODESTART + pinode->i_ino*DINODESIZ;
            fseek(fd,addr,SEEK_SET);
            fwrite(&pinode->di_number,DINODESIZ,1,fd);
        }
        else{
            block_num = pinode->di_size/BLOCKSIZ;
            for(i = 0;i < block_num;i++)
            bfree(pinode->di_addr[i]);
            ifree(pinode->i_ino);
        }
        if(pinode->i_forw == NULL)
            pinode->i_back->i_forw = NULL;
        else{
            pinode->i_forw->i_back = pinode->i_back;
            pinode->i_back->i_forw = pinode->i_forw;
        }
        ifree(pinode->i_ino);
    }
}