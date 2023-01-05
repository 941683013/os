#include <linux/module.h>
#include "stdio.h"

//filesys.h 定义本文件系统中的数据结构和常数
//filesys. h 定义本文件系统中的数据结构和常数
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
//filsys
#define DINODEBLK 32
#define FILEBLK 512
#define NICFREE 50
#define NICINOD 50
#define DINODESTART 2*BLOCKSIZ
#define DATASTART (2+DINODEBLK) *BLOCKSIZ
//di_mode
#define DIEMPTY 0000
#define DIFILE 01000
#define DIDIR 02000
#define UDIREAD 00001 //user
#define UDIWRITE 00002
#define UDIEXICUTE 00004
#define GDIREAD 00010 //group
#define GDIWRITE 00020
#define GDIEXICUTE 00040
#define ODIREAD 00100 //other
#define ODIWRITE 00200
#define ODIEXECUTE 00400
#define READ 1
#define WRITE 2
#define EXECUTE 4
#define DEFAULTMODE 00777
//I_flag
#define IUPDATE 00002
//s_fmod
#define SUPDATE 00001
//f_flag
#define FREAD 00001
#define FWRITE 00002
#define FAPPEND 00004
//error
#define DISKFULL 65535
//fseek origin
#define SEEK_SET 0
//文件系统数据结构
struct inode{
struct inode *i_forw;
struct inode *i_back;
char i_flag;
unsigned int i_ino; //磁盘 i 节点标志
unsigned int i_count; //引用计数
unsigned short di_number; //关联文件数, 当为 0
unsigned short di_mode; //存取权限
unsigned short di_uid;
unsigned short di_gid;
unsigned int di_size; //文件大小
unsigned int di_addr[NADDR] ; //物理块号
} ;
struct dinode{
unsigned short di_number; //善关联文件数铃/
unsigned short di_mode; //存取权限祷/
unsigned short di_uid;
unsigned short di_gidp;
unsigned long di_size; //文件大小
unsigned int di_addr[NADDR] ; //祷物理块号费/
} ;
struct direct{
char d_name[DIRSIZ] ;
unsigned int d_ino;
} ;
struct filsys{
unsigned short s_isize; //i 节点块块数
unsigned long s_fsize; //数据块块数
unsigned int s_nfree; //空闲块块数
unsigned short s_pfree; //空闲块指针
unsigned int s_free[NICFREE] ; //空闲块堆钱
unsigned int s_ninode; //空闲 i 节点数
unsigned short s_pinode; //空闲 i 节点指针
unsigned int s_inode[NICINOD]; //空闲 i 节点数组
 unsigned int s_rinode; //铭记 i 节点
char s_fmod; //超级块修改标志
} ;
struct pwd {
unsigned short p_uid;
unsigned short p_gid;
char password[PWDSIZ] ;
} ;
struct dir{
struct direct direct[DIRNUM] ;
int size; //当前目录大小
} ;
struct hinode{
struct inode *i_forw; //hash 表指针
} ;
struct file{
char f_flag; //文件操作标志
unsigned int f_count; //引用计数
struct inode *f_inode; //指向内存 i 节点
unsigned long f_off; //读/写指针
} ;
struct user {
unsigned short u_default_mode;
unsigned short u_uid;
unsigned short u_gid;
unsigned short u_ofile[NOFILE]; //用户打开文件表
} ;
//下为全局变量
extern struct hinode hinode[NHINO];
extern struct dir dir; //当前目录(在内存中全部读入)
extern struct file sys_ofile[SYSOPENFILE];
extern struct filsys filsys; //内存中的超级块
extern struct pwd pwd[PWDNUM];
extern struct user user[USERNUM];
extern FILE *fd; //the file system column of all the system
extern struct inode *cur_path_inode;
extern int user_id, file_block;
//proptype of the sub roution used in the file system
extern struct inode *iget(unsigned int dinodeid) ;
extern void iput(struct inode *pinode) ;
extern unsigned int balloc() ;
extern void bfree(unsigned int block_num) ;
extern struct inode *ialloc();
extern void ifree(unsigned dinodeid) ;
extern unsigned int namei(char *name);
extern unsigned int iname(char *name) ;
extern unsigned int access(unsigned int user_id,struct inode *inode,unsigned short mode) ;
extern void _dir();
extern void mkdir(char *dirname) ;
extern void chdir(char *dirname) ;
extern void dirlt(int j) ;
extern unsigned short open(int user_id,char *filename,unsigned short openmode) ;
extern unsigned short create(unsigned int user_id,char *filename,unsigned short mode) ;
extern unsigned int read(int fd1,char *buf,unsigned int size) ;
extern unsigned int write(int fd1,char *buf,unsigned int size) ;
extern int login(unsigned short uid,char *passwd) ;
extern int logout(unsigned short uid) ;
extern void install() ;
extern void format() ;
extern void close(unsigned int user_id,unsigned short cfd) ;
extern void halt() ;
extern void delete(char *filename) ;