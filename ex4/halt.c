#include <stdio.h>
#include "filesys.h"
#include"stdlib.h"
void halt() {
    struct inode *inode;
    int i, j;
    // 1.write back the current dir
    chdir("..");
    iput(cur_path_inode);
    // 2.free the u_ofile and sys_ofile and inode
    for (i = 0; i < USERNUM; i++)
    {
        if (user[i].u_uid != 0)
        {
            for (j = 0; j < NOFILE; j++)
            {
                if (user[i].u_ofile[j] != SYSOPENFILE + 1)
                {
                    close(i, j);
                    user[i].u_ofile[j] = SYSOPENFILE + 1;
                }
            }
        }
    }
    // 3.write back the filsys to the disk
    fseek(fd, BLOOKSIZ, SEEK_SET);
    fwrite(&filsys, 1, sizeof(struct filsys), fd);
    // 4.close the file system colum
    fclose(fd);
    // 5.say GOODBYE to all the user
    printf("\n Goodbye. See you Next Time. Please turn off the switch\n");
    exit(0);
}
