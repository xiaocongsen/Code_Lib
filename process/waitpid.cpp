#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
int main()
{
	pid_t pid = fork();
	if(pid < 0)
	{
		perror("fork error");
		return -1;
	}
	if(pid == 0)
	{
		for(int i = 2; i  > 0; --i)
		{
			printf("this %d\n",i);
			sleep(1);
		}
		return 10;
	}
	else
	{
		int status;
		int flags = 1;
		while(flags)
		{
			int ret = waitpid(pid, &status, WNOHANG); //wnohang 不阻塞调用, 如果指定0,则默认阻塞；  status 填NULL 表示不需要返回值；
			/*	填：
				pid == 0  表示同一进程组中任何子进程消亡都处理;
				pid == -1 表示任何一个子进程消亡都处理
				pid为正 只等待子进程==pid的进程结束才处理；
				pid< -1		表示等待指定进程组的任何子进程结束；
			*/
			if(ret == 0) //没有任何子进程结束；
				printf("等子进程结束%d\n", ret);
			else if(ret < 0) //异常错误
			{
				perror("waitpid error");
				return ret;
			}	
			else   //子进程结束了；
			{
				printf("成功等到%d, return %d\n",ret , WEXITSTATUS(status)); //打印子进程号，和正常结束返回值；
				flags = 0;
			}
			usleep(100000);
		}
	}
}
