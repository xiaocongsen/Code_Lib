#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{
	const char *pathname = "hello.d";
	mode_t mode = 0770;
	chmod(pathname, mode); //不受umask影响；
/*	int fd = open(pathname, O_RDONLY);
	fchmod(fd, mode);	//用文件描述符时用这个函数
	close(fd);
*/	return 0;
}
