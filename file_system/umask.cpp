#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
int main()
{
	mode_t mask = 0444; //设置掩码屏蔽read权限， 0222(屏蔽write权限),0111(屏蔽所以的EXEC权限)
	umask(mask); 
	const char *pathname = "hello.d";
	unlink(pathname); //删除文件；
	int flags = O_RDWR | O_CREAT;
	mode_t mode = 0777;
	int fd = open(pathname, flags, mode);
	close(fd);
	struct stat buf;
	stat(pathname, &buf); //获取文件属性
	if((buf.st_mode & 00000777) == mode) //对比文件真实属性和设置属性是否一至，抹去文件属性位
	{
		printf("umask没成功,实际%o\n", buf.st_mode & 00000777);
	}
	else
	{
		printf("是umask干的,实际%o\n", buf.st_mode & 00000777);
	}
	return 0;
}
