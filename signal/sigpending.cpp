#include<stdio.h>
#include<signal.h>
#include<string.h>

int main()
{
	sigset_t set; //创建一个阻塞信号集
	sigset_t oldset; //创建一个用于保存老的信号集
	sigemptyset(&oldset); //将老的信号集全部置0
	sigfillset(&set);//将需要设置到系统的阻塞信号集全部置1；
	sigprocmask(SIG_SETMASK, &set, &oldset);//将设置好的阻塞信号集设置到系统，并保存系统原来的信号集到oldset
	char buf[1024] = { 0 };
	while(1){
		fgets(buf, sizeof(buf), stdin);
		if(strcmp(buf, "exit\n") == 0)
			break; }
	sigpending(&set); //获取系统的未决信号集；
	int ret = sigismember(&set, SIGQUIT); //判断信号集中SIGQUIT是否置1；如果置1，证明有信号的到来不过被阻塞了;
	if(ret == 1)
	{
		printf("存在\n");
	}
	else if(ret == 0)
	{
		printf("不存在\n");
	}
	else if(ret == -1)
	{
		perror("sigsmember error");
		return ret;
	}
	ret = sigismember(&set, SIGINT); //同上；
	if(ret == 1)
	{
		printf("存在\n");
	}
	else if(ret == 0)
	{
		printf("不存在\n");
	}
	else if(ret == -1)
	{
		perror("sigsmember error");
		return ret;
	}
	return 0;
}
