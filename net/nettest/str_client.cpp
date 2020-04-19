/*************************************************************************
    > File Name: str_client.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2018年08月08日 星期三 17时17分08秒
 ************************************************************************/

#include<iostream>
#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>

using namespace std;

#define MAX_BUFFER_SIZE 8192

static FILE *fp;
static int sockfd;

void * thread_fun(void *arg)
{

	// 子线程监控标准输入
	char sendbuff[MAX_BUFFER_SIZE];

	while (fgets(sendbuff, MAX_BUFFER_SIZE, fp) != NULL)
	{
		write(sockfd, sendbuff, strlen(sendbuff));

	}

	// 当输入EOF,关闭写
	shutdown(sockfd, SHUT_WR);

	return NULL;
}

int str_client(FILE *fp_arg, int sockfd_arg)
{
	fp = fp_arg;
	sockfd = sockfd_arg;
	pthread_t tid;

	pthread_create(&tid, NULL, thread_fun, NULL);

	// 主进程监控套接字的数据
	int nRead = 0;
	char buff[MAX_BUFFER_SIZE];

	while ((nRead = read(sockfd, buff, MAX_BUFFER_SIZE)) > 0)
	{
		buff[nRead] = '\0';
		fputs(buff, stdout);
	}
    
	return 0;
}
