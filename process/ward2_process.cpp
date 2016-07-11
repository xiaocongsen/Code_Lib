#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<signal.h>
int main()
{
	pid_t pid = fork();
	if(pid == 0)
	{
		setsid();
		pid = fork();
			if(pid == 0)
			{
				chdir("/tmp");
				umask(0);
				signal(SIGCHLD, SIG_IGN);
				for(int i = 0; i < 1024; ++i)
					close(i);
				sleep(100);
			}
			else
				usleep(1000*10);
		return 0;

	}
	usleep(1000*10);
	return 0;
}
