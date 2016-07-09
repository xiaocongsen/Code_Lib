#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
	pid_t pid = fork();	
	if(pid == 0)
	{
		//execl("./a.out", "a.out", NULL); 如果生成的文件是a.out,程序就回死循环;
		//execlp( "ls", "ls", "-al", NULL); //调用系统ls -al 命令；
		char const* envp[] ={"PATH=/home/Code_lib", "TERM=console", NULL};
		int ret = execle("a", "a", NULL, envp);
		if(ret == -1)
			perror("execle error"); // 使用错误
		/*	char a[] = "a";
		char *const argv[] = { a, NULL};
		execv("../a", argv); */ //使用execv 数组

	//	char *const argv[] = { (char *)"ls", (char *)"-al", NULL};
	//	execvp("ls", argv); 
		//看爱好选一个就行;
	}
	else
	{
		printf("nihao");
		sleep(1);
		system("echo $PATH");
		sleep(1);
	}
	return 0;
}
