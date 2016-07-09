#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>

int main()
{
	const char* r_path = "./r.fifo";
	const char* w_path = "./w.fifo";
	int fd_w = open(r_path, O_WRONLY); //因为send程序先打开的r.fifo的写
	int fd_r = open(w_path, O_RDONLY);//因为send程序先打开的w.fifo的读
	if(fd_w == -1 | fd_r == -1)
	{
		perror("fopen error");
		return -1;
	}
	pid_t pid = fork();
	if(pid == 0)
	{
		while(1)
		{
			char buf[1024] = { 0 };
			int ret = read(fd_r, buf, sizeof(buf));  
			if(ret == 0)     //如果对方关闭管道 ret 等于0
			{
				printf("对方已经关闭");
				return -1;
			}
			else if(ret < 0)
			{
				perror("read error");
				return ret;
			}
			else
			printf("%s", buf);
		}
	}
	else
	{
		while(1)
		{
			char buf[1024] = { 0 };
			fgets(buf, sizeof(buf), stdin);
			write(fd_w, buf, sizeof(buf));
		}
	}
	close(fd_r);
	close(fd_w);
	return 0;
}
