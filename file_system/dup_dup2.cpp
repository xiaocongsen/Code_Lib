#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
int main()
{
	const char *pathname = "b.txt";
	unlink(pathname);//如果存在删除；
	int fd = open(pathname, O_WRONLY | O_CREAT, 0777);
	write(1, "qhello\n", sizeof("qhello\n"));//dup2前往1描述符中写入数据；
	int newfd = dup(1); //备份一号描述符从前的指向；
	printf("备份stdout:%d\n", newfd);
	dup2(fd, 1); //将1描述符指向fd描述符对应的文件(讲新的描述符指向旧的描述符),返回值为newfd填写的描述符；
	close(fd);//关闭旧描述符
	write(1, "hhello\n", sizeof("hhello\n"));//dup2后往1描述符中写入数据；
	write(newfd, "word\n", sizeof("word\n"));//往备份1号文件描述符的对应文件写数据；
	dup2(newfd, 1);
	write(1, "fyhello\n", sizeof("fyhello\n"));//dup2复原后往1描述符中写入数据；
	close(newfd);
}
