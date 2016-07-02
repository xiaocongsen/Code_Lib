#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
int main()
{
	int domain = AF_INET; //协议族
	int type = SOCK_STREAM;
	int protocol = 0;
	int fd = socket(domain, type, protocol);
	if(fd < 0)
	{
		perror("socket creat error");
		return fd;
	}
	else
	{
		int sockfd = fd;
		struct sockaddr_in addr;
		addr.sin_family = AF_INET;  //协议族
		addr.sin_port = htons(19999);
		addr.sin_addr.s_addr = 0;
		socklen_t addrlen = sizeof(addr);
		int ret = bind(sockfd, (struct sockaddr*)&addr, addrlen);
		if(ret == -1)
		{
			perror("bind error");
			return ret; 
		}
		else
		{
			int backlog = 5; //缓存区最大等来链接数量;
			ret = listen(sockfd, backlog);
			if(ret == -1)
			{
				perror("listen error");
				return ret;	
			}
			else
			{	
				struct sockaddr_in client_addr;
				socklen_t len = sizeof(addr);
				int fd_client = accept(sockfd, (struct sockaddr*)&client_addr, &len);
				if(fd_client < 0)
				{
					perror("accept error");
					return fd_client;
				}
				else 
				{
					pid_t pid = fork();
					if(pid == 0)
					{
						while(1)
						{
							char buf[1024] = { 0 };
							ret = read(fd_client, buf, sizeof(buf));
							if(ret < 0)
							{
								perror("read error");
								kill(getppid(), SIGKILL);
								return ret;
							}
							else if(ret == 0)
							{
								printf("%s: 已经离开\n",inet_ntoa(client_addr.sin_addr));
								kill(getppid(), SIGKILL);
								break;
							}
							else
								printf("%s: %s",inet_ntoa(client_addr.sin_addr),buf);
						}
					}
					else
					{
						while(1)
						{
							char buf[1024] = { 0 };
							fgets(buf, sizeof(buf), stdin);
							//system("clear");
							ret = write(fd_client, buf, sizeof(buf));
							if(ret < 0)
							{
								perror("wriet error");	
								kill(pid, SIGKILL);
								return ret;
							}
						}
					}
					close(fd_client);
				}

			}
		}
	}
	close(fd);
}
