/*************************************************************************
    > File Name: boostlock.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2019年10月12日 星期六 17时38分36秒
 ************************************************************************/

#include <unistd.h>
#include<pthread.h>
#include<iostream>
#include<boost/thread.hpp>
#include<set>
using namespace std;
static boost::shared_mutex rwMutext;
typedef boost::shared_lock<boost::shared_mutex> ReadLock;
typedef boost::unique_lock<boost::shared_mutex> WriteLock;
int g_i = 0;
set<int> g_s;

void fun()
{
	for (int i = 0; i < 10; i++)
	{
	//	WriteLock lock(rwMutext);
	    int j = g_i++;
		cout << pthread_self() << ":" <<j << endl;
		auto it = g_s.find(j);
		if (it != g_s.end())
		{
			cout << "repeat num：" << j;
		}
		else 
		{
			g_s.insert(j);
		}

		//usleep(1000*10);
	}
}

int main(int argc, char** argv)
{
	boost::thread t1(fun);	
	//usleep(1000*5);
	boost::thread t2(fun);	
	//usleep(1000*5);
	boost::thread t3(fun);	
	//usleep(1000*5);
	boost::thread t4(fun);	

	t1.join();
	t2.join();
	t3.join();
	t4.join();
	return 0;
}

