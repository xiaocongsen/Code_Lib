#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
unsigned int i = 0;
void fun(int)
{
	printf("%d\n", i);
	exit(0);
}
int main()
{
	signal(SIGALRM, fun);
	alarm(1);
	while(1)
		i++;
}
