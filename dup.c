#include"xiaocs.h"
int dou(int Of,int file,char *tmp,int num)
{
	dup2(Of,1);
	write(file,tmp,num);
	printf("2%s\n",tmp);
	close(Of);
	return 0;
}
int main()
{
	char tmp[] = "xiaocongsen";
	int file = open("a.txt",O_WRONLY|O_CREAT,0777);
	int Of = dup(1);
	dup2(file,1);
	close(file);
	write(file,tmp,sizeof(tmp));
	printf("1%s\n",tmp);
	fflush(stdout);
	dou(Of,file,tmp,sizeof(tmp));
	return 0;
}

