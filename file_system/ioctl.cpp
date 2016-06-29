#include<stdio.h>
#include<unistd.h>
#include<sys/ioctl.h>
int main()
{
	struct winsize size;
	if(isatty(STDOUT_FILENO) == 0)  //判断终端是否打开
	{
		return -1;
	}
	printf("%d\n",isatty(STDOUT_FILENO)); //fd = 1; //指向了标准输出设备
	if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &size) < 0) //如果返回小于0,表示获取TIOCGWINSZ属性失败；
	{
		perror("ioctl TIOCGWINSZ error");
		return -2;
	}
	printf("%d rows, %d columns\n",size.ws_row, size.ws_col);//成功则打印TIOCGWINSZ的行和列值；
	return 0;
}
