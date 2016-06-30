#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main()
{
	gid_t gid1 = getgid();//实际用户组id
	printf("主程序的实际gid = %d\n",gid1);
	gid_t gid = getegid();  //有效用户组id
	printf("主程序的有效gid = %d\n",gid);
	pid_t pid = getppid();
	printf("主程序的父的pid = %d\n",pid);
	pid = getpid();
	printf("主程序的pid = %d\n",pid);
	pid = fork();
	printf("fork 返回值的pid = %d\n",pid);
	if(pid == 0)
	{
		pid = getpid();
		printf("的pid == %d\n",pid);
		gid_t gid = getgid();//实际用户组id
		printf("pid == 0分支的实际gid = %d\n",gid);
		gid = getegid();  //有效用户组id
		printf("pid == 0分支的有效gid = %d\n",gid);
	}
	else
	{
		sleep(1);
		pid = getpid();
		printf("pid != 0分支的pid = %d\n",pid);
	}
}
