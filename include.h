#ifndef INCLUDE_XIAOCS
#define INCLUDE_XIAOCS
//----------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>

#include<errno.h>

#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>

#include<sys/socket.h>
#include<signal.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

#include<sys/epoll.h>
int My_read(int fd, char *buf, int len);
int My_write(int fd, const char *buf, int len);

//-----------------------------------------------------------------------
#endif
