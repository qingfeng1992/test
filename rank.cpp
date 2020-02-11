/*************************************************************************
    > File Name: rank.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2020年02月11日 星期二 21时10分36秒
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;
void arrange(vector<int> &v, vector<int> &vCombo)
{
	//递归出口
	if (1 == v.size())
	{
		vCombo.push_back(v[0]);
		for (auto item : vCombo)
		{
			cout << item;
		}
		cout << endl;
		return;
	}


	for (auto it = v.begin(); it != v.end(); it++)
	{
		//递归
		vector<int> v1;
		vector<int> vCombo1 = vCombo;
		vCombo1.push_back(*it);
		v1.insert(v1.end(), v.begin(), it);	
		v1.insert(v1.end(), it + 1, v.end());
		arrange(v1, vCombo1);
	}
	
}

int main(int argc, char** argv)
{

	vector<int> v = {1, 2, 3, 4};
	vector<int> vCombo;
	arrange(v, vCombo);
	return 0;
}
