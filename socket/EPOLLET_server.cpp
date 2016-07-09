#include"../include.h"
int set_nonblock(int fd)
{
	int flags = fcntl(fd, F_GETFL);
	flags |= O_NONBLOCK;
	fcntl(fd, F_SETFL, flags);
	return 0;
}
int main()
{
	//	domain	 type	     protocol
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		perror("socket error");
		return sockfd ;
	}
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9999);
	addr.sin_addr.s_addr = htonl(0);
	int ret = bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
	if(ret < 0)
	{
		perror("bind error");
		return ret ;
	}
	int backlog = 5;
	ret =listen(sockfd, backlog);
	if(ret < 0)
	{
		perror("listen error");
		return ret ;
	}
	int epfd = epoll_create(1024);
	if(epfd < 0)
	{
		perror("epoll_create error");
		return epfd;
	}
	struct epoll_event ev;
	ev.events = EPOLLIN | EPOLLET;
	epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &ev);
	set_nonblock(sockfd);
	while(1)
	{
		struct epoll_event ev2[8]; 
		ret = epoll_wait(epfd, ev2, 8, 5000);
		if(ret > 0)
		{
			for(int i = 0; i < ret; ++i)
			{
				if(ev2[i].data.fd == sockfd)
				{
					while(1)
					{
						int newfd = accept(sockfd, NULL, NULL);
						if(newfd < 0)
						{
							if(errno == EAGAIN || errno == EINTR)
							{
								break;
							}
							perror("accept error");
							return -1;
						}
						set_nonblock(newfd);
						printf("hello nonblock\n");
					}
				}
			}	
		}
	}
	return 0;
}
