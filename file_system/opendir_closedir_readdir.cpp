#include<stdio.h>
#include<dirent.h>
#include<sys/types.h>
#include<string.h>
int judgename(const char *name)
{
	if(strstr(name,"mail") != NULL)
	{
		printf("%s\n",name);
	}
	else
	{
	//	printf("NO:%s\n",name);
		return 0;
	}
	return 0;
}
int judgetype(const char *name, DIR *dirp)
{
	while(1)
	{
		struct dirent *attr = readdir(dirp);
		if(attr == NULL)
			break;
		if(attr->d_type == 4)
		{
			if(strcmp(attr->d_name,"..") == 0)
			{
				continue;
			}
			else if(strcmp(attr->d_name,".") == 0)
			{
				continue;
			}
			else
			{
				char buf[2048] = { 0 };
				sprintf(buf,"%s/%s",name,attr->d_name);
				DIR*dirp = opendir(buf);
				judgetype(buf, dirp);
				closedir(dirp);
			}
		}
		else
		{
			judgename(attr->d_name);
		}
	}
	return 0;

}
int main()
{
	const char *name = "./";
	DIR *dirp = opendir(name);
	judgetype(name,dirp);
	closedir(dirp);
	return 0;
}
