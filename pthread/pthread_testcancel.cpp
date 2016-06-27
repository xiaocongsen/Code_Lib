#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
int i = 0;
void* pthread_fun(void *arg)
{
	while(1)
	{
		int a =10;
		a++;
//		pthread_testcancel();           //不掉用这个坚持是否有终止信号
//		printf("wocao%d\n",i++);       //刷新缓存可会检测是否有终止信号
//		sleep(5);			//也会，许多函数都会，如果没有这类函数,终止信号将不会被检测，无法终止程序；
	}
	return (void*)1;
}
int main()
{
	pthread_t thread;
	pthread_attr_t *attr = NULL;
	void *arg = NULL;
	pthread_create(&thread, attr, pthread_fun, arg);
	//sleep(1);
	pthread_cancel(thread);
	void *retval = NULL;
	pthread_join(thread, &retval);
	return 0;
}
