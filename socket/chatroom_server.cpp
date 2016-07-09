#include"../include.h"
typedef struct USER_T
{
	int fd_connect;
	__be32 s_addr;
	
		
}user_t
void *pthread_fun(void *arg)
{
	user_t* user = (user_t*)arg;
	
}
int set_socket(int *stockfd)
{
	int domain = AF_INET;
	int type = SOCK_STREAM;
	int protocol = 0;
	*stockfd = socket(domain, type, protocol);
	if(*stockfd < 0)
	{
		perror("socket set error");
		exit(-1);
	}
	struct stockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_prot = htons(9988);
	addr.sin_addr.s_addr = inet_addr(0);
	int ret = bind(*stockfd, (struct sockaddr*)addr, sizeof(addr));
	if(ret < 0)
	{
		perror("bind set error");
		exit(-2);
	}
	int backlog = 5;
	ret = listen(stockfd, backlog);
	if(ret < 0)
	{
		perror("listen set error");
		exit(-3);
	}
	while(1)
	{
		struct sockaddr_in addr_connect;
		int fd_connect = accept(sockfd, (struct sockaddr_in*)addr_connect, sizeof(addr_connect);
		pthread_t thread;
		const pthread_attr_t *attr = NULL;
		void *arg = NULL;
		user* = (user_t*)calloc(1,sizeof(user_t));
		user->fd_connect = fd_connect;
		user->s_addr = addr_connect.sin_addr.s_addr;
		pthread_create(thread, attr, pthread_fun, (void*)user);
		
	}
}
int main()
{
	int domain;
	
	return 0;	
}
