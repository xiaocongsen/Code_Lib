#include"../include.h"
int main(int argc, char *argv[])
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1)
	{
		perror("socket create");
		return -1;
	}
	struct sockaddr_in addr;
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(9999);
	int ret = bind(sockfd, (struct sockaddr *) &addr, sizeof(addr));
	if(ret == -1)
	{
		perror("bind create");
		return ret;
	}
	listen(sockfd, 20);
	int size = 2048;
	int epfd = epoll_create(size);
	if(epfd == -1)
	{
		perror("epoll create");
		return epfd;
	}
	int op = EPOLL_CTL_ADD;
	struct epoll_event event;
	event.events = EPOLLIN;
	event.data.fd = sockfd;
	ret = epoll_ctl(epfd, op, sockfd, &event);
	if(ret == -1)
	{
		perror("epoll_ctl error");
		return ret;
	}
	while(1)
	{
		struct epoll_event ev[1024];
		int nready = epoll_wait(epfd, ev, 1024, 1000);  //(-1 阻塞监听)
		if(nready <= 0)
			continue;
		for(int i = 0; i < nready; ++i)
		{
				if(ev[i].data.fd == sockfd)
				{
					struct sockaddr_in connectaddr;
					socklen_t len = sizeof(connectaddr);
					int fd_connect = accept(sockfd, (struct sockaddr*)&connectaddr, &len);
					char buf[32] = { 0 };
					inet_ntop(AF_INET, &connectaddr.sin_addr, buf, sizeof(buf));
					printf("ev[%d] = %s, %d\n", nready, buf, ntohs(connectaddr.sin_port));
					event.events = EPOLLIN;
					event.data.fd = fd_connect;
					epoll_ctl(epfd, op, fd_connect, &event);
				}
				else
				{
					char buf[1024] = { 0 };
					read(ev[i].data.fd, buf, sizeof(buf));
					if(read <= 0)
					{
						close(ev[i].data.fd);
						printf("close\n");
						continue;
					}
					printf("ev[%d] = %d", i, nready);
				}
		}
	}
}
