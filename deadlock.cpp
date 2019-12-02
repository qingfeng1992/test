/*************************************************************************
    > File Name: deadlock.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2019年10月14日 星期一 16时08分15秒
 ************************************************************************/

#include<iostream>
#include<boost/thread.hpp>
using namespace std;

typedef boost::shared_mutex rwMutex;
typedef boost::unique_lock<boost::shared_mutex> wrLock;

int main(int argc, char** argv)
{
	wrLock lock1(rwMutex);
	wrLock lock2(rwMutex);

	cout << "end." << endl;
	return 0;
}
