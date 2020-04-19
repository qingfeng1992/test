/*************************************************************************
    > File Name: client.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2018年08月07日 星期二 10时46分06秒
 ************************************************************************/

#include<iostream>
#include<pthread.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdio.h>

using namespace std;

// 函数声明
int str_client(FILE *fp_arg, int sockfd_arg);

int main(int argc, char * argv[])
{
	int sockfd;
	struct sockaddr_in servaddr; 
	
	if (argc < 2)
	{
		cout << "usage: ip_address" << endl; 
		return 0;
	}
    	

	bzero(&servaddr, sizeof(servaddr));

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		cout << "创建套接字失败" << endl;
		return 0;
	}
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8888);
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr.s_addr);
	
	if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == 0)
	{
		cout << "服务器连接成功" << endl;
	}
	else 
	{
		cout << "服务器连接失败" << endl;
		return -1;
	}

	str_client(stdin, sockfd);

	return 0;
}
