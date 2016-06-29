#include<stdio.h>
int main()
{
	char *pathname = "hello.d";
	mode = 0777;
	int flags = O_RDWR|O_CREAT;
	int fd = open(pathname,flags,mode);
	if(fg < 0)
	{
		perror("open error");
		return 0;
	}
	else
	{
		/*ssize_t write(int fd, const void *buf, size_t count); */
		const char buf[2048] = { 0 };
		size_t count = sizeof(buf);
		f
		write(fd, buf, count); 
	}
}
