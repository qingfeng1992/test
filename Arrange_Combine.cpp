#include <iostream>
#include <string>
#include <vector>
using namespace std;

//从集合中取m个元素的所有组合
vector<vector<int>> Combine(vector<int> &vt, int m)
{
	vector<vector<int> > ret;
	if (vt.size() < m)
	{
		return ret;
	}

	//如果是集合大小vt.size() 和 m相同，也可以确定结果，相当于在有m个元素的集合里面取m个元素的组合，只有一种
	//因此不需要往后做多余的递归调用
	if (vt.size() == m)
	{
		ret.push_back(vt);
		return ret;
	}

	//递归出口
	if (1 == m)
	{
		for (auto &item : vt)
		{
			vector<int> vtTemp;
			vtTemp.push_back(item);
			ret.push_back(vtTemp);
		}
		return ret;
	}
	int i = 1;
	for (auto it = vt.begin(); it != vt.end() && (vt.size() - i) >= (m - 1); it++, i++)
	{
		//单趟循环，得到的集合中，取出的m个元素中必含有当前元素it，下一个循环得到的集合中，必不含有前一个循环必定会包含的元素
		//这就做到每次循环都不会有重复的集合
		//依次对剩下的元素进行取m-1个元素的递归调用
		//但是剩下的元素要满足元素个数大于等于m-1这个条件，避免无谓的递归调用
		if (it + 1 != vt.end())
		{
			vector<int> vtBack(it + 1, vt.end());
			vector<vector<int>> vtCombi1 = Combine(vtBack, m - 1);
			//加入当前元素
			for (auto &item : vtCombi1)
			{
				item.push_back(*it);
			}
			ret.insert(ret.end(), vtCombi1.begin(), vtCombi1.end());
		}
		
	}

	return ret;
}

//从集合中取m个元素进行全排，递归实现
vector<vector<int> > Arrange(vector<int> &vt, int m)
{
	vector<vector<int> > ret;
	if (vt.size() < m)
	{
		return ret;
	}

	//递归出口，当递归到m=1时，就可以确定所有的集合
	if (1 == m)
	{
		for (auto &item : vt)
		{
			vector<int> vtTemp;
			vtTemp.push_back(item);
			ret.push_back(vtTemp);
		}
		return ret;
	}

	for (auto it = vt.begin(); it != vt.end(); it++)
	{
		//取集合中的一个元素，然后让剩下的元素取m-1个元素进行全排，递归
		vector<int> vtTemp;
		//取当前元素的前面部分元素
		if (it != vt.begin())
		{
			vtTemp.insert(vtTemp.end(), vt.begin(), it);
		}
		//取当前元素的后面部分
		if (it + 1 != vt.end())
		{
			vtTemp.insert(vtTemp.end(), it + 1, vt.end());
		}
		vector<vector<int> > vtArrage = Arrange(vtTemp, m - 1);//递归，分解问题
		//把当前元素加入集合,并把集合加入结果集
		for (auto &vtSet : vtArrage)
		{
			auto itInsert = ret.insert(ret.end(), vtSet);
			itInsert->push_back(*it);//加入当前元素
		}
	}

	return ret;
}

int main(int argc, char** argv)
{
	vector<int> vt = { 1, 2, 3 ,4, 5};
	vector<vector<int>> ret = Combine(vt, 2);
	//vector<vector<int>> ret = Arrange(vt, 2);

	for (auto &vtInt : ret)
	{
		for (auto &item : vtInt)
		{
			cout << item << "";
		}
		cout << endl;
	}

	cout << "size:" << ret.size() << endl;
	return 0;
}
