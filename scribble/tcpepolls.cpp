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
#include<sys/epoll.h>
int main()
{
	int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(sock_fd < 0)
	{
		perror("socket error");
		return sock_fd;
	}
	int sockfd_s = epoll_create(1024);
	struct epoll_event event;
	event.events = EPOLLIN;
	event.data.fd = sock_fd;
	epoll_ctl(sockfd_s, EPOLL_CTL_ADD, sock_fd, &event);
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
	while(1)
	{
		struct epoll_event newevents[1024];
		int num = epoll_wait(sockfd_s, newevents, 1024, 1000*100);
		if(num < 0)
		{
			perror("epoll_wait error");
			return num;
		}
		pid_t pid = fork();
		if(pid == 0)
		{ 
			for(int i = 0 ; i < num; i++)
			{
				struct sockaddr_in cliaddr;
				socklen_t len = sizeof(cliaddr);
				if(newevents[i].data.fd == sock_fd)
				{
					int newfd = accept(sock_fd, (struct sockaddr*)&cliaddr, &len);
					if(newfd < 0)
					{
						perror("access error");
						return newfd;
					}
					event.events = EPOLLIN;
					event.data.fd = newfd;
					epoll_ctl(sockfd_s, EPOLL_CTL_ADD, newfd, &event);

					printf("添加成功%d\n", newfd);
				}
				else
				{
					while(1)
					{
						char buf[1024] = { 0 };
						ret = read(newevents[i].data.fd, buf, sizeof(buf));
						if(ret <= 0)
						{
					//		printf("ip = %s fd = %d已经断开连接\n", inet_ntoa(cliaddr.sin_addr), newevents[i].data.fd);
							close(newevents[i].data.fd);
							return ret;
						}
						printf("ip = %s, buf = %s", inet_ntoa(cliaddr.sin_addr), buf); 
					}
				}
			}
		}
	}
}
