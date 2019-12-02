/*************************************************************************
    > File Name: defual_value.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2019年11月07日 星期四 19时24分25秒
 ************************************************************************/

#include<iostream>
using namespace std;

class A
{
	public:
		virtual void fun(int i = 10){ cout << i << endl;}

};

class B: public A
{
	public:
		virtual void fun(int i = 20){ cout << i << endl;}

};

int main(int argc, char** argv)
{
	A *p = new B;
	p->fun();

	B b;
	b.fun();

	return 0;
}
