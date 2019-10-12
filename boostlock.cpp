/*************************************************************************
    > File Name: boostlock.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2019年10月12日 星期六 17时38分36秒
 ************************************************************************/

#include<iostream>
#include<boost/thread.hpp>
using namespace std;
static boost::shared_mutex rwMutext;
typedef boost::shared_lock<boost::shared_mutex> ReadLock;
typedef boost::unique_lock<boost::shared_mutex> WriteLock;
int g_i = 0;

void fun()
{
	for (int i = 0; i < 100; i++)
	{
		WriteLock lock(rwMutext);
		cout << g_i++ << endl;
	}
}

int main(int argc, char** argv)
{
	boost::thread t1(fun);	
	boost::thread t2(fun);	

	t1.join();
	t2.join();
	return 0;
}

