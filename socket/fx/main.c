#include "fx.h"

char *ipname[100] = { 0 };
void sockaddrinit(struct sockaddr_in *addr, char *ip)
{
	addr->sin_family = AF_INET;
	addr->sin_port = htons(19981);
	addr->sin_addr.s_addr = inet_addr(ip);
}

int mysend(int sock_fd, char *buf, char *ip)
{
	struct sockaddr_in addr;
	sockaddrinit(&addr, ip);
	int ret = sendto(sock_fd, buf, strlen(buf)+1, 0, (struct sockaddr*)&addr, sizeof(addr));
	if(ret == -1)
		perror("sendto error");
	return 0;
}

int init_socket()
{
	int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock_fd < 0)
	{
		perror("socket error");
		return sock_fd;
	}
	struct sockaddr_in addr;
	sockaddrinit(&addr, "0.0.0.0");
	int ret = bind(sock_fd, (struct sockaddr*)&addr, sizeof(addr));
	if(ret < 0)
	{
		printf("bind error\n");
		return 0;	
	}
	int optval = 1;
	ret = setsockopt(sock_fd, SOL_SOCKET, SO_BROADCAST, &optval, sizeof(optval));
	if(ret == -1)
		perror("setsockopt error");
	return sock_fd;
}

void son(int sock_fd)
{
	while(1)
	{
		char buf[1024] = { 0 };
		struct sockaddr_in addr;
		socklen_t addrlen = sizeof(addr);
		int ret = recvfrom(sock_fd, buf, sizeof(buf), 0, (struct sockaddr*)&addr, &addrlen);
		char *ip = inet_ntoa(addr.sin_addr);
		static int index = 0;
		int flags = 0;
		for(int i = 0; i < index; i++)
		{
			if(strcmp(ipname[i],ip) == 0)
			{
				flags = 1;
				break;
			}
		}
		if(flags == 0)
		{
			ipname[index] = (char *)malloc(strlen(ip)+1);
			strcpy(ipname[index], ip);
			index++;
		}
		printf("ip=%s:%s", ip, buf);
	}
}

pid_t pid;
int father(int sock_fd)
{
	mysend(sock_fd, "上线了\n", GB);
	while(1)
	{
	sleep(1);
		char buf[1024] = { 0 };
		fgets(buf, sizeof(buf), stdin);
		if(strcmp(buf, "exit\n") == 0)
			break;
		else if(strstr(buf, "sendto ") != NULL)
		{
			strtok(buf," ");
			char *p = strtok(NULL, " ");
			char *content = buf+strlen("sendto ")+strlen(p) + 1;
			mysend(sock_fd, content, p);
		}
		else if(strcmp(buf, "list\n") == 0)
		{
			kill(pid, SIGUSR1);
		}
		else if(strcmp(buf, "name\n") == 0)
		{
				printf("未实现\n");
		}
		else
			mysend(sock_fd, buf, GB);
	}
	mysend(sock_fd, "下线了\n", GB);
}

void List(int a)
{
	for(int i = 0; ipname[i] ; i++)
	{
		printf("%s\n",ipname[i]);
	}
}

int main()
{
	signal(SIGUSR1, List);
	int sock_fd;
	sock_fd = init_socket();
	pid = fork();
	if(pid != 0)
	{
		father(sock_fd);
		kill(pid, SIGQUIT);
		wait(NULL);
	}
	else
	{
		son(sock_fd);
	}
	return 0;
}
