#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>
int main()
{
	int filedes[2]; //创建2个文件描述符
	int ret = pipe(filedes);//创建管道；
	if(ret != 0)
	{
		perror("perror error"); 
		return ret; 
	} 
	int flags = fcntl(filedes[0], F_GETFL);//获取文件描述符属性 注意是F_GETFL
	flags |= O_NONBLOCK;    //添加不阻塞属性
	fcntl(filedes[0], F_SETFL, flags); //设置不阻塞属性；
//	flags = fcntl(filedes[1], F_GETFL); 
//	flags |= O_NONBLOCK;
//	fcntl(filedes[1], F_SETFL, flags);
	pid_t pid = fork();
	if(pid == 0)
	{
		close(filedes[1]); //关闭标准输出 写端
		while(1)
		{
			char buf[1024] = { 0 };
			ret = read(filedes[0], buf, sizeof(buf)); //读取管道
			printf("%d\n", ret);
			if( ret == 0)
			{
				printf("对方关闭");
				return -1;
			}
			else if(ret < 0)
			{
				if(errno == EAGAIN)  //如果是非阻塞引起的错误继续
				{
					printf("jixu\n");
					sleep(1);
					continue;
				}
				perror("read error");
				return ret;
			}
			printf("%s", buf);
		}
	}
	else
	{
		close(filedes[0]);//关闭标准输入， 读端
		while(1)
		{
			char buf[1024] = { 0 };
			fgets(buf, sizeof(buf), stdin);  
			if(strcmp(buf, "exit\n") == 0)
				break;
			ret = write(filedes[1], buf, sizeof(buf));  //往管道写数据，
			if(ret < 0)
			{
				if(errno == EAGAIN) //如果是非阻塞引起的错误eagain
				{
					continue;
				}
				perror("write error");
				return ret;
			}
		}
	}
}
