#include<stdio.h>
#include<string.h>
#include<sys/mman.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
int main(int argc, char **argv)
{
	if(argc < 3)
	{
		printf("参数不够,需要有复制的文件名和复制后的文件名\n");
		return -1;
	}
	else
	{
		char *oldpathname = argv[1]; //需要复制的文件名；
		char *newpathname = argv[2]; //复制后的文件名
		int oldfd = open(oldpathname, O_RDONLY); //用读打开需要复制的文件
		struct stat stat; //创建文件属性结构体
		fstat(oldfd, &stat); //获取需要复制的文件属性结构体
		int total_size = stat.st_size; //获取文件大小
		char *oldbegin = (char *)mmap(NULL, total_size, PROT_READ, MAP_SHARED, oldfd, 0); //把需要复制的文件整个映射到内存中；MAP_SHARED共享;
		if(oldbegin == MAP_FAILED) //判断映射是否失败；
		{
			perror("mmap old error");
			return -1;
		}
		int newfd = open(newpathname, O_RDWR|O_CREAT, 0777);  //创建字节为0的文件；
		ftruncate(newfd, total_size); //截断创建的文件到total_size个字节；
		char *newbegin = (char *)mmap(NULL, total_size, PROT_READ | PROT_WRITE, MAP_SHARED, newfd, 0);//把这个文件也映射到系统内存中.PROT_READ PROT_WRITE 可读|可写.
		if(newbegin == MAP_FAILED)
		{
			perror("mmap new error");
			return -1;
		}
		memcpy(newbegin, oldbegin, total_size); //将内存oldbegin开始长total_size的数据拷贝到newbegin开始的地址；
		munmap(oldbegin, total_size); //卸载映射；
		munmap(newbegin, total_size); 
		close(newfd);
		close(oldfd);		
	}
	return 0;
}
