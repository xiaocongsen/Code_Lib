#include<stdio.h>
#include<pthread.h>
void *pthread_fun(void *arg)
{
	printf("我要毁灭");
	pthread_exit((void*)1);	//结束线程，返回(void*)1
	return (void*)2;
}
int main()
{
	pthread_t thread;
	pthread_attr_t *attr = NULL;
	void * arg = NULL;
	pthread_create(&thread, attr, pthread_fun, arg);	
	void *retval = NULL;	
	pthread_join(thread,&retval);
	printf("\n%p\n",retval);
	return 0;
}
