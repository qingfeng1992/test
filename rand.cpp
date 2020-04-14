/*************************************************************************
    > File Name: rand.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2020年04月13日 星期一 12时13分32秒
 ************************************************************************/

#include<iostream>
#include<unistd.h>
using namespace std;

bool IsHitTheTarget(int nRatio)
{
	srand(time(NULL));//随机种子
	int nRand = rand() % 100;//产生一个0-99的随机值

	if (nRand <= nRatio - 1)
	{
		return true;
	}
	else
		return false;
}

int main (int argc, char** argv)
{
	int nCount = 0;

	int nNum = 10;
	for (int i = 0; i < nNum; i++)
	{
		sleep(1);
		if (IsHitTheTarget(30))
		{
			nCount++;
		}
	}
	cout << nCount << " ratio:"<< nCount / (double)nNum <<  endl;
	return 0;
}
