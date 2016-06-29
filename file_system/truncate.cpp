#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{
	const char* pathname = "./hello.d";
	int fd = open(pathname, O_RDONLY|O_TRUNC); //O_TRUNC 截断方式open，这样就清空了文件里所以东西
	if(fd < 0)
	{
		perror("open error");
		return -1;
	}
	else
	{
		off_t length = 40000;			
		if(truncate(pathname, length))	//产生一个指定大小的文件，可长于原文件，可短于原文件；
		{
			return -2;   //如果-2则结束；
		}
	}
	close(fd);
	return 0;
}
