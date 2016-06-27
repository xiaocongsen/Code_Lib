#include<stdio.h>
#include<pthread.h>
pthread_t thread0, thread1, threadmain;
int equal()
{
	if(pthread_equal(thread0, pthread_self()))
	{
		printf("my tread0");
	}
	else if(pthread_equal(thread1, pthread_self()))
	{
		printf("my tread0");
	}
	else if(pthread_equal(threadmain, pthread_self()))
	{
		printf("my tread0");
	}
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
	
	return 0;
}
