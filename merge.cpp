/*************************************************************************
    > File Name: merge.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2019年10月15日 星期二 17时41分17秒
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;


int main(int argc, char** argv)
{
	vector<int> c;
	int a[] = {1, 2, 3, 6};
	int b[] = {0, 2, 4};
	int n1 = 4;
    int n2 = 3;	
	int i = 0, j = 0;
	for (; i < n1 && j < n2;)
	{	
		if (a[i] < b[j])
		{
			c.push_back(a[i]);
			i++;
		}
		else if (a[i] > b[j])
		{
			c.push_back(b[j]);
			j++;
		}
		else
		{
			c.push_back(b[j]);
			c.push_back(a[i]);
			i++;
			j++;
		}
	}

	for (;i < n1; i++)
	{
		c.push_back(a[i]);
	}

	for (;j < n2; j++)
	{
		c.push_back(b[j]);
	}

	for (int k = 0; k < (int)c.size(); k++)
	{
		cout << c[k] << " ";
	}

	return 0;
}
