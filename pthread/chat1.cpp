#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
pthread_t thread0;
pthread_t thread1;
int fg_0w, fg_0r; 
void* pthread_main(void* arg)
{
	mkfifo("pipe1",0666);
	mkfifo("pipe2",0666);
	fg_0r = open("pipe1", O_RDONLY);
	if(fg_0r < 0)
		perror("RD1");
	while(1)
	{	
		char buf0[2048] = {0};
		read(fg_0r,buf0,sizeof(buf0));
		printf("%s",buf0);
		usleep(1000);
	}
}
int main(int argc, char *argv[])
{
	if(argc >= 2)
	{
		const pthread_attr_t *attr = NULL;
		void *arg = NULL;
		pthread_create(&thread1, attr, pthread_main, arg);
		sleep(1);
		fg_0w = open("pipe2", O_WRONLY);
		if(fg_0w < 0)
			perror("openw");
		while(1)
		{
			char buf1[2048] = {0};
			sprintf(buf1,"%s:",argv[1]);
			fgets(buf1+strlen(buf1),sizeof(buf1),stdin);
			write(fg_0w,buf1,strlen(buf1));
			usleep(1000);
		}
	}
	return 0;
}
