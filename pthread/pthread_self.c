#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
pthread_t thread0, thread1;
void get_Mypid()
{
	printf("%lu\n", pthread_self());//打印线程自己的pid
}
void* pthread_main(void *arg)
{
	get_Mypid();
	return (void*)1;
}
int main()
{
	const pthread_attr_t *attr = NULL;
	void *arg = NULL;
	pthread_create(&thread0, attr, pthread_main, arg);
	pthread_create(&thread1, attr, pthread_main, arg);
	get_Mypid();
//	sleep(1);
	pthread_join(thread0,NULL);//回收线程
	pthread_join(thread1,NULL);//回收线程,必须回收，不然会出现线程还没结束，主函数已经结束的状况；
	return 0;

}
