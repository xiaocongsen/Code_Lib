#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
//全局区需要有个队列，用于主线程和子线程的数据交换；
sem_t sem ;
void *pthread_fun(void* arg)
{
	while(1)
	{
		sem_wait(&sem);  //等待接收信号，执行下面操作，信号数量减一；
		printf("%lu\n",pthread_self()%1000);//打印线程pid;
	}
		return (void*)1;
}
int main()
{
	int pshared = 0;   //零为线程， 非零为进程；
	unsigned int value = 10;  //初始化信号数量；
	sem_init(&sem, pshared, value);  //初始化信号量函数；
	pthread_t thread[10];	
	pthread_attr_t *attr = NULL;
	void *arg = NULL;
	for(int i = 0; i < 10; i++)
		pthread_create(&thread[i], attr, pthread_fun, arg);
	for(int i = 0; i < 10; i++)
		sem_post(&sem);// 增加信号数；
	sleep(1);
	for(int i = 0; i < 10; i++)
		pthread_detach(thread[i]); //分离线程，
	sem_destroy(&sem);  //销毁信号量；
	return 0;
}
