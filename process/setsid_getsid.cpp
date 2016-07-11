#include<stdio.h>
#include<unistd.h>

int main()
{
	pid_t pid = fork();
	if(pid == 0)
	{
		pid_t pit = getsid(pid); //获取子进程的组长id;
		printf("z q 会话 %d\nfpid %d\n", pit, getppid());
		pit = setsid(); //子进程自己新建一个组，当组长;脱离父进程的组
		printf("z h 会话 %d\nfpid %d\n", pit, getppid());
		sleep(100);
		return 0;
	}
	else
	{
		pid_t pit = getsid(pid); //父进程获得组长信息；
		printf("f q 会话 %d\nffpid %d\n", pit, getppid());
		pit = setsid(); //父进程已经是组长，所以返回-1设置失败
		printf("f h 会话 %d\nffpid %d\n", pit, getppid());
		sleep(2);
	}
	return 0;
}
