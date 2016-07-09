#include"../include.h"
int main()
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0); //创建socked tcp链接
	if(sockfd < 0)
	{
		perror("socket set error");
		return -1;
	}
	int index = 0; //存储客户链接文件描述符的数组下标;
	int newfds[1024] = { 0 }; //存描述符的数组
	int nfds = sockfd; //等于最大文件描述符
	nfds++;				//加一;
	fd_set bfreadfds;  //监控读数据，的文件描述符集合
	FD_ZERO(&bfreadfds); //集合清零函数
	FD_SET(sockfd,&bfreadfds); //设置主描述符为监控读的对象
	struct sockaddr_in addr; 
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9999);
	addr.sin_addr.s_addr = htonl(0);
	int ret = bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
	if(ret < 0)
	{
		perror("socket set error"); 
		return -1;
	}
	int backlog = 5;
	ret = listen(sockfd, backlog);
	if(ret < 0)
	{
		perror("socket set error");
		return -1;
	}
	while(1)
	{
		fd_set readfds = bfreadfds;  //使用临时变量操作，因为操作会改变文件描述符集合的内容; 原始内容不能改变;所以使用临时的;
		struct timeval timeout;  //设置延迟时间为1秒;
		timeout.tv_sec = 1;
		timeout.tv_usec = 0;
		ret = select(nfds, &readfds, NULL, NULL, &timeout);//开始监控
		if(ret == -1) 
		{
			if(errno == EINTR)
				continue;
			perror("select error");
			break;
		}
		else if(ret > 0)  //有多少个描述符有信息，ret就等与多少;
		{
			if(FD_ISSET(sockfd, &readfds)) //判断是不是sock文件描述符有新连接到达;
			{
				int connect_fd = accept(sockfd, NULL, NULL); //响应新连接;
				if(nfds <= connect_fd) //判断nfds是否是最大的文件描述符号+1;
				{
					nfds = connect_fd; //如果不是，则等于最大的
					nfds++;				//然后加一
				}
				newfds[index] = connect_fd; //存入数组;
				index++;					//数组下标加一
				FD_SET(connect_fd, &bfreadfds);//添加到监控集合;
				if(--ret == 0) //判断相应个数是不是已经用完
					continue;
			}
			if(index > 1024) //判断数组的集合是否已经爆满;
			break;
			for(int i = 0; i < index; i++) //轮寻整个数组;
			{
				if(newfds[i] == -1)  //假设有-1存在证明已经退出;需要删除
				{
					for(int j = i; j < index ; j++)
					newfds[j] = newfds[j+1];
					index--;
				}
				char buf[1024] = { 0 };
				if(FD_ISSET(newfds[i], &readfds)) //判断这个描述符是否有信号
				{
					int et = read(newfds[i], buf, sizeof(buf));
					if(et <= 0)
					{
						close(newfds[i]);
						FD_CLR(newfds[i],&bfreadfds);
						newfds[i] = -1;
						continue;
					}
					//	buf[strlen(buf)] = 0;
				}
			}
			for(int i = 0; i < 10; i++)
				if(newfds[i] )
				printf("%d\n", newfds[i]);
		}
	}
	return 0;
}
