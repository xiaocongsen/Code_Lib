#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main()
{
	pid_t pid = fork();
	if(pid == 0)
	{
		setsid(); //独立门户 成为组长;
		chdir("/"); //更换工作目录
		umask(0); //设置umask码
		close(0);//关闭标准输入
		open("/dev/null", O_RDWR); //打开null设备文件 文件描述符为0；
		dup2(0, 1); //重定义文件描述符到0号
		close(1); 
		dup2(0, 2); //重定义文件描述符到0号
		sleep(100);
	}
	else
		return 0;
	return 0;
}
