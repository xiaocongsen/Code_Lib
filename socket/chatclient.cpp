#include"../include.h"
int main()
{
	int domain = AF_INET;
	int type = SOCK_STREAM;		//stream
	int protocol = 0;
	int sockfd = socket(domain, type, protocol);
	if(sockfd < 0)
	{
		perror("socket error");
		return sockfd;
	}
	else
	{
		struct sockaddr_in addr;
		addr.sin_addr.s_addr = inet_addr("127.0.0.1");
		addr.sin_port = htons(9999);
		addr.sin_family = AF_INET;
		socklen_t addrlen = sizeof(addr);
		int ret = connect(sockfd, (struct sockaddr*)&addr, addrlen);
		if( ret < 0)
		{
			perror("connect error");
			return ret;
		}
		else
		{
			pid_t pid = fork();
			while(1)
			{
				char buf[1024] = { 0 };
				if(pid == 0)
				{
					while(1)
					{
						ret = read(sockfd, buf, sizeof(buf));
						if(ret < 0)
						{
							if(errno == EINTR)
							perror("read error");
							kill(getppid(),SIGKILL);
							return ret;
						}
						else if(ret == 0)
						{
							printf("%s:服务器已关闭", inet_ntoa(addr.sin_addr));	
							kill(getppid(),SIGKILL);
							return 0;	
						}
						else
						{
							printf("%s: %s\n", inet_ntoa(addr.sin_addr), buf);	
						}
					}
				}
				else
				{
					//fgets(buf, sizeof(buf), stdin);
					//system("clear");
					usleep(1000);
					ret = write(sockfd, "xxbuf", sizeof("xxbuf"));
					if(ret < 0)
					{
						perror("write errof");
						kill(pid,SIGKILL);
						return ret;
					}
				}
			}
		}
	}
}
