/*************************************************************************
    > File Name: myserver.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2018年07月07日 星期六 18时58分04秒
 ************************************************************************/

#include<iostream>
#include<sys/socket.h>
#include<signal.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<assert.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<poll.h>
#include<errno.h>
//#include<limits.h> //for OPEN_MAX
using namespace std;

#define OPEN_MAX 10000
#define INFTIM -1
#define MAX_BUFFER_SIZE 8192
/**
 *主函数必须输入三个参数：ip地址， 端口号， 监听队列的长度
 *
 *
 */

bool bStop = false;

static void handle_term(int sig)
{
	bStop = true;
}

int main(int argc, char *argv[])
{
	if (argc < 4)
	{
		cout << "usage:" << argv[0] << " ip_address port_number backlog" << endl;
		return 1;
	}
	
	//设置为守护进程
	daemon(0, 0);
	
	int nPort = atoi(argv[2]);
	int nBacklog = atoi(argv[3]);
	signal(SIGTERM, handle_term);

	// 地址结构体
	sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	//serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	inet_pton(AF_INET, argv[1], &serveraddr.sin_addr.s_addr);
	serveraddr.sin_port = htons(nPort);

	int fdListen = socket(AF_INET, SOCK_STREAM, 0);
	bool b = true;
	setsockopt(fdListen, SOL_SOCKET, SO_REUSEADDR, &b, sizeof(bool));
	assert(fdListen > 0);
	if (fdListen < 0)
	{
		cout << "套接字创建失败" << endl;
		exit(-1);
	}
	else
	{
		cout << "创建套接字成功" << endl;
	}
	bind(fdListen, (sockaddr*)&serveraddr, sizeof(serveraddr));

	if (listen(fdListen, nBacklog) != -1)
	{
		cout << "套接字监听成功" << endl;
	}
	else
	{
		cout << "套接字监听失败" << endl;
	}

	// 利用poll模型
	struct pollfd fdClient[OPEN_MAX];
	int nMaxIndex = 0;//有效pollfd的最大下标
	fdClient[0].fd = fdListen;
	fdClient[0].events = POLLRDNORM;
	
	// 其他的pollfd设置为无效
	for (int i=1; i<OPEN_MAX; i++)
	{
		fdClient[i].fd = -1;
	}
	
	sockaddr_in clientaddr;
    socklen_t len = sizeof(sockaddr_in);
	char recvbuff[MAX_BUFFER_SIZE];

	//开始循环监听套接字状态
	while(true)
	{
		int nReady = poll(fdClient, nMaxIndex + 1,INFTIM);
		//先检查监听套接字
		if (fdClient[0].revents & POLLRDNORM)
		{
			//说明有连接，调用accept函数连接
			int client = accept(fdListen,(struct sockaddr*)&clientaddr, &len); 
			cout << "有新客户端连接" << endl;
			// 查找数组中索引最小的，可用的元素
			int i;
			for (i = 1; i < OPEN_MAX; i++)
			{
				if (fdClient[i].fd == -1)
				{
					fdClient[i].fd = client;
					fdClient[i].events = POLLRDNORM;
					// 更新最大索引
					if (i > nMaxIndex)
					{
						nMaxIndex = i;
					}
					break;
				}
			}

			// 连接数量超过最大值
			if (OPEN_MAX == i)
			{
				cout << "连接超过最大限制" << endl;
				return -1;
			}

			if (--nReady <= 0) 
			{
				// 如果没有其他套接字就绪，重新下一次循环等待
				continue;
			}
		}

		//检查客户套接字
		for (int i = 1; i <= nMaxIndex; i++ )
		{
			if (-1 == fdClient[i].fd)
			{
				// 跳过无效套接字
				continue;
			}

			if (fdClient[i].revents & (POLLRDNORM | POLLERR))
			{
				// 套接字可读或者发生错误
				int nRead = read(fdClient[i].fd, recvbuff, MAX_BUFFER_SIZE);
				// 根据read的返回值判断套接字的状态
				if (nRead <= 0)
				{
					//客户端发送FIN，结束连接
					if (0 == nRead)
					{
						cout << "有客户端正常中断连接" << endl;
					}
					else
					{
						// 连接出现错误
						if (errno != ECONNRESET)
						{
							cout << "客户端连接出现错误" << endl;
						}
					}
					close(fdClient[i].fd);
					fdClient[i].fd = -1;// 将这个套接字设为无效
					if (i == nMaxIndex)
					{
						// 如果关闭的是下标最大的套接字，最大下标减一
						nMaxIndex--;
					}

				}
				else
				{
				// 正常读取，回射
				write(fdClient[i].fd, recvbuff, nRead);

				}
				
			if (--nReady <= 0)
			{
				break;
			}
			}
		}
	}

	return 0;
}

