#include<stdio.h>
#include<dirent.h>
#include<sys/types.h>
#include<string.h>
int judgename(const char *name)
{
	if(strstr(name,"mail") != NULL) //如果文件名中有mail就打印
	{
		printf("%s\n",name);
	}
	else		//没有就结束；
	{
	//	printf("NO:%s\n",name);
		return 0;
	}
	return 0;
}
int judgetype(const char *name, DIR *dirp)
{
	while(1)  //循环读取目录文件中每一条纪录文件；
	{
		struct dirent *attr = readdir(dirp); //返回下一条目录文件纪录保存的文件结构体
		if(attr == NULL)  //判断是否到末尾了；
			break;
		if(attr->d_type == 4)  //如果是==4 即为目录文件
		{
			if(strcmp(attr->d_name,"..") == 0) //跳过上级目录
			{
				continue;
			}
			else if(strcmp(attr->d_name,".") == 0)  //跳过再次打开当前目录
			{
				continue;
			}
			else
			{
				char buf[2048] = { 0 };
				sprintf(buf,"%s/%s",name,attr->d_name);  //如果是目录，拼接路径地址
				DIR*dirp = opendir(buf); //打开这个目录文件
				judgetype(buf, dirp); //递归再次查找
				closedir(dirp); //关闭目录文件；
			}
		}
		else   //不是目录文件的处理
		{
			judgename(attr->d_name);
		}
	}
	return 0;

}
int main()
{
	const char *name = "./"; 
	DIR *dirp = opendir(name); //打开目录文件；
	judgetype(name,dirp); 
	closedir(dirp);//关闭目录文件；
	return 0;
}
