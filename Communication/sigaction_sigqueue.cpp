#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void Mysig_fun1(int, siginfo_t *, void *)
{
	printf("word\n");
}
void Mysig_fun(int, siginfo_t *, void *)
{
	printf("hello ");
}
int main()
{
	struct sigaction sig_act;
	sig_act.sa_sigaction = Mysig_fun;
	sigemptyset(&sig_act.sa_mask);
	sig_act.sa_flags = SA_NODEFER;
	struct sigaction sig_oldact;
	sigaction(SIGUSR1, &sig_act, &sig_oldact);
	struct sigaction act;
	act.sa_sigaction = Mysig_fun1;
	act.sa_flags = SA_NODEFER;
	sigemptyset(&act.sa_mask);
	struct sigaction oldact;
	sigaction(SIGUSR2,&act,&oldact);
	pid_t pid = fork();
	int i = 50;
	while(i)
	{
		if(pid == 0)
		{
			union sigval val1;
			val1.sival_int = 0;
			sigqueue(getppid(), SIGUSR1, val1);
			i--;
		}
		else
		{
			union sigval val;
			val.sival_int = 0;
			sigqueue(pid, SIGUSR2, val);
			i--;
		}
	}
	return 0;
}
