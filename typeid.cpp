/*************************************************************************
    > File Name: typeid.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2020年04月27日 星期一 11时24分12秒
 ************************************************************************/

#include<iostream>
#include<typeinfo>
using namespace std;

class A
{
	public:
	int a = 0;
};

int main(int argc, char **argv)
{
	cout << typeid(A).name() << endl;
	cout << typeid(1.0f).name() << endl;
	return 0;
}
