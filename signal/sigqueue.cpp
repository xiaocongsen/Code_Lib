#include<stdio.h>
#include<signal.h>
#include<sys/types.h>
#include<unistd.h>

void fun(int a, siginfo_t *act, void *val)
{
	printf("nimei%d\n", a);
	printf("kao%d\n",act->si_value.sival_int); //打印传参值；
	while(1) //由于设置了屏蔽信号，所以2秒的定时将不起作用;但是9号信号无法屏蔽
	{		sleep(3);
		kill(getpid(), 9); //对当前进程发送SIGKILL信号
	}
}
int main()
{
	alarm(2);  //定时
	struct sigaction act; //创建注册函数
	//	act.sa_handler = fun;
	act.sa_sigaction = fun; //对信号处理函数进行传参
	sigfillset(&act.sa_mask); //对屏蔽字进行填满1；
	act.sa_flags = SA_SIGINFO; //设置调用sa_sigaction函数时必须设置;
	sigaction(SIGUSR1, &act, NULL);//注册信号；

	union sigval val; //创建需要通过信号传递的公用体;
	val.sival_int = 999; //对共用体的赋值需要传递的参数;
	sigqueue(getpid(), SIGUSR1, val); //通过可传递参数的信号发送函数进行发送信号；
	return 0;
}
