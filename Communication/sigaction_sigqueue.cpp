#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
#include<signal.h>

void Mysig_fun1(int, siginfo_t *, void *)
{
	printf("word\n");
}
void Mysig_fun(int, siginfo_t *, void *)
{
	printf("hello\n");
}
int main()
{
	struct sigaction sig_act;
	sig_act.sa_sigaction = Mysig_fun;
	sigemptyset(&sig_act.sa_mask);
	sig_act.sa_flags = 0;
	sig_act.sa_flags |= SA_RESTART;
	struct sigaction sig_oldact;
	sigaction(SIGUSR1, &sig_act, &sig_oldact);
	struct sigaction act;
	act.sa_sigaction = Mysig_fun1;
	act.sa_flags = 0;
	act.sa_flags |= SA_RESTART;
	sigemptyset(&act.sa_mask);
	struct sigaction oldact;
	sigaction(SIGUSR2,&act,&oldact);
	pid_t pid = fork();
	int i = 50;
	if(pid == 0)
	{
		while(i)
		{
			union sigval val;
			val.sival_int = 0; 
			sigqueue(getppid(), SIGUSR1);
			usleep(10);
			i--;
			printf("%d\n",i);
		}
	}
	else
	{
		while(i)
		{
			union sigval val;
			val.sival_int = 0; 
			sigqueue(pid,SIGUSR2,val);
			usleep(100);
			i--;
			printf("%d\n",i);
		}
		wait(NULL);
	}

	return 0;
}
