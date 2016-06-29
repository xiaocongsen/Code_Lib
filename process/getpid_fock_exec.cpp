#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main()
{
	gid_t gid = getgid();//实际用户主
	gid = getegid();
	pid_t pid = getppid();
	printf("主程序的父的pid = %d\n",gid);
	pid = getpid();
	printf("主程序的pid = %d\n",gid);
	gid = fork();
	printf("fork 返回值的pid = %d\n",gid);
	if(pid == 0)
	{
		pid = getpid();
		printf("pid == 0分支的pid = %d\n",gid);
	}
	else
	{
		pid = getpid();
		printf("pid != 0分支的pid = %d\n",gid);
	}
}
