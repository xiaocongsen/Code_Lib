#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
int main()
{
	const char *pathname = "./open";
	int flags = O_RDONLY;
	int fg = open(pathname, flags);
	if(fg < 0)
	{
		perror("open error");
		return -1;
	}
	printf("open success");
	return 0;
}
