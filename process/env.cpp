#include<stdio.h>
#include<stdlib.h>

int main()
{
	const char *setname = "XIAO"; //设置键值名
	const char *setvalue = "帅呆了"; //设置键值；
	int overwrite = 1;		//是否覆盖，0为不覆盖原来的定义（键名存在就不覆盖键值），也不返回错误，非0，覆盖原来的定义；
	if(setenv(setname,setvalue,overwrite))//设置键值进当前程序的环境变量里
	{	
		perror("setenv error");
		return -1;
	}
	else
	{
		char *value = NULL;
		const char *name = "XIAO";
		value = getenv(name);	//指定键值名获得当前进程的name的键值
		if(value == NULL)
		{
			printf("%s\n", value);
			return -1;
		}
		else
		{
			printf("%s\n",value);
		}
		if(unsetenv(name))//删除当前进程的键值
		{
			perror("unsetenv error");
			return -1;
		}
		else
		{
			printf("删除后：%s\n", getenv(name));//删除后打印为空；
		}
	}
	return 0;
}
