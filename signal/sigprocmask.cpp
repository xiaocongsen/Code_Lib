#include<stdio.h>
#include<string.h>
#include<signal.h>
int main()
{
	printf("%lu\n", sizeof(sigset_t));
	sigset_t set;   //创建信号屏蔽字
	sigfillset(&set);  //把创建的屏蔽字中所有信号都设置成1；
	sigset_t old;
	sigprocmask(SIG_BLOCK, &set, &old); //把创建的屏蔽字 通过SIG_BLOCK 设置到系统里, 添加了所以信号都屏蔽  old获得系统原有屏蔽字
	while(1)
	{
		char buf[1024] = { 0 };
		fgets(buf, sizeof(buf), stdin);
		if(strcmp(buf, "exit\n") == 0)
			break;
	}
	sigdelset(&set, SIGQUIT); //在创建的屏蔽字中删除SIGQUIT信号(讲这个位设置成0);
	sigprocmask(SIG_SETMASK, &set, NULL); //把操作过的set 通过SIG_SETMASK 设置到系统，等于替换了原有的系统屏蔽字；
	while(1)
	{
		char buf[1024] = { 0 };
		fgets(buf, sizeof(buf), stdin);
		if(strcmp(buf, "exit1\n") == 0)
			break;
	}
	sigaddset(&set, 3); // 在set中添加3号位将其设置成1；
	sigprocmask(SIG_UNBLOCK, &set, NULL);  //把所以set中是1的全部解除屏蔽，在这意味着清楚了系统所有的屏蔽信号
	while(1)
	{
		char buf[1024] = { 0 };
		fgets(buf, sizeof(buf), stdin);
		if(strcmp(buf, "exit2\n") == 0)
			break;
	}
	sigemptyset(&set); //把set中所以的位都设置成0; 
	sigprocmask(SIG_UNBLOCK, &set, NULL); //没乱用；
	while(1)
	{
		char buf[1024] = { 0 };
		fgets(buf, sizeof(buf), stdin);
		if(strcmp(buf, "exit3\n") == 0)
			break;
	}
	sigprocmask(SIG_SETMASK, &old, NULL); //还原系统原有屏蔽字;
	return 0;
}
