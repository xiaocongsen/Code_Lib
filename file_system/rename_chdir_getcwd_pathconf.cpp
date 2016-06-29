#include<stdio.h>
#include<unistd.h>
int main()
{
	const char* oldpath = "hello.d";
	const char* newpath = "word.d";
	const char* path = "./";
	rename(oldpath, newpath);  //重命名文件
	char buf[1024] = { 0 };
	size_t size = sizeof(buf);
	int ret = chdir(path); //改变工作目录；
	if(ret == 0)
		printf("ok");
	getcwd(buf, size);    //获得当前工作目录；
	printf("%s\n", buf);
	long l = pathconf("a.out", _PC_LINK_MAX); //打印链接最大数
	if(l == -1)
	{	
		perror("pathconf");
	}
	printf("%ld", l);
	return 0;
}
