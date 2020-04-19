/*************************************************************************
    > File Name: test_thread.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2018年07月08日 星期日 14时59分07秒

 ************************************************************************/

#include<iostream>
#include<pthread.h>
#include<unistd.h>
/**
 *创建两个线程，交替输出AAAAA和BBBBB
 */
using namespace std;

pthread_mutex_t mutexA = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t conA = PTHREAD_COND_INITIALIZER;

//pthread_mutex_t mutexB = PTHREAD_MUTEX_INITIALIZER;
//pthread_cond_t conB = PTHREAD_COND_INITIALIZER;
void* threadA(void *argv)
{
	while(true)
	{
		pthread_mutex_lock()
		cout << "AAAAA" << endl;
		pthread_cond_signal(&conA);
		pthread_cond_wait(&conA, &mutexA);
		sleep(1);
	}
	return NULL;
}

void * threadB(void *argv)
{
	while (true)
	{
		usleep(100);
		pthread_cond_wait(&conA, &mutexA);
		cout << "BBBBB" << endl;
		pthread_cond_signal(&conA);
		sleep(1);
	}
	return NULL;
}

int main()
{
	pthread_t tidA, tidB;

	pthread_create(&tidA, NULL, threadA, NULL);
	pthread_create(&tidB, NULL, threadB, NULL);

	pthread_join(tidA, NULL);
	pthread_join(tidB, NULL);

	return 0;
}

//void *threadfun(void* argv)
//{
//	cout << "进入子线程函数" << endl;
//	sleep(5);
//
//	cout << "子线程函数结束" << endl;
//	return NULL;
//}
//
//int main(int argc, char **argv)
//{
//	pthread_t tid;
//	
//	pthread_create(&tid, NULL, threadfun, NULL);
//
//	pthread_join(tid, NULL);
//
//	cout << "主线程结束" << endl;
//
//	return 0;
//
//}
