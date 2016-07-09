#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main()
{
	gid_t gid1 = getgid();//实际用户组id
	printf("主程序的实际gid = %d\n",gid1);
	gid_t gid = getegid();  //有效用户组id
	printf("主程序的有效gid = %d\n",gid);
	uid_t uid = getgid();//实际用户id
	printf("主程序的实际uid = %d\n",uid);
	uid = getegid();  //有效用户id
	printf("主程序的有效uid = %d\n",uid);
	pid_t pid = getppid();	//活动父进程pid;
	printf("主程序的父的pid = %d\n",pid);
	pid = getpid(); //活动当前进程的pid;
	printf("主程序的pid = %d\n",pid);
	pid = fork(); //创建子进程
	printf("fork 返回值的pid = %d\n",pid);
	if(pid == 0)
	{
		pid = getpid();//获得子进程的pid
		printf("子进程的pid == %d\n",pid);
		pid = getppid(); // 获得父进程的pid
		printf("子进程的父进程pid == %d\n",pid);
		gid_t gid = getgid();//实际用户组id
		printf("子进程的实际gid = %d\n",gid);
		gid = getegid();  //有效用户组id
		printf("子进程的有效gid = %d\n",gid);
	}
	else
	{
		sleep(1);
		printf("父进程子进程的pid = %d\n",pid);
		pid = getpid();
		printf("父进程的pid = %d\n",pid);
	}
}
