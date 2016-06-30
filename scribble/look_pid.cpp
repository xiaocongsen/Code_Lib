#include<stdio.h>
#include<stdlib.h>
int main()
{
	int index = 0;
	system("ps -aux > a.txt");
	FILE *file = fopen("./a.txt", "r");
	if(file == NULL)
	{
		perror("open error");
		return 0;
	}
	else
	{
		char buf[2048] = { 0 };
		while(fgets(buf,sizeof(buf),file))
		{
			char *p = buf;
			while(*p != ' ')
				++p;
			while(*p == ' ')
				++p;
			int a = atoi(p);
			if(a > 4000 && a < 5000)
				index++;
			printf("%d\n",a);
		}
	}
	printf("4000~5000之间的进程有%d个", index);
	fclose(file);
	return 0;
}
