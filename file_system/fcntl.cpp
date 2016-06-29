#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
int main()
{
	int flags = fcntl(STDIN_FILENO, F_GETFL);   //F_GETFL获得文件的flags
	flags |= O_NONBLOCK;		//添加文件标记属性到flags.
	if(fcntl(STDIN_FILENO,F_SETFL,flags) == -1)  //给文件设置新的flags；  如果返回值是-1代表设置失败
	{
		perror("fcntl set flags error");
		return -1;
	}
	else
	{
		char buf[2048] = { 0 };
		for(int i = 0; i < 5; ++i)
		{
			int byte_r = read(STDIN_FILENO, buf, sizeof(buf));
			if(byte_r == -1)   //读取返回-1,代表失败；
			{
				if(errno == EAGAIN)   //错误码是eagain 为不阻塞错误；
				{
					sleep(1);
					printf("try argin\n");
					continue;
				}
				else
				{
					perror("read error");
					return -1;
				}
			}
			else
			{
				write(STDOUT_FILENO,buf,strlen(buf));	
				return 0;
			}
		}
		printf("timeout\n");
	}	
	return -2;
}
