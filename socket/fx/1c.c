#include"fx.h"
typedef struct nameip
{
	char name[50];
	char ip[15];
};
int broadcast_send(int sock_fd,char *buf)
{
	struct sockaddr_in gbaddr;
	gbaddr.sin_family = AF_INET;
	gbaddr.sin_port = htons(19981);
	gbaddr.sin_addr.s_addr = inet_addr("255.255.255.255");
	sendto(sock_fd, buf, strlen(buf)+1, 0, (struct sockaddr*)&gbaddr, sizeof(gbaddr));
	return 0;
}
/*
int sendto(int sock_fd,char *ip)
{
	struct sockaddr_in gbaddr;
	gbaddr.sin_family = AF_INET;
	gbaddr.sin_port = htons(19981);
	gbaddr.sin_addr.s_addr = inet_addr(ip);
	sendto(sock_fd, buf, strlen(buf)+1, 0, (struct sockaddr*)&gbaddr, sizeof(gbaddr));
	return 0;	
}
*/
int main()
{
	int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock_fd < 0)
	{
		perror("socket error");
		return sock_fd;
	}
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(19981);
	addr.sin_addr.s_addr = 0;
	bind(sock_fd, (struct sockaddr*)&addr, sizeof(addr));
	//struct ip_mreqn optval;
	int optval = 1;
	setsockopt(sock_fd, SOL_SOCKET, SO_BROADCAST, &optval, sizeof(optval));
	char buf[1024] = { 0 };
	pid_t pid = fork();
	if(pid != 0)
	{
		broadcast_send(sock_fd,"上线了\n");
		while(1)
		{
			fgets(buf, sizeof(buf), stdin);
			if(strcmp(buf, "exit\n") == 0)
				break;
			char *gut = NULL;
			if((gut = strstr(buf, ":")) != NULL)
			{
				
				printf("请输入对方ip:\n");
				memset(buf, 0, sizeof(buf));
				fgets(buf,sizeof(buf), stdin);
		//		sendto(sock_fd, buf);
			}
			broadcast_send(sock_fd ,buf);
		}
		broadcast_send(sock_fd,"下线了\n");
		kill(pid, SIGQUIT); 
	}
	else
	{

		while(1)
		{
			signal(SIGUSR1, headlen)
			struct sockaddr_in heraddr;
			socklen_t addrlen = sizeof(heraddr);
			recvfrom(sock_fd, buf, sizeof(buf), 0, (struct sockaddr*)&heraddr, &addrlen);
			char *ip = inet_ntoa(heraddr.sin_addr);
				if(strcmp(ip,"192.168.155.21"))
					continue;
				if(strcmp(buf,"list\n"))
					broadcast_send(sock_fd ,"");
					
			printf("%s: %s", ip ,buf);
		}
	}
	return 0;

}
