#include<stdio.h>
#include<unistd.h>
int main()
{
	const char* oldpath = "hello.d"; //现有的需要硬链接的路径和文件名；
	const char* Hnewpath = "hellh.d";  //需要新建的硬链接路径和名字；
	const char* Snewpath = "hellr.d";     
	link(oldpath, Hnewpath);	//创建硬链接；
	symlink(oldpath, Snewpath);      //创建软链接；
	unlink(Snewpath);    //删除文件；
	remove(Hnewpath);    //删除文件；
	return 0;
}
