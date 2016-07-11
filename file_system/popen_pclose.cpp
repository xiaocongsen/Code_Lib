#include<stdio.h>

int main()
{
	FILE* file  = popen("ls -al", "er"); //打开一个程序，将其输出内容当做文件打开；可读可写；如果有执行exec族的函数 请指定"er"或者"ew"打开;
										//会自行关闭;
	while(1)
	{
		char buf[1024] = { 0 };
		int ret = fread(buf, 1,sizeof(buf)-1, file);
		if(ret <= 0)
			break;
		printf("%s", buf);
	}
	pclose(file);
	return 0;
}
