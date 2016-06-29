#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
int main()
{
	const char *pathname = "./open"; //路径
	int flags = O_RDONLY;		//只读方式打开；
	int fg = open(pathname, flags);//打开文件
	if(fg < 0)
	{
		perror("open error");
		return -1;
	}
	printf("open success");
	close(fg);//关闭文件
	return 0;
}
