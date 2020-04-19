/*************************************************************************
    > File Name: test_crreatesem.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2018年10月06日 星期六 14时28分14秒
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
#define     FILE_MODE       (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
void err_quit()
{
	cout << "errno:" << errno << " error message:" << strerror(errno) << endl;
	exit(0);
}

int main(int argc, char ** argv)
{
	int c, flags;
	sem_t *sem;
	unsigned int value;

	flags = O_RDWR | O_CREAT;
	value = 1;
	while ((c = getopt(argc, argv, "ei:")) != -1)
	{
		switch (c)
		{
			case 'e':
				flags |= O_EXCL;
				break;

			case 'i':
				value = atoi(optarg);
				break;
		}
	}
	if (optind != argc - 1)
	{
		cout << "usage: " << argv[0] << " [-e] [-i initalvaule] <name>";
		return 0;
	}

	sem = sem_open(argv[optind], flags, FILE_MODE, value);
	if (NULL == sem)
	{
		err_quit();
	}
	sem_close(sem);
	return 0;
}

