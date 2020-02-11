/*************************************************************************
    > File Name: erase.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2020年01月10日 星期五 18时35分16秒
 ************************************************************************/

#include<iostream>
#include<vector>
#include<map>
using namespace std;

int main(int argc, char** argv)
{

	map<int, int> v;
	v.insert(pair<int, int>(1, 1));
	v.insert(pair<int, int>(2, 2));
	v.insert(pair<int, int>(3, 3));

	for (auto it = v.begin(); it != v.end(); )
	{
		auto it1 = it++;
		cout << it1->first << endl;
		v.erase(it1);
	}

	cout << "end" << endl;

//	for (auto it = v.begin(); it != v.end(); it++)
//	{
//		cout << *it << endl;
//	}

	return 0;
}

