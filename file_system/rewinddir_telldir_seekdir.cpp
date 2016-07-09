#include<stdio.h>
#include<dirent.h>
#include<sys/types.h>
#include<string.h>
int main()
{
	const char *pathname = "./"; 
	DIR* dirp = opendir(pathname);//打开文件目录
	struct dirent *ent = readdir(dirp);//读取目录一条文件纪录项
	ent = readdir(dirp);//再读
	ent = readdir(dirp);//再读
	ent = readdir(dirp);//再读
	long nonce = telldir(dirp); //保存当前文件纪录项的地址的位置
	ent = readdir(dirp);//再读
	printf("jl nonce : %s\n\n", ent->d_name);//打印当前文件名
	rewinddir(dirp);  //从新回到目录开头第一条
	while(1)
	{
		ent = readdir(dirp);
		if(ent == NULL)   //最后返回空
			break;
		printf("%s\n", ent->d_name);
	}
	seekdir(dirp, nonce);//回到记录的那条；
	ent = readdir(dirp);//读取下一条
	printf("\nhy nonce : %s\n", ent->d_name);//打印
	return 0;	
}
