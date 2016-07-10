#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/time.h>
#include<unistd.h>
int main()
{
	struct itimerval utime; //创建定时结构体
	utime.it_interval.tv_sec = 0 ; //初始化2次定时任务之间的间隔时间的秒
	utime.it_interval.tv_usec = 0; //初始化2次定时任务之间的间隔时间的微秒
	utime.it_value.tv_sec = 1; //初始化定时时长的秒
	utime.it_value.tv_usec = 1000;//初始化定时时长的微妙
	setitimer(ITIMER_REAL, &utime , NULL); //创建定时器；
	
	usleep(1000000);
	struct itimerval oldutime; //创建定时结构体
	utime.it_value.tv_sec = 2; //再次设定定时时长的秒
	setitimer(ITIMER_REAL, &utime, &oldutime); //重新创建定时器
	printf("%ld",oldutime.it_value.tv_usec); //打印老定时器剩余的时间；
	getchar();	
}

