#include<stdio.h>
#include<sys/stat.h>
#include<string.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
int main()
{
	const char *pathname = "/dev/tty";
	int flags = O_RDONLY | O_NONBLOCK;   //O_NONBLOCK  不阻塞方式打开文件,对文件使用阻塞函数时，会返回一个错误EAGAIN; 不是真正的错误！
	int fd = open(pathname, flags);
	if(fd < 0)
	{
		perror("open error");
		return -1;
	}
	else
	{
		int index = 0;
		char buf[2048] = { 0 };
flags:		int n = read(fd, buf, sizeof(buf));	
		int tmp_fd = STDOUT_FILENO;
		if( n < 0)
		{
			if(errno != EAGAIN)    //判断文件是不是由于非阻塞导致返回的EAGAIN
			{
				perror("open error");
				return 0;
			}
			else
			{
				index++;
				sleep(1);
				const char *tmp = "try argin\n";
				size_t count = strlen(tmp);
				write(tmp_fd, tmp, count);
				if(index >= 5)
				{
					printf("timeout\n");
				}
				else
				goto flags;
			}
		}
		else
		{
			write(tmp_fd, buf, strlen(buf)); 
		}
		close(fd);
	}
}
