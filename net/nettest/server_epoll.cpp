/*************************************************************************
    > File Name: server_epoll.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2018年09月10日 星期一 22时32分48秒
 ************************************************************************/

#include<iostream>
#include<pthread.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<sys/epoll.h>
using namespace std;

#define MAX_BUFFER 1024
#define MAX_EVENT_NUMBER 1024
#define LISTENT_PORT 8889

int main(int argc, char** argv)
{
	int fdListen = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in servaddr;

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(LISTENT_PORT);
	inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr.s_addr);

	bool b = true;
	setsockopt(fdListen, SOL_SOCKET, SO_REUSEADDR, &b, sizeof(bool));
	socklen_t len;
	if (bind (fdListen ,(sockaddr*)&servaddr, sizeof(sockaddr_in)) < 0)
	{
		cout << "绑定端口失败:" << errno <<  endl;
		return 0;
	}

    if (listen(fdListen, 5) < 0)
	{
		cout << "监听失败" << endl;
		return 0;
	}
	else
	{
		cout << "服务器监听成功，端口:" << LISTENT_PORT << endl;
	}

	// 使用epoll模型
	int fdepoll = epoll_create(9);
	struct epoll_event event;
	event.events = EPOLLIN | EPOLLERR;
	event.data.fd = fdListen;// 将描述符保存到用户数据结构体里面，以便以后取出

	epoll_ctl(fdepoll, EPOLL_CTL_ADD, fdListen, &event);

	unsigned char recvbuff[MAX_BUFFER]= {0};
	struct epoll_event events[MAX_EVENT_NUMBER];
	// 事件循环
	while (true)
	{
		int nEvent = epoll_wait(fdepoll, events, MAX_EVENT_NUMBER, -1);

		if (nEvent == -1)
		{
			cout << "epoll_wait error" << endl;
			return 0;
		}

		for (int i=0; i < nEvent; i++)
		{

			if (fdListen == events[i].data.fd && events[i].events & EPOLLIN)
			{
				// 接收客户端连接
				sockaddr_in clientaddr;
				int fdClient = accept(fdListen, (sockaddr*)&clientaddr, &len);

				if (fdClient == -1)
				{
					cout << "accept error" << endl;
					return 0;
				}
				cout << "有客户端连接:" << fdClient << endl;
				//客户端连接的时候，不能一直设置EPOLLOUT,否则在LT模式下会一直触发的，cpu会空转
				// 一般的做法是，在write返回EAGAIN / EWOULDBLOCK时，才会给该套接字设置EPOLLOUT，然后在下次触发EPOLLOUT 后重新write刚才失败的数据，write成功后就删除EPOLLOUT这个标志
				event.events = EPOLLIN | EPOLLERR;
				event.data.fd = fdClient;
                epoll_ctl(fdepoll, EPOLL_CTL_ADD, fdClient, &event);				
			}
			else
			{
				int fd = events[i].data.fd;
				if (events[i].events & EPOLLIN)
				{
					int nRead = read(fd, recvbuff, MAX_BUFFER);
					if (nRead == 0)
					{
						cout << "客户端:" << fd << "正常关闭" << endl;
						epoll_ctl(fdepoll, EPOLL_CTL_DEL, fd, &events[i]);
					}
					else
					{
						write(fd, recvbuff, nRead);
					}
				}
				else if (events[i].events & EPOLLOUT)
				{
					cout << "fd:" << fd << "can write." << endl;
				}
				else 
				{
					cout << "fd:" << fd << "error" << endl;
					epoll_ctl(fdepoll, EPOLL_CTL_DEL, fd, &events[i]);

				}

			}
		}

	}


	return 0;
}
