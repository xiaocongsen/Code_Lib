#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{
	const char *pathname = "hello.d";
	int flags = O_WRONLY | O_CREAT;
	mode_t mode = 0777;
	unlink(pathname);
	int fd = open(pathname, flags, mode);
	if(fd < 0)
	{
		perror("open hello.d error");
		return -1;
	}
	else
	{
		off_t offset = 4095;// 偏移量为0；
		int whence = SEEK_END;   //从文件结尾处开始偏移 SEEK_SET(文件开头)   SEEK_CUR(当前位置)
//		off_t lseek(int fd, off_t offset, int whence);   //lseek的原型
		lseek(fd, offset, whence); //移动到4095大小的位置；
		write(fd,"a",1); //写入1个字符；
		offset = lseek(fd, 0, SEEK_END);
		printf("%ld", offset);  //返回值打印为偏移开始位置的大小
	}
	close(fd);
	return 0;
}
