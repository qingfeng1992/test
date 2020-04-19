/*************************************************************************
    > File Name: test_pipe.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2018年08月30日 星期四 22时27分58秒
 ************************************************************************/
// 这是一个类似文件服务器的程序，客户端进行发送文件名给服务器，服务器返回文件内容或者错误信息
#include<iostream>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<wait.h>
using namespace std;

#define MAXPATH 256

void server(int fdRead, int fdWrite)
{
	cout << "执行服务器进程" << endl;
	// 从管道中读文件名
	char buff[MAXPATH + 1] = {0};
	int nRead;
	if ((nRead = read(fdRead, buff, MAXPATH)) == 0)
	{
		cout << "读取文件名时出错:" << strerror(errno) << endl;
	}

	buff[nRead] = '\0';

	//打开文件
	int fdFile = open(buff, O_RDONLY);
	if (fdFile < 0)
	{
		// 打开文件时出错，给客户端写入出错信息
		snprintf(buff + nRead, MAXPATH + 1 -nRead, ": can't open file, %s\n", strerror(errno));
		write(fdWrite, buff, strlen(buff));
		exit(0);
	}
	// 打开成共，向管道中写入文件
	while((nRead = read(fdFile, buff, MAXPATH)) > 0)
	{
		write(fdWrite, buff, nRead);
	}
	close(fdFile);//关闭文件
}

void client(int fdRead, int fdWrite)
{
	cout << "执行客户端进程" << endl;
	char buff[MAXPATH] = {0};
	cin >> buff;

	// 写入管道
	write(fdWrite, buff, strlen(buff));
	// 从管道中读出数据
	int nRead = 0;
	while((nRead = read(fdRead, buff, MAXPATH)) > 0)
	{
		cout << buff;
	}
}

int main(int argc, char** argv)
{
	int pipe1[2], pipe2[2];
	int fdChild;
	// 创建两个管道
	pipe(pipe1);
	pipe(pipe2);

	// 创建一个新的进程
	if ((fdChild = fork()) == 0)
	{
		//子进程
		close(pipe1[0]);
		close(pipe2[1]);
		server(pipe2[0], pipe1[1]);
		exit(0);
	}

	// 父进程
	close(pipe1[1]);
	close(pipe2[0]);
	client(pipe1[0], pipe2[1]);
	waitpid(fdChild, NULL, 0);// 等待子进程结束

	return 0;
}

