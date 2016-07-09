#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<signal.h>
#include<fcntl.h>
#include<string.h>
#include<sys/wait.h>
int main()
{
	const char *pathname_r = "./r.fifo";
	int mode = 0777;
	const char *pathname_w = "./w.fifo";
	mkfifo(pathname_w, mode); //创建一个写数据的管道
	mkfifo(pathname_r, mode); //创建一个读数据的管道；
	int fd_r = open(pathname_r, O_RDONLY); //只读打开读数据的管道
	if(fd_r < 0)
	{
		perror("open_r error");
		return fd_r;
	}
	int fd_w = open(pathname_w, O_WRONLY); //只写打开写数据的管道
	if(fd_w < 0)
	{
		perror("open_w error");
		return fd_r;
	}
	pid_t pid = fork();
	if(pid == 0)
	{
		int i = 0;
		while(1)
		{
			char buf[1024] = { 0 };
			printf("%d\n", i++);
			int ret = read(fd_r, buf, sizeof(buf)); //往读数据的管道读
			if(ret == 0)
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
			printf("%s",buf);
		}
	}
	else
	{
		while(1)
		{
			char buf[1024] = { 0 };
			fgets(buf, sizeof(buf), stdin);
			if(strcmp(buf, "exit\n") == 0)
				break;
			write(fd_w, buf, sizeof(buf));//往写数据的管道写
		}
		kill(pid, SIGKILL); //结束干掉子进程
		usleep(1000);
		waitpid(pid, NULL, WNOHANG);// 不阻塞调用,回收子进程；
	}
	close(fd_w); //关闭文件
	close(fd_r);
	unlink(pathname_r); //删除文件
	unlink(pathname_w);
	return 0;
}
