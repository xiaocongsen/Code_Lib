#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
void handler(int){}
void fun(int)
{
	printf("nihao\n");
}
int main()
{
	alarm(2); //定时，到时间后回收到SIGALRM信号， 默认是终止程序；
	int a[100] = { 0 };
	for(int i = 0; i < 100; ++i)
	{
		a[i] = i;
	}
	signal(SIGUSR1,handler); //注册一个SIGUSR1信号的处理函数;
	pid_t pid = fork();
	int i = 0;
	if(pid == 0)
	{
		while(i < 99)
		{
			sleep(1);  //子进程接收到信号，处理对应的信号函数后,sleep已经失效；则继续执行下面的函数；
			i++;
			if(i % 2 != 0)
				i++;
			if(i > 99)
				return 0;	
			printf("pid = %d ：%d\n",getpid(),a[i]);
		}
	}
	else
	{
		pid_t pid2 = fork();
		if(pid2 == 0)
		{
			while(1)
				abort(); //杀死自己；
		}
		else
		{
			while(i < 99)
			{
				kill(pid,SIGUSR1); //父进程发生信号给子进程；
				i++;
				if(i % 2 == 0)
					i++;
				usleep(1000);
				printf("pid = %d ：%d\n",getpid(),a[i]);
			}
		}
		signal(SIGUSR2, fun);//注册一个SIGUSR2信号；
		waitpid(pid, NULL, 0);//等待pid子进程死亡
		waitpid(pid2, NULL, 0);//等待pid2子进程死亡；
		while(1)
		{
			raise(SIGUSR2); //给自己发送SIGUSR2信号；
			usleep(100000);
		}
	}
	return 0;
}
