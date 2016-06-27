#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
int i = 0;
void* pthread_main(void *arg)  //arg就是main函数里的arg;
{
		sleep(1);
		printf("hell%d",i);
	return (void*)1; 
}
int main()
{
	pthread_t thread;//保存创建出的线程的线程号的参数
	const pthread_attr_t *attr = NULL;//线程的属性！
	void *arg = NULL;//线程函数的传参参数！
	pthread_create(&thread, attr, pthread_main, arg);//创建一个线程；
		i++;
	pthread_cancel(thread);//结束一个线程	
	void *retval = NULL;
	pthread_join(thread,&retval);
	printf("\n%p",retval);
	return 0;

}
