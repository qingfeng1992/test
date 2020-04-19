/*************************************************************************
    > File Name: test_mmap.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2018年10月06日 星期六 11时44分40秒
 ************************************************************************/

#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>
#include<sys/mman.h>
#include<semaphore.h>
using namespace std;
#define     SEM_NAME "/tmp/mysem"
#define     FILE_MODE       (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

void err_quit()
{
	cout << "errno:" << errno << " error message:" << strerror(errno) << endl;
	exit(0);
}

int main( int argc, char **argv)
{
	int zero = 0;
	int *ptr = NULL;
	if (argc < 3)
	{
		cout << "usage:" << argv[0] << "<pathname> <#loops>" << endl;
		return 0;
	}

	int nloop = atoi(argv[2]);

	// 打开文件
	int fd = open(argv[1], O_RDWR | O_CREAT, FILE_MODE);//读写权限打开，没有则创建
	if (fd < 0)
	{
		err_quit();
	}
	write(fd, &zero, sizeof(int));//在文件中写入一个0

	// 申请共享内存
	ptr = (int*)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	if(NULL == ptr)
	{
		err_quit();
	}
	close(fd);// 关闭文件，没有影响

	// 创建有名信号量
    sem_t *mutex = sem_open(SEM_NAME, O_CREAT | O_RDWR, FILE_MODE, 1);
	if (NULL == mutex)
	{
		err_quit();
	}
	sem_unlink(SEM_NAME);//删除信息量的文件，不会对信息量有影响，这样这个文件也不会因为程序的意外终止而没有删除
	setbuf(stdout, NULL);//关闭输出缓冲区
	
	// 创建两个进程
	if (fork() == 0)
	{
		//子进程
		for (int i=0; i < nloop; i++)
		{
			sem_wait(mutex);
			cout << (*ptr)++ << " ";
			sem_post(mutex);
		}
		exit(0);
	}
	else 
	{
		// 父进程
		for (int i = 0; i < nloop; i++)
		{
			sem_wait(mutex);
			cout << (*ptr)++ << " ";
			sem_post(mutex);
		}
		exit(0);
	}

	return 0;
}
