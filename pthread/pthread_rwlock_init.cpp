#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
pthread_rwlock_t rwlock; //建立循环锁变量
int data = 0;	
void* pthread_fun_w(void* arg)
{
//	usleep(100);
	pthread_rwlock_wrlock(&rwlock);//写锁
	for(int i = 0; i < 10000000; i++)
		data += 1;
	pthread_rwlock_unlock(&rwlock);//解锁
	
}
void* pthread_fun_r(void* arg)
{
	pthread_rwlock_rdlock(&rwlock);//读锁
	printf("%d\n",data);
	pthread_rwlock_unlock(&rwlock);//解锁
}
int main()
{
	/*       int pthread_rwlock_init(pthread_rwlock_t *restrict rwlock, const pthread_rwlockattr_t *restrict attr);*/
	pthread_rwlockattr_t lattr;
	/* int pthread_rwlockattr_init(pthread_rwlockattr_t *attr);*/
	pthread_rwlockattr_init(&lattr);
	pthread_rwlock_init(&rwlock, &lattr);
	pthread_t thread[8];
	pthread_attr_t *attr = NULL;
	void *arg = NULL;
	pthread_rwlock_destroy(&rwlock);//销毁锁；
	for(int i = 0; i < 5; ++i)
	pthread_create(&thread[i], attr, pthread_fun_w, arg);
	for(int i = 5; i < 8; ++i)
	pthread_create(&thread[i], attr, pthread_fun_r, arg);
	for(int i = 0; i < 8; ++i)
	pthread_join(thread[i],NULL);
	return 0;
}
