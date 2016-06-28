#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; //创建锁变量，并初始化为基础锁
pthread_rwlock_t rwlock ;		//创建循环锁变量
pthread_cond_t cond;			//创建条件变量；
int data = 0;				//全局变量；
void *pthread_fun_w(void *arg)		//写函数
{
	int i = 6;
	while(i--)
	{	
		pthread_cond_wait(&cond, &mutex); //等待条件变量信号；
	//	data += 10;			
		pthread_rwlock_wrlock(&rwlock);	//写锁		
		printf("%d\n",data);		
		pthread_rwlock_unlock(&rwlock);	//解锁	
	}
	return (void*)1;

}
void *pthread_fun_r(void *arg)
{
	int i = 3;
	while(i--)
	{	
		/*     int pthread_cond_wait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex);*/
		pthread_cond_wait(&cond, &mutex);
		pthread_rwlock_rdlock(&rwlock);		//读锁	
		printf("%d\n",++data);	
		pthread_rwlock_unlock(&rwlock);		//解锁		
	}
	return (void*)2;
}
int main()
{
	pthread_rwlockattr_t lattr;	//创建读写锁属性变量；
	pthread_rwlockattr_init(&lattr);//初始化属性变量
	pthread_rwlock_init(&rwlock,&lattr);//初始化读写锁
	pthread_condattr_t cattr;    //创建条件变量的属性变量；
	pthread_condattr_init(&cattr);//初始化条件变量属性;
	pthread_cond_init(&cond, &cattr);//初始化条件变量
	pthread_t thread0, thread1;
	pthread_attr_t *attr = NULL;
	void *arg = NULL;
	pthread_create(&thread0, attr, pthread_fun_w, arg);
	pthread_create(&thread1, attr, pthread_fun_r, arg);
	for(int i = 0; i < 10; ++i)
	{
		usleep(100);
//		printf("( %d ) ",i);
	//	pthread_cond_signal(&cond);   //发生信号,只有0和1两种状态，不累加,所以可能丢失；
		pthread_cond_broadcast(&cond);//发生广播,激活所以wait的线程；
	}
	void *retval = NULL;
	pthread_detach(thread0);
	pthread_detach(thread1);
	pthread_join(thread0,&retval);
	printf("%p",retval);
	pthread_join(thread1,&retval);
	printf("%p",retval);
	pthread_rwlock_destroy(&rwlock);
	pthread_cond_destroy(&cond);  //销毁条件变量
	pthread_mutex_destroy(&mutex);
	return 0;
}
