/*************************************************************************
    > File Name: test2.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2019年10月12日 星期六 15时09分29秒
 ************************************************************************/

#include<iostream>
#include<set>
using namespace std;

class A
{
	public:
		char arr[20] = {0};
		int i;
};

class compare
{
	public:
		bool operator () (const A& a1, const A& a2)
		{
			return a1.i < a2.i;
		}
};

int main(int argc, char** argv)
{
	A a, b;
	a.arr[0] = 'h';
	a.arr[1] = 'e';
	a.arr[2] = 'l';
	a.arr[3] = 'l';
	a.arr[4] = 'o';

	b = a;
	cout << b.arr << endl;
	set<A, compare> s;
	s.insert(a);
	
	return 0; 
}
