#include<stdio.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<signal.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<arpa/inet.h>
#include<fcntl.h>
int main()
{
	int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(sock_fd < 0)
	{
		perror("socket error");
		return sock_fd;
	}
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9999);
	addr.sin_addr.s_addr = 0;
	int ret = bind(sock_fd, (struct sockaddr*)&addr, sizeof(addr));
	if(ret < 0)
	{
		perror("bind error");
		return 0;
	}
	listen(sock_fd, 5);
	struct sockaddr_in cliaddr;
	socklen_t len = sizeof(cliaddr);
	int newfd = accept(sock_fd, (struct sockaddr*)&cliaddr, &len);
	if(newfd < 0)
	{
		perror("access error");
		return newfd;
	}
	pid_t pid = fork();
		if(pid == 0)
		{ 
			while(1)
			{
				char buf[1024] = { 0 };
				ret = read(newfd, buf, sizeof(buf));
				if(ret <= 0)
				{
					perror("read error");
					kill(SIGKILL, getppid());
					return ret;
				}
				printf("ip = %s, buf = %s", inet_ntoa(cliaddr.sin_addr), buf); 
			}
		}
		else
		{
			while(1)
			{
				char buf[1024] = { 0 };
				fgets(buf, sizeof(buf), stdin);
				write(newfd, buf, sizeof(buf));
				if(write <= 0)
				{
					perror("write error");
						return 0;
				}
			}
		}
}
