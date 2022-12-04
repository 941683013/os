#include<stdio.h>
#include "filesys.h"

unsigned short create(unsigned int user_id, char *filename, unsigned short mode) 
{    
                unsigned int di_ino, di_ith;
                struct inode * inode;
                int i,j;
                di_ino = namei(filename);
                if( di_ino != 0)
                {
                        inode = iget(di_ino);
                        if(access(user_id,inode,mode) == 0)
                        {                          iput(inode);
                                printf("\ncreate access not allowed");
                                return 0;                          
                        }
                for(i = 0; i < inode->di_size/BLOCKSIZ + 1; i ++)
                {
                        bfree(inode ->di_addr[i]);
                } 

               for(i = 0; i <SYSOPENFILE; i ++)
                       if(sys_ofile[i].f_inode == inode)
                                 sys_ofile[i].f_off = 0;
                
               for(i = 0; i <NOFILE; i ++)
                    if(user[user_id].u_ofile[i] == SYSOPENFILE + 1)
                 {
                            user[user_id].u_uid = inode ->di_uid;
                            user[user_id].u_uid = inode ->di_gid;
                                  for(j = 0; j < SYSOPENFILE ; j ++)
                                          if(sys_ofile[j].f_count == 0)
                                     {
                                                user[user_id].u_ofile[j] = j;
                                                sys_ofile[j].f_flag = mode;
}
                                           return i;
                                    }
           
}
                      
                               else{
                                     inode = ialloc();
                                     di_ith = iname(filename);
                                       
                                       dir.size ++;

                                      dir.direct[di_ith].d_ino = inode-> i_ino;
                                      dir.direct[di_ith +1].d_ino = 0;
                                      inode->di_mode = user[user_id].u_default_mode|DIFILE;
                                      inode->di_mode = user[user_id].u_uid;
                                      inode->di_mode = user[user_id].u_gid;
                                      inode->di_size = file_block;
                                      inode->di_number = 1;

                                      for(i = 0; i < SYSOPENFILE; i ++)
                                                if(sys_ofile[i].f_count == 0)
                                                             break;

                                                   for(j = 0 ; j <NOFILE ; j ++)
                                           if(user[user_id].u_ofile[j] ==SYSOPENFILE +1)
                                                             break;
                                                      user[user_id].u_ofile[j] = i;
                                                      sys_ofile[i].f_flag = mode;
                                                      sys_ofile[i].f_count = 0;
                                                      sys_ofile[i].f_off = 0;
                                                      sys_ofile[i].f_inode = inode;
                                       
                                                     return j;

 }

}