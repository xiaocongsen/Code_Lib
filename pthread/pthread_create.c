#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
int i = 0;
void* pthread_main(void *arg)
{
	while(1)
	{
		printf("hell%d",i);
		sleep(1);
	}
}
int main()
{
	pthread_t thread;//保存创建出的线程的线程号的参数
	const pthread_attr_t *attr = NULL;//设置线程属性
	void *arg = NULL;//线程主函数的函数参数；
	pthread_create(&thread, attr, pthread_main, arg);
	while(1)
	{
		getchar();
		i++;
	}
	return 0;

}
