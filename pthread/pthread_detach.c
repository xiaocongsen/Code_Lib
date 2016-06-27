#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
void *phread_fun(void *arg)
{
	while(1)
	{
		printf("%s\n",(char*)arg);	
		usleep(100000);
	}
	return (void *)9;
}
int main()
{
	pthread_t thread;
	pthread_attr_t *attr = NULL;
	char *arg = "xiaocs";
	pthread_create(&thread, attr, phread_fun, (void*)arg);//创建线程
	pthread_detach(thread);//分离线程，主线程可以不必等他结束；
	void *retval = NULL;
	int ret = pthread_join(thread,&retval);//无法活动分离后的线程返回值,不阻塞，直接通过；
	printf("%p\n",retval);
	sleep(1);
	if(ret != 0)
		perror("pthread_join");	
	return 0;
}
