/*************************************************************************
  > File Name: semaphore.cpp
  > Author: ma6174
  > Mail: ma6174@163.com 
  > Created Time: 2019年08月26日 星期一 18时42分19秒
 ************************************************************************/
#include<memory.h>
#include<iostream>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#include<errno.h>

using namespace std;
sem_t sem1;
sem_t sem2;
sem_t sem3;
sem_t sem4;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t con = PTHREAD_COND_INITIALIZER;
bool bSet = false;
int nCount = 0;
int nIndex = 0;
char g_write[1032];

void* fun1(void* arg)
{
	int *intPtr = (int*)arg;
	int n = *intPtr;
	pthread_mutex_lock(&mutex);
	nCount = n; 
	bSet = true;
	pthread_mutex_unlock(&mutex);
	pthread_cond_broadcast(&con);//唤醒等待的所有线程,读取循环次数
	for (int i = 0; i < n; i++)
	{
		sem_wait(&sem1);//等待信号量
		//向数组里面输出字符A
		g_write[nIndex++] = 'A';
		//唤醒第二个线程
		sem_post(&sem2);
	}
	return NULL;
}

void* fun2(void* arg)
{
	//等待读取循环次数
	pthread_mutex_lock(&mutex);
	if (!bSet)//如果循环次数还没有被设置，则等待
		pthread_cond_wait(&con, &mutex);
	pthread_mutex_unlock(&mutex);

	int n = nCount;
	for (int i = 0; i < n; i++)
	{
		sem_wait(&sem2);	

		g_write[nIndex++] = 'B';
		//唤醒第3个线程
		sem_post(&sem3);
	}

	return NULL;
}

void* fun3(void* arg)
{
	//等待读取循环次数
	pthread_mutex_lock(&mutex);
	if (!bSet)//如果循环次数还没有被设置，则等待
		pthread_cond_wait(&con, &mutex);
	pthread_mutex_unlock(&mutex);

	int n = nCount;
	for (int i = 0; i < n; i++)
	{
		sem_wait(&sem3);	

		g_write[nIndex++] = 'C';
		//唤醒第4个线程
		sem_post(&sem4);
	}


	return NULL;
}

void* fun4(void* arg)
{
	//等待读取循环次数
	pthread_mutex_lock(&mutex);
	if (!bSet)//如果循环次数还没有被设置，则等待
		pthread_cond_wait(&con, &mutex);
	pthread_mutex_unlock(&mutex);

	int n = nCount;
	for (int i = 0; i < n; i++)
	{
		sem_wait(&sem4);	

		g_write[nIndex++] = 'D';
		//唤醒第4个线程
		sem_post(&sem1);
	}
	return NULL;
}

int main(int argc, char** argv)
{
	int nCount;
	while (cin >> nCount)
	{
		bSet = false;
		nIndex = 0;
		memset(g_write, 0, sizeof(g_write));
		con = PTHREAD_COND_INITIALIZER;
		mutex = PTHREAD_MUTEX_INITIALIZER;
		pthread_t tid1;
		pthread_t tid2;
		pthread_t tid3;
		pthread_t tid4;
		//pthread_mutex_init(&mutex,)
		sem_init(&sem1, 0, 1);
		sem_init(&sem2, 0, 0);
		sem_init(&sem3, 0, 0);
		sem_init(&sem4, 0, 0);
		pthread_create(&tid1, NULL, fun1, &nCount);
		pthread_create(&tid2, NULL, fun2, NULL);
		pthread_create(&tid3, NULL, fun3, NULL);
		pthread_create(&tid4, NULL, fun4, NULL);

		pthread_join(tid1, NULL);
		pthread_join(tid2, NULL);
		pthread_join(tid3, NULL);
		pthread_join(tid4, NULL);
		cout << g_write << endl;
	}
	return 0;
}
