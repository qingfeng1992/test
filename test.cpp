/*************************************************************************
    > File Name: test.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2019年10月13日 星期日 12时37分06秒
 ************************************************************************/

#include<iostream>
#include<set>
#include<vector>
using namespace std;

class A
{
	public:
		A()
		{
			cout << "A construct " << ++nObjCount << endl;
		}
		A(const A &other)
		{
			cout << "copy construct " << ++nObjCount << endl;	
			i = other.i;
			d = other.d;
		}
		A& operator = (const A &other)
		{
			cout << "A operator =" << endl;	

			//赋值函数一定要检查自赋值
			if (this != &other)
			{
				i = other.i;
				d = other.d;
			}
			return *this;
		}

		~A()
		{
			cout << "A destruct" << endl;
		}
	public:
		bool operator < (const A &other) const
		{
			return i < other.i;	
		}
	public:
		int i;
		double d;
		static int nObjCount;
		
};

int A::nObjCount = 0;

void AddElement(set<A> &s)
{
	A a;
	A a1;
	a1.i = -1;
	a.i = 9;
	s.insert(a);
	s.insert(a1);
}

void AddElement(vector<A> &v)
{
	A a;
	A a1;
	a1.i = -1;
	a.i = 9;
	v.push_back(a);
	v.push_back(a1);
}

int main()
{
	//set<A> s;
//	vector<A> v;
//	AddElement(v);
//	for (auto &item : v)
//	{
//		cout << item.i << " ";
//	}
//	}
//
int i = 0;
i = +8+-5;
cout << i << endl;
	return 0;
}
