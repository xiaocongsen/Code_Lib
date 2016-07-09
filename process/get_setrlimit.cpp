#include<stdio.h>
#include<stdlib.h>
#include<sys/resource.h>
int main()
{
	system("cat /proc/self/limits"); //文件打印系统资源限制
	int resource = RLIMIT_NOFILE; //需要获取或修改的资源是一个进程打开文件的最大个数
	struct rlimit rlim;	//创建一个结构体用于接受获取的资源内容；
	getrlimit(resource, &rlim);  //获取到资源结构体
	printf("\n%lu, max = %lu",rlim.rlim_cur, rlim.rlim_max);//打印当前设置资源和系统最大资源；
	rlim.rlim_cur = 2048;	//修改当前设置资源；
	setrlimit(resource, &rlim);//设置修改后的资源
	printf("\n%lu, max = %lu",rlim.rlim_cur, rlim.rlim_max);//打印
	
	printf("\n");
	system("ulimit -a");//命令打印系统资源限制；
}
