#include<stdio.h>
#include<signal.h>
#include<stdlib.h> 
#include<unistd.h>
static void int_handler(int s)
{

	write(1,"!",1);
}

int main()
{
	sigset_t set,oset,saveset;
	signal(SIGINT,int_handler); //注册信号处理函数;
	sigemptyset(&set); //清空屏蔽字;
	sigaddset(&set,SIGINT); //添加SIGINT信号位为1；
	sigprocmask(SIG_UNBLOCK,&set,&saveset);//备份原有的屏蔽字;
	sigprocmask(SIG_BLOCK,&set,&oset);//备份没有屏蔽SIGINT的屏蔽字并设置屏蔽SIGINT信号
	for(int j = 0 ; j < 10000; j++) 
	{
		for(int i = 0 ; i < 5; i++)
		{
			sigpending(&set);
			int ret = sigismember(&set,SIGINT);
			if(ret == 0)
			write(1,"0",1);
			else
			write(1,"1",1);
			sleep(1);
		}
		write(1,"\n",1);
		sigsuspend(&oset); // 相当于下面三行的原子操作
	/*
		   sigset_t tmpset;
		   sigprocmask(SIG_SETMASK,&oset,&tmpset); //执行解除屏蔽，如果未决信号集中有信号被阻塞了，在解除后就回马上调用；
		   pause();				//按正常想法是想让屏蔽的那个阻塞信号打断pause()这个函数的挂起状态;
		   sigprocmask(SIG_SETMASK,&tmpset,NULL); //然后再次屏蔽这个信号;
		   但是这3步不能实现想法操作；只能使用sigsuspend函数代替
	*/
	}
	sigprocmask(SIG_SETMASK, &saveset, NULL); //还原；
}
