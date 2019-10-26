/*************************************************************************
    > File Name: tencent_exam3.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2019年10月26日 星期六 14时12分58秒
 ************************************************************************/

#include<iostream>
using namespace std;
#define DEF_COUNT 32

void SetFinish(unsigned int *arr, int nIndex)
{
	int nCol = (nIndex - 1) / 32;
	int nPos = (nIndex - 1) % 32;
	unsigned int val = 0x00000001;
	val <<= nPos;
	arr[nCol] |= val; 
}

int CheckIsFinish(unsigned int *arr, int nIndex)
{
	int nCol = (nIndex - 1) / 32;
	int nPos = (nIndex - 1) % 32;
	unsigned int val = 0x00000001;
	val <<= nPos;
	unsigned int result = arr[nCol] & val; 
	if (0 == result)
	{
		return 0;
	}
	else 
	{
		return 1;
	}
}

int main(int argc, char** argv)
{
	unsigned int arr[DEF_COUNT] = {0};

	int in1, in2;
	while (cin >> in1 >> in2)
	{
		if (in1 < 1 || in1 > 1024 || in2 < 1 || in2 > 1024)
		{
			cout << 1 << endl;	
			continue;
		}
	    
		SetFinish(arr, in1);

		cout << CheckIsFinish(arr, in2) << endl;
		
	}

	return 0;
}
