/*************************************************************************
    > File Name: pthread_test.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2019年10月13日 星期日 15时02分35秒
 ************************************************************************/

#include<iostream>
#include<unistd.h>
#include<boost/thread.hpp>
#include<pthread.h>
using namespace std;

static boost::shared_mutex rwMutext;
typedef boost::shared_lock<boost::shared_mutex> ReadLock;
typedef boost::unique_lock<boost::shared_mutex> WriteLock;
const int num = 10;
int g_i = 0;

void* fun(void*)
{
	WriteLock lock(rwMutext);
	usleep(1000*50);
	g_i++;
	
	usleep(1000*50);
	cout << g_i << endl;
	return NULL;
}

int main(int argc, char** argv)
{
	pthread_t t[num];

	for (int i=0; i<num; i++)
	{
		pthread_create(&t[i], NULL, fun, NULL);
	}
	for (int i=0; i<num; i++)
	{
		pthread_join(t[i], NULL);
	}

	return 0;
}

