#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
pthread_t thread0, thread1, threadmain;
int equal()
{
	if(pthread_equal(thread0, pthread_self()))//判断当前调用进程是否为thread0
	{
		printf("my tread0\n");
	}
	else if(pthread_equal(thread1, pthread_self()))//判断当前调用进程是否为thread1
	{
		printf("my tread1\n");
	}
	else if(pthread_equal(threadmain, pthread_self()))//判断当前调用进程是否为原函数；
	{
		printf("my treadmian\n");
	}
	else
	{
		printf("error\n");
	}
	return 0;
}
void* pthread_fun(void *arg)
{
	equal();
	return (void*)1;
}
int main()
{
	threadmain = pthread_self();
	pthread_attr_t *attr = NULL;
	void *arg = NULL;
	pthread_create(&thread0, attr, pthread_fun, arg);
	pthread_create(&thread1, attr, pthread_fun, arg);
	equal();
	usleep(1000);
	void *retval = NULL;
	pthread_join(thread0,&retval);
	pthread_join(thread1,&retval);
	return 0;
}
