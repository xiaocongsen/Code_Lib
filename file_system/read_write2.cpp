#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
int main()
{
	char buf[10] = { 0 };
	int n = read(STDIN_FILENO, buf, sizeof(buf)); //读取终端标准输入
	if( n < 0 )
	{
		perror("read error");
		return 0;
	}
	write(STDOUT_FILENO, buf, n);//写入终端标准输出；
	return 0;
}
