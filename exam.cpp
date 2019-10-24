/*************************************************************************
    > File Name: exam.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2019年10月24日 星期四 19时22分41秒
 ************************************************************************/

#include<iostream>
#include<vector>
#include<set>
using namespace std;

int main (int argc, char** argv)
{

	set<string> setStr;
	vector<string> vtStr;
	char chArr[5] = {0};
	int nAdd = 'a' - 1;

	for (int n1 = 1; n1 < 26; n1++)
	{
		for (int n2 = 0; n2 < 26; n2++)
		{
			for (int n3 = 0; n3 < 26; n3++)
			{
				for (int n4 = 0; n4 < 26; n4++)
				{
					chArr[0] = n1 + nAdd;	

					chArr[1] = n2;
					if (n2 != 0)
					{
						chArr[1] = n2 + nAdd;
					}
				
					chArr[2] = n3;
					if (n3 != 0)
					{
						chArr[2] = n3 + nAdd;
					}
				
					chArr[3] = n4;
					if (n4 != 0)
					{
						chArr[3] = n4 + nAdd;
					}
					string str = chArr;
					setStr.insert(str);
				}
			
			}
		
		}
	
	}

	for (auto it = setStr.begin(); it != setStr.end(); it++)
	{
		vtStr.push_back(*it);
	}


	string inStr;
	while (cin >> inStr)
	{
		for (int i = 0; i < (int)vtStr.size(); i++)
		{
			if (inStr == vtStr[i]) 
			{
				cout << i << endl;
			}
		}
	}


	return 0;
}


