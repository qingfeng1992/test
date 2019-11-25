/*************************************************************************
    > File Name: arithmetic.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2019年11月25日 星期一 10时30分04秒
 ************************************************************************/

#include<iostream>
using namespace std;
#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;
vector<vector<char>> priority;//符号优先级列表，序号越低，优先级越低

int GetPriority(char ch)
{
	int pri = 0;
	for (int i = 0; i < (int)priority.size(); i++)
	{
		vector<char> &samePri = priority[i];
		for (int j = 0; j < (int)samePri.size(); j++)
		{
			if (ch == samePri[j])
			{
				pri = i;
				break;
			}
		}
	}

	return pri;
}

int calculate(string strExpression)
{
	strExpression += '#';
	string strOperNum;//存放操作数
	vector<string> infixExp;//中缀表达式结果
	stack<char> st;
	st.push('#');//辅助字符先进栈


	//扫描字符串
	for (int i = 0; i < (int)strExpression.size(); i++)
	{
		char ch = strExpression[i];
		if (ch >= '0' && ch <= '9')
		{
			//是操作数
			strOperNum += ch;
		}
		else 
		{
			//是运算符
			//先把前面的操作数输出
			if (!strOperNum.empty())
			{
				infixExp.push_back(strOperNum);
				strOperNum.clear();//清空缓存
			}

			int x2 = GetPriority(ch);//当前字符优先级
			while (true)
			{
				//取栈顶元素优先级
				char stCh = st.top();
				int x1 = GetPriority(stCh);

				//当前字符优先级比栈顶元素优先级高，则入栈
				if (x2 > x1)
				{
					st.push(ch);
					break;//跳出循环
				}
				else 
				{
					//当前字符优先级比栈顶元素低，或者优先级相等，都要出栈，因为同一优先级要从左到右
					st.pop();
					//检查是否是左右括号,或者是结束符
					if((stCh == '(' && ch == ')')  || (stCh == '[' && ch == ']') || (stCh == '{' && ch == '}') || (stCh == '#' && ch == '#'))	
					{
						break;
					}
					else 
					{
						//是运算符，则放入中缀表达式
					    char strArr[2] = {0};
						strArr[0] = stCh;
						infixExp.push_back(strArr);
					}

				}
			}

		}

	}

	//计算中缀表达式的值
	int nRet = 0;
	stack<int> stNum;//操作数

	for (int i = 0; i < (int)infixExp.size(); i++)
	{
		string &str = infixExp[i];
		if ("+" ==str)
		{
			//取出栈顶的两个元素来运算	
			int x2 = stNum.top(); 
			stNum.pop();
			int x1 = stNum.top();
			stNum.pop();
			int result = x1 + x2;
			//计算完成后入栈
			stNum.push(result);
		}
		else if ("-" == str)
		{//取出栈顶的两个元素来运算	
			int x2 = stNum.top(); 
			stNum.pop();
			int x1 = stNum.top();
			stNum.pop();
			int result = x1 - x2;
			//计算完成后入栈
			stNum.push(result);
		
		}
		else if ("*" == str)
		{
			int x2 = stNum.top(); 
			stNum.pop();
			int x1 = stNum.top();
			stNum.pop();
			int result = x1 * x2;
			//计算完成后入栈
			stNum.push(result);
		}
		else if ("/" == str)
		{
			//取出栈顶的两个元素来运算	
			int x2 = stNum.top(); 
			stNum.pop();
			int x1 = stNum.top();
			stNum.pop();
			int result = x1 / x2;
			//计算完成后入栈
			stNum.push(result);
		}
		else 
		{
			//操作数入栈
			stNum.push(atoi(str.c_str()));
		}

	}

	nRet = stNum.top();//最后的栈顶元素就是结果

	return nRet;
}

int main(int argc, char** argv)
{
	vector<char> samePri;//同一个优先级的运算符

	samePri.push_back('#');//辅助字符，优先级最低
	priority.push_back(samePri);

	samePri.clear();
	samePri.push_back('}');//右括号的优先级最低
	priority.push_back(samePri);

	samePri.clear();
	samePri.push_back(']');//右括号的优先级最低
	priority.push_back(samePri);

	samePri.clear();
	samePri.push_back(')');//右括号的优先级最低
	priority.push_back(samePri);

	samePri.clear();
	samePri.push_back('+');//加减同一个优先级   
	samePri.push_back('-');
	priority.push_back(samePri);

	samePri.clear();
	samePri.push_back('*');//乘除同一个优先级   
	samePri.push_back('/');
	priority.push_back(samePri);

	samePri.clear();
	samePri.push_back('{');//左括号的优先级最高
	priority.push_back(samePri);

	samePri.clear();
	samePri.push_back('[');//左括号的优先级最高
	priority.push_back(samePri);

	samePri.clear();
	samePri.push_back('(');//左括号的优先级最高
	priority.push_back(samePri);

	string strIn;
	while (cin >> strIn)
	{
		cout << calculate(strIn) << endl;;
	}

	return 0;
}
