#include<stdio.h>
int main()
{
	domain = AF_INET;
		
	int sockfd = socket(domain, SOCK_STREAM, 0);
	
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9988);
	addr.sin_addr.s_addr = inet_addr(0);
	int ret = bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
	if(ret < 0)
	{
		perror("bind error");
		return -1;
	}
	int backlog = 5
	listen(sockfd, backlog);

	while(1)
	{
		int fd_connect = accept(stockfd,  
		char buf[1024];
	}
}
