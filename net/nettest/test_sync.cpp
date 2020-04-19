/*************************************************************************
    > File Name: test_sync.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2018年09月14日 星期五 22时19分49秒
 ************************************************************************/

#include<iostream>
#include<pthread.h>
using namespace std;

 using namespace std;

 struct Lock
 {
     pthread_mutex_t mutex;
     pthread_cond_t cond;
     bool bReady;//A是否打印
 };

 Lock lock = {
     PTHREAD_MUTEX_INITIALIZER,
     PTHREAD_COND_INITIALIZER,
     false
 };

void* threadA(void* argv)
{
	for (int i=0; i<30; i++)
	{
		pthread_mutex_lock(&lock.mutex);
		// 检查标志位
		while(lock.bReady)
		{
			// 如果A打印了，B没打印，则等待
			pthread_cond_wait(&lock.cond, &lock.mutex);
		}
		cout << "A";
		lock.bReady = true;
		pthread_mutex_unlock(&lock.mutex);
		//唤醒可能在等待的线程B
		pthread_cond_signal(&lock.cond);
	}
	return NULL;
}

void* threadB(void* argv)
{	
	for (int i=0; i<30; i++)
	{
		pthread_mutex_lock(&lock.mutex);
		// 检查标志位
		while(!lock.bReady)
		{
			// 如果A打印了，B没打印，则等待
			pthread_cond_wait(&lock.cond, &lock.mutex);
		}
		cout << "B" << endl;
		lock.bReady = false;
		pthread_mutex_unlock(&lock.mutex);
		//唤醒可能在等待的线程B
		pthread_cond_signal(&lock.cond);
	}
	return NULL;
}

int main(int argc, char ** argv)
{
	// 创建两个线程
	pthread_t idA,idB;
	pthread_create(&idA, NULL, threadA, NULL);
	pthread_create(&idB, NULL, threadB, NULL);

	
	pthread_join(idA, NULL);
	pthread_join(idB, NULL);
	return 0;
}

