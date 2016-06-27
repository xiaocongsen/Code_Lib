#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
int i = 0;
void* pthread_main(void *arg)
{
		sleep(1);
		printf("hell%d",i);
	return (void*)1;
}
int main()
{
	pthread_t thread;
	const pthread_attr_t *attr = NULL;
	void *arg = NULL;
	pthread_create(&thread, attr, pthread_main, arg);
		i++;
	void *retval = NULL;//线程终止返回值参数；
	pthread_join(thread,&retval);//等等进程结束后
	printf("\n%p",retval);
	return 0;

}
