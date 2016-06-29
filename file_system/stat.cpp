#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
int main()
{
	struct stat buf;
	const char *pathname = "hello.d";
	stat(pathname, &buf);	
	buf.st_mode = 0100700;
	buf.st_size = 1024;
	buf.st_blksize = 1024;
	buf.st_atime = 2017;
	printf("dev:%ld\n", buf.st_dev);
	if(S_ISREG(buf.st_mode) == 1)  //判断是否为普通文件；
	{	
		printf("我是普通文件\n");
	}
	printf("ino:%ld\n", buf.st_ino);
	printf("mode:%o\n", buf.st_mode);
	printf("nlink:%lu\n", buf.st_nlink);
	printf("uid:%d\n", buf.st_uid);
	printf("gid:%d\n", buf.st_gid);
	printf("rdev:%lu\n", buf.st_rdev);
	printf("size:%ld\n", buf.st_size);
	printf("blksize:%ld\n", buf.st_blksize);
	printf("atime:%ld\n", buf.st_atime);
	printf("mtime:%ld\n", buf.st_mtime);
	printf("ctime:%ld\n", buf.st_ctime);
	return 0;
}
/*
struct stat {
        dev_t st_dev; // ID of device containing file /
        ino_t st_ino; // inode number / inode号
        mode_t st_mode; // protection / 权限和文件类型，位图权限为9位,类型3位,u+s 1位,g+s 1位,粘滞位(T位)1位。  位图是用一位或几位数据表示某种状态。许多要解决看似>不可能的问题的面试题往往需要从位图着手。
        nlink_t st_nlink; // number of hard links /  硬链接数量
        uid_t st_uid; // user ID of owner /    文件属主ID
        gid_t st_gid; // group ID of owner /   文件属组ID
        dev_t st_rdev; // device ID (if special file) / 设备号,只有设备文件才有
        off_t st_size; // total size, in bytes / 总大小字节数，编译是需要指定宏-D_FILE_OFFSIZE_BITES=64,否则读取大文件可能导致溢出
        blksize_t st_blksize; // blocksize for file system I/O /系统文件块大小
        blkcnt_t st_blocks; // number of 512B blocks allocated / 每个block占用 512B,则整个文件占用的 block 数量。这个值是文件真正意义上所占用的磁盘空间
        // 下面三个成员都是大整数,实际使用时需要先转换
        time_t st_atime; // time of last access /  文件最后访问时间戳
        time_t st_mtime; // time of last modification / 文件最后修改时间戳
        time_t st_ctime; // time of last status change / 文件亚数据最后修改时间戳
};*/
