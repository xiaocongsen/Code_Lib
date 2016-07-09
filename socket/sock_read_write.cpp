#include"../include.h"
int My_read(int sockfd, char* buf, int len)
{
	int begin = 0;
	int spare = len;
	while(spare > 0)
	{
		int ret = read(sockfd, buf + begin, spare);
		if(ret == 0)
		{
			perror("server close");
			return -1;
		}
		else if(ret < 0)
		{	
			if(errno == EINTR)
				continue;
			perror("read error");
			return ret;
		}
		begin += ret;
		spare -= ret;
	}
	return len;
}
int My_write(int sockfd, const char *buf, int len)
{
	int begin = 0;
	int spare = len;
	while(spare > 0)
	{
		int ret = write(sockfd, buf+begin, spare);
		if(ret < 0)
		{
			if(errno == EINTR)
				continue;
			perror("write error");
			return ret;
		}
		else
		{
			begin += ret;
			spare -= ret;	
		}
		
	}
	return len;
}
