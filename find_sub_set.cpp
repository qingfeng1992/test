/*************************************************************************
    > File Name: find_sub_set.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2020年01月10日 星期五 21时29分36秒
 ************************************************************************/

#include<iostream>
#include<vector>
#include<string>
#include<memory>
#include<math.h>
using namespace std;
typedef std::shared_ptr<vector<vector<int> > > TDArrPtr;

TDArrPtr GetSubSet(vector<int> &vt)
{
	TDArrPtr ret(new vector<vector<int> >);
	if (vt.size() > sizeof(int))
	{
		return ret;
	}
	unsigned int nCount = pow(2, vt.size());
	for (unsigned int i = 0; i < nCount; i++)
	{
		vector<int> subSet;
		//检查对应的二进制位，为1的位表示集合中需要加入对应位置的数
		for (int j = 0; j < (int)vt.size(); j++)
		{
			unsigned int temp = (1 << j) & i;
			if (0 != temp)
			{
				subSet.push_back(vt[j]);
			}
		}
		ret->push_back(subSet);
	}
	return ret;
}

int main(int argc, char** argv)
{
	vector<int> vt;
	vt.push_back(1);
	vt.push_back(2);
	vt.push_back(3);
	TDArrPtr allSubSet = GetSubSet(vt);
	for (auto &arr : *allSubSet)
	{
		cout << "{";
		for (unsigned int k = 0; k < arr.size(); k++)
		{
			cout << arr[k];
			if (k != arr.size() - 1)
			{
				cout << ",";
			}
		}
		cout << "}";
		cout << endl;
	}

	cout << endl;
	return 0;
}

