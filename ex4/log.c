#include<stdio.h>
#include"filesys.h"
#include "string.h"

int login(unsigned short uid, char * passwd)
{
	int i ,j;

	for(i=0; i<PWDNUM; i++)
	{
		if((uid==pwd[i].p_uid)&&!(strcmp(passwd,pwd[i].password)))
		{
			for(j=0;j<USERNUM;j++)
				if(user[j].u_uid==0)
					break;
				if(j==USERNUM)
				{
					printf("\ntoo much user in the system,waited to login\n");
					return 0;
				}
				else
				{
					user[j].u_uid=uid;
					user[j].u_uid=pwd[i].p_gid;
					user[j].u_default_mode=DEFAULTMODE;
				}
				break;
		}
	}
	if(i==PWDNUM)
	{
		printf("(\nincorrect password,Login Failure!\n");
		return 0;
	}
	else
	{
		printf("Login Success!%d's user id is %d\n",uid,j);
		return 1;
	}
}
int logout(unsigned short uid)
{
	int i,j,sys_no;
	struct inode *inode;
	
	for(i=0;i<USERNUM;i++)
		if(uid==user[i].u_uid)
			break;
	if(i==USERNUM)
	{
	printf("\nno such a file\n");
	return 0;
	}
	for(j=0;j<NOFILE;j++)
	{
		if(user[i].u_ofile[j]!=SYSOPENFILE+1)
		{
		sys_no=user[i].u_ofile[j];
		inode=sys_ofile[sys_no].f_inode;
		iput(inode);
		sys_ofile[sys_no].f_count--;
		user[i].u_ofile[j]=SYSOPENFILE+1;
	}
}
printf("no user in the file system \n");
return 1;
}