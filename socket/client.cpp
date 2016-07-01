#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
int main()
{
	int fd = socket(AF_INET, SOCK_STREAM, 0);//创建socket
	if(fd == -1)
	{
		perror("socket 创建");
		return -1;
	}
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9999);
	addr.sin_addr.s_addr = inet_addr("192.168.155.51");
	int ret = connect(fd, (struct sockaddr*)&addr, sizeof(addr));
	if(ret == -1)
	{
		perror("connect 链接失败");
		return -1;
	}
	write(fd, "hello server", sizeof("hello server"));
	char buf[1024] = { 0 };
	read(fd, buf, sizeof(buf));
	printf("%s\n",buf);
	close(fd);
	return 0;
}
