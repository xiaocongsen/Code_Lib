#include"../include.h"
int mian()
{
	int sockfd = socked(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		perror("socked error");
		return -1;
	}
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9999);
	int ret = inet_pton(AF_INET,"192.168.155.215", (void*)&addr.sin_addr.s_addr);
	pid_t pid = fork();
	int ret = connect(sockfd, (struct sockaddr*)&addr, sizeof(addr));
	if(ret < 0)
	{
		if(ret == EAGAIN | ret == EINTR) //eagain非阻塞状态  eintr信号打断错误
		{
			
		}
	}
}
