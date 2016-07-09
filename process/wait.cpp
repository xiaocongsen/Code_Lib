#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
int main()
{
	int a = 10;
	int b = 20;
	int num = 0;
	pid_t pid = fork();
	if(pid == 0)
	{
		sleep(1);
		return a*b+12;
	}
	else
	{
		num = a + b;	
		int status; //获得子进程的死亡状态;
		int pr = wait(&status);  //返回值pr 为子进程的pid号
		if(!WIFEXITED(status)) //如果是正常退出则条件成立
			printf("我被杀死的");
		else
		{
			int p = WEXITSTATUS(status); //如果是正常退出,可wexitstatus获得子进程的返回值
			printf("我老死的%d, pr = %d, %d", p, pr,pid);
		}
		num = p + a + b;
	}
	return 0;
}
