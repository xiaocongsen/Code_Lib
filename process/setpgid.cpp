#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
	pid_t pid = fork();  //fuck出一个子进程
	if(pid != 0)
	{
		usleep(1000*100); //休息一会等子进程打印完成
		setpgid(pid, pid);//设置子进程的组id;
		usleep(1000*180);//在休息一会等待子进程打印修改后的效果
		printf("父getpid %d\n", getpid());//打印父进程的pid
		printf("父getppid %d\n", getppid());//打印父进程的父进程pid
		printf("父getgpid %d\n", getpgid(getpid()));//打印组id;
		setpgid(getpid(),getppid()); //设置父进程的组id为父进程的父进程的组id
		printf("父getpgid %d\n", getpgid(getpid()));//打印

	}
	else
	{
		printf("子getpid %d\n", getpid()); //打印子进程pid
		printf("子getppid %d\n", getppid());//打印子进程的父进程pid
		printf("子getpgid %d\n", getpgid(getpid()));//打印组id
		usleep(1000*200);
		printf("子getpgid %d\n", getpgid(getpid())); //打印修改后的组id
		exit(34);
	}
	int status;
	wait(&status);
	printf("%d", WEXITSTATUS(status));	
	return 0;
}
