/*************************************************************************
    > File Name: InnerClass.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2019年11月12日 星期二 17时52分18秒
 ************************************************************************/

#include<iostream>
using namespace std;

class Outer
{
	public:
		class Inner
		{
			public:
				int j = 2;
				void print()
				{
					cout << i << endl;
				}
				void print1()
				{
					if (NULL != m_pOuter)
					cout << m_pOuter->k << endl;
				}
			public:
				Outer  *m_pOuter = NULL;
		};
	private:
	  static int i;
	  int k = 9;
	
};

int Outer::i = 1;


int main (int argc, char** argv)
{
	Outer::Inner inner;
	Outer outer;
	inner.m_pOuter = &outer;
	inner.print();
	inner.print1();


	return 0;
}
