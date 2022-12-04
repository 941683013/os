#include <linux/module.h>
#include "stdio.h"

#define BLOOKSIZ 512
#define BLOCKSIZ 512
#define SYSOPENFILE 40
#define DIRNUM 128
#define DIRSIZ 14
#define PWDSIZ 12
#define PWDNUM 32
#define NOFILE 20
#define NADDR 10
#define NHINO 128
#define USERNUM 10
#define DINODESIZ 32

/* filsys */
#define DINODEBLK 32
#define FILEBLK 512
#define NICFREE 50
#define NICINOD 50
#define DINODESTART 2 * BLOOKSIZ
#define DATASTART (2+DINODEBLK) * BLOOKSIZ

/* di_mode */
#define DIEMPTY 0000
#define DIFILE 01000
#define DIDIR 02000
#define UDIREAD 00001 /* user */
#define UDIWRITE 00002
#define UDIEXICUTE 00004
#define GDIREAD 00010 /* group */
#define GDIWRITE 00020
#define GDIEXICUTE 00040
#define ODIREAD 00100 /* other */
#define ODIWRITE 00200
#define ODIEXICUTE 00400
#define READ 1
#define WRITE 2
#define EXICUTE 4
#define DEFAULTMODE 00777

/* i_flag */
#define IUPDATE 00002

/* s_fmod */
#define SUPDATE 00001

/* f_flag */
#define FREAD 00001
#define FWRITE 00002
#define FAPPEND 00004

/* error */
#define DISKFULL 65535

/* fseek origin */
#define SEEK_SET 0

/* null  NULL*/
#define null NULL

struct inode{
	struct inode * i_forw;
	struct inode * i_back;
	char i_flag;
	unsigned int i_ino;
	unsigned int i_count;
	unsigned short di_number;
	unsigned short di_mode;
	unsigned short di_uid;
	unsigned short di_gid;
	unsigned int di_size;
	unsigned int di_addr[NADDR];
};

struct dinode{
	unsigned short di_number;
	unsigned short di_mode;
	unsigned short di_uid;
	unsigned short di_gid;
	unsigned long di_size;
	unsigned int di_addr[NADDR];
};

struct direct{
	char d_name[DIRSIZ];
	unsigned int d_ino;
};

struct filsys{
	unsigned short s_isize;
	unsigned long s_fsize;
	unsigned int s_nfree;
	unsigned short s_pfree;
	unsigned int s_free[NICFREE];
	unsigned int s_ninode;
	unsigned short s_pinode;
	unsigned int s_inode[NICINOD];
	unsigned int s_rinode;

	char s_fmod;
};

struct pwd{
	unsigned short p_uid;
	unsigned short p_gid;
	char password[PWDSIZ];
};

struct dir{
	struct direct direct[DIRNUM];
	int size;
};

struct hinode{
	struct inode * i_forw;
};

struct file {
	char f_flag;
	unsigned int f_count;
	struct inode * f_inode;
	unsigned long f_off;
};

struct user{
	unsigned short u_default_mode;
	unsigned short u_uid;
	unsigned short u_gid;
	unsigned short u_ofile[NOFILE];
};

extern struct hinode hinode[NHINO];
extern struct dir dir;
extern struct file sys_ofile[SYSOPENFILE];
extern struct filsys filsys;
extern struct pwd pwd[PWDNUM];
extern struct user user[USERNUM];
extern FILE * fd;
extern struct inode * cur_path_inode;
extern int user_id,file_block;

/* proptype of the sub routine used in the file system */
extern struct inode * iget(unsigned int dineodeid);
extern void iput(struct inode *pinode);
extern unsigned int balloc();
extern void bfree(unsigned int block_num);
extern struct inode * ialloc();
extern void ifree(unsigned dinodeid);
extern unsigned int namei(char *name);
extern unsigned int iname(char *name);
extern unsigned int access(unsigned int user_id, struct inode * inode, unsigned short mode);
extern void _dir();
extern void mkdir(char * dirname);
extern void chdir(char * str);
extern void dirlt(int j);
extern unsigned short open(int user_id, char * filename,  unsigned short openmode);
extern unsigned short create(unsigned int user_id, char *filename, unsigned short mode);
extern unsigned int read(int fd1, char *buf, unsigned int size);
extern unsigned int write(int fd1, char *buf, unsigned int size);
extern int login(unsigned short uid, char * passwd);
extern int logout(unsigned short uid);
extern void install();
extern void format(struct inode * inode);
extern void close(unsigned int user_id, unsigned short cfd);
extern void halt();
extern void delete(char *filename);