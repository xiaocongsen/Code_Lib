#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
int main()
{
	const char *pathname = "hello.d";
	//mode_t mode = 0777;
	char buf[2048] = { 0 };
	//int flags = O_WRONLY | O_CREAT;
	//unlink(pathname);  //删除文件
	//	int fd = open(pathname,flags,mode); 
	const char * mode = "w";
	FILE *file  = fopen(pathname,mode);   //用c语言的函数打开文件
	//	if(fd < 0)
	if(file == NULL)
	{
		perror("open error");
		return 0;
	}
	else
	{
		size_t count = sizeof(buf);
		fgets(buf,sizeof(buf),stdin);   //获取键盘输入；
		fwrite(buf, 1, strlen(buf), file);
		//	ssize_t write(int fd, const void *buf, size_t count);  //write 原型；
		//write(fd, buf, count); //写入文件;
		//		close(fd);    //关闭文件
		//int fflush(FILE *stream);   //刷新函数原型
		fflush(file);  //刷新缓存区

		int flags = O_RDONLY;  
		int fd = open(pathname,flags);
		if(fd < 0)
		{
			perror("open error");
			return 0;
		}
		//		ssize_t read(int fd, void *buf, size_t count); //read原型
		read(fd, buf+1024, sizeof(buf)-1024);  //读取文件
		fclose(file); //关闭文件
		printf("%s, sizeof = %lu", buf+1024,sizeof(buf)-1024);
	}
}
