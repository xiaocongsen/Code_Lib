#include<stdio.h>
#include<pthread.h>
int data = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;  //直接给锁设置
//pthread_mutex_t mutex;//定义一个全局锁变量；
void *pthread_fun(void* arg)
{
	for(int i = 0; i < 100000; i++)
	{
//		pthread_mutex_lock(&mutex);//加锁
		pthread_mutex_lock(&mutex);//加锁
		data+=1;	
		pthread_mutex_unlock(&mutex);//解锁
//		pthread_mutex_unlock(&mutex);//解锁
	}	
	return (void*)1;
}
int main()
{
//	pthread_mutexattr_t attr1;  //定义一个锁的属性变量
//	pthread_mutexattr_init(&attr1);	//对锁的属性变量进行初始化；
//	pthread_mutexattr_settype(&attr1, PTHREAD_MUTEX_RECURSIVE);//设置锁的属性变量成循环锁
//	pthread_mutex_init(&mutex, &attr1);//初始化锁；
	pthread_t thread1,thread2;
	pthread_attr_t *attr = NULL;
	void *arg = NULL;
	pthread_create(&thread1, attr, pthread_fun, arg);
	pthread_create(&thread2, attr, pthread_fun, arg);
	void *retval2 = NULL;
	void *retval1 = NULL;
	pthread_join(thread1, &retval1);
	pthread_join(thread2, &retval2);
	pthread_mutex_destroy(&mutex);//销毁锁；
	printf("%d\n", data);
	return 0;
}

