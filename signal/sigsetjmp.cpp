#include <stdio.h>
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>
static sigjmp_buf env;
static void fun (void)
{
	sigsetjmp(env, 0);
	long long i = 1000000000;
	printf("2before %s\n", __FUNCTION__);
	while(i)
	i--;
	printf("2end %s\n", __FUNCTION__);
}
static void handler (int s)
{

	printf("1before %s\n", __FUNCTION__);
	siglongjmp(env, 0);
	printf("1end %s\n", __FUNCTION__);
}
int main (void)
{
	signal(SIGINT, handler);
	sleep(1);
	fun();
	long long i = 0;
	for (i = 0; ; i++)
	{
		printf("打印：%lld\n", i);
		pause();
	}
	return 0;
}
