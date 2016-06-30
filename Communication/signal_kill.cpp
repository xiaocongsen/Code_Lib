#include<stdio.h>
#include<sys/types.h>
#include<signal.h>
#include<unistd.h>
void handler(int){}
int main()
{
	int a[100] = { 0 };
	for(int i = 0; i < 100; ++i)
	{
		a[i] = i;
	}
	signal(SIGUSR1,handler);
	pid_t pid = fork();
	int i = 0;
	while(i < 99)
	{
		if(pid == 0)
		{
			sleep(10);
			i++;
			if(i % 2 != 0)
			i++;
			if(i > 99)
				return 0;	
			printf("pid = %d ：%d\n",getpid(),a[i]);
		}
		else
		{
			kill(pid,SIGUSR1);
			i++;
			if(i % 2 == 0)
			i++;
			usleep(1000);
			printf("pid = %d ：%d\n",getpid(),a[i]);
		}
	}
	return 0;
}
