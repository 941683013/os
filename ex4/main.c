#include<string.h>
#include<stdio.h>
#include"filesys.h"
#include"malloc.h"

struct hinode hinode[NHINO];

struct dir dir;
struct file sys_ofile[SYSOPENFILE];
struct filsys filsys;
struct pwd pwd[PWDNUM];
struct user user[USERNUM];
FILE * fd;
struct inode * cur_path_inode;
int user_id,file_block;

int main() {
	unsigned short ab_fd1,ab_fd2,ab_fd3,ab_fd4;
	unsigned short bhy_fd1;
	char * buf;

	printf("\nDo you want to format the disk?\n");
	if(getchar() == 'y')
	{
		printf("Format will erase all context on the disk.Are you sure?\n");
		getchar();
	}
	else
	 	return 0;
	if(getchar() == 'y') {
		format(cur_path_inode);
	}
		
	else 
		return 0;

	install();
	_dir();
	login(2118,"abcd");
	user_id=0;
	mkdir("a2118");
	chdir("a2118");
	ab_fd1=create(user_id,"file0.c",01777);
	file_block=BLOOKSIZ * 6 + 5;
	buf = (char *)malloc(BLOCKSIZ * 6 + 5);
	write(ab_fd1,buf,BLOOKSIZ * 6 + 5);
	close(user_id,ab_fd1);
	free(buf);

	mkdir("subdir");
	chdir("subdir");
	ab_fd2=create(user_id,"file1.c",01777);
	file_block=BLOOKSIZ*4+20;
	buf=(char*)malloc(BLOOKSIZ*4+20);
	write(ab_fd2,buf,BLOOKSIZ*4+20);
	close(user_id,ab_fd2);
	free(buf);

	chdir("..");
	ab_fd3=create(user_id,"file2.c",01777);
	file_block=BLOOKSIZ * 3 + 255;
	buf = (char * )malloc(BLOOKSIZ * 3 + 255);
	write(ab_fd3,buf,BLOCKSIZ * 3 + 255);
	close(user_id,ab_fd3);
	free(buf);

	_dir();
	delete("ab_file0.c");

	ab_fd4=create(user_id,"file3.c",01777);
	file_block=BLOCKSIZ*8+300;
	buf=(char *)malloc(BLOCKSIZ * 8 + 300);
	write(ab_fd4,buf,BLOCKSIZ * 8 + 300);
	close(user_id,ab_fd4);
	free(buf);

	_dir();
	ab_fd3=open(user_id,"file2.c",FAPPEND);
	file_block=BLOCKSIZ * 3 + 100;
	buf=(char*)malloc(BLOCKSIZ * 3 + 100);
	write(ab_fd3,buf,BLOCKSIZ * 3 + 100);
	close(user_id,ab_fd3);
	free(buf);

	_dir();
	chdir("..");
	logout(user_id);
	halt();
}