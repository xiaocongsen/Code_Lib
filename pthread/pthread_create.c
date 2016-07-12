#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<signal.h>
#include<unistd.h>
int i = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void fun()
{
	pthread_mutex_lock(&mutex);
	++i;
	pthread_mutex_unlock(&mutex);
}
void* pthread_main(void *arg)
{
	while(1)
	{
		fun();	
	}
}
void Exit(int a)
{
	printf("%d\n",i);
	exit(0);
}
int main()
{
	alarm(1);
	signal(SIGALRM, Exit); 
	pthread_mutex_init(&mutex, NULL);
	pthread_t thread;//保存创建出的线程的线程号的参数
	const pthread_attr_t *attr = NULL;//设置线程属性
	void *arg = NULL;//线程主函数的函数参数；
//	pthread_create(&thread, attr, pthread_main, arg);
//	pthread_create(&thread, attr, pthread_main, arg);
//	pthread_create(&thread, attr, pthread_main, arg);
//	pthread_create(&thread, attr, pthread_main, arg);
//	pthread_create(&thread, attr, pthread_main, arg);
//	pthread_create(&thread, attr, pthread_main, arg);
	pthread_create(&thread, attr, pthread_main, arg);
	pthread_create(&thread, attr, pthread_main, arg);
	while(1)
	{
		fun();
	}
	return 0;

}
