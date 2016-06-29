#include<stdio.h>
#include<unistd.h>
int main()
{
//	 int access(const char *pathname, int mode);	
	const char *pathname = "hello.d";
	int mode = F_OK;
	int ret = access(pathname, mode); //检查次文件是否存在
	if(ret == -1)
	{
		perror("F_OK NO");
	}
	else
	{
		perror("F_OK yes");
	}
	mode = R_OK;
	ret = access(pathname, mode); //检查当前用户对该文件是否有read权限
	if(ret == -1)
	{
		perror("R_OK NO");
	}
	else
	{
		perror("R_OK yes");
	}
	mode = W_OK;
	ret = access(pathname, mode); //检查当前用户对该文件是否有write权限
	if(ret == -1)
	{
		perror("W_OK NO");
	}
	else
	{
		perror("W_OK yes");
	}
	mode = X_OK;
	ret = access(pathname, mode); //检查当前用户对该文件是否有EXEC权限
	if(ret == -1)
	{
		perror("X_OK NO");
	}
	else
	{
		perror("X_OK yes");
	}
}
