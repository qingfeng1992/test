/*************************************************************************
    > File Name: main.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2020年09月17日 星期四 17时30分09秒
 ************************************************************************/

#include<iostream>
#include"threadpool.h"
#include <memory.h>
#include <stdlib.h>
using namespace std;

static void doSomething(void* arg)
{
	nJob *pJob = (nJob*) arg;
	cout << "用户函数输出:"  <<*(int*)pJob->user_data << endl;
	free(pJob->user_data);
	free(pJob);
}

int main (int argc, char** argv)
{
	nThreadPool pool;
	nCreateThreadPool(&pool, 6);

	for (int i = 0; i < 10; i++)
	{
		nJob *pJob = (nJob*)malloc(sizeof(nJob));
		memset(pJob, 0, sizeof(nJob));
		pJob->user_data = malloc(sizeof(int));
		pJob->fun = doSomething;
		*(int*)pJob->user_data = i;
		nThreadPoolJobPush(&pool, pJob);
	}
	nThreadPoolShutdown(&pool);
	int i;
	cin >> i;

	return 0;
}

