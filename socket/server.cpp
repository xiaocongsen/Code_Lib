#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
int main()
{
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if(fd == -1)
	{
		perror("socket 创建");
		return -1;
	}
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9999);
	addr.sin_addr.s_addr = 0;
	int ret = bind(fd, (struct sockaddr*)&addr, sizeof(addr));
	if(ret == -1)
	{
		perror("bind 绑定失败");
		return ret;
	}
	ret = listen(fd, 5);
	if(ret == -1)
	{
		perror("listen 监听失败");
		return ret;
	}
	int fd_connect = accept(fd, NULL, NULL);
	char buf[1024] = { 0 };
	ret = read(fd_connect, buf, sizeof(buf));
	if(ret > 0)
	{
		perror("read 失败");
		return ret;
	}
	else if(ret == 0)
	{
		printf("客走了");
	}

	printf("recv data is %s\n", buf);
	ret = write(fd_connect, "i got it\n", sizeof("i got it\n"));
	close(fd_connect);
	close(fd);
	return 0;
}
