/*************************************************************************
    > File Name: BigIntegerAdd.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2020年02月02日 星期日 11时59分41秒
 ************************************************************************/

#include<iostream>
#include<string>

using namespace std;

string BigIntegerAdd(string strNum1, string strNum2)
{
	string strRet;
	if (strNum1.empty() || strNum2.empty())
	{
		return strRet;	
	}

	//确定两个数的符号
	bool bNum1Minus = false;//加数1是否为负数
	bool bNum2Minus = false;//加数2是否为负数

	if ('-' == strNum1[0])
	{
		bNum1Minus = true;
		//去掉字符串前面的负号
		strNum1.erase(0, 1);
	}

	if ('-' == strNum2[0])
	{
		bNum2Minus = true;
		strNum2.erase(0, 1);
	}

	//找出比较大的那个数
	string &strLarger = (strNum1.size() > strNum2.size() || (strNum1.size() == strNum2.size() && strNum1 > strNum2)) ? strNum1 : strNum2;
	string &strSmaller = &strLarger != &strNum1 ? strNum1 : strNum2;

	//结果的符号和较大数的符号相同
	bool bResultMinus = false;
	if (&strLarger == &strNum1)
	{
		bResultMinus = bNum1Minus;
	}
	else 
	{
		bResultMinus = bNum2Minus;
	}
	bool bZero = true;//结果是否为0
	//符号相同
	if (bNum1Minus == bNum2Minus)
	{
		//执行加法
		int i = strLarger.size() - 1;
		int j = strSmaller.size() - 1;
		int carry = 0;//进位标志
		for (; i >= 0; i--)
		{
			//从最低位开始加起，按照人工计算的方式
			int num1 = strLarger[i] - '0';
			int num2 = 0;
			if (j >= 0)
				num2 = strSmaller[j--] - '0';
			
			int sum = num1 + num2 + carry;
			//判断下一轮是否要进位
			if (sum > 9)
			{
				carry = 1;
				sum %= 10;//只取个位数
			}
			else 
			{
				carry = 0;
			}
			//拼接结果
			if (0 != sum)
			{
				bZero = false;
			}
			strRet = std::to_string(sum) + strRet;
		}
		if (1 == carry)
		{
			strRet = "1" + strRet;
		}
	}
	else 
	{
		//执行减法
		int i = strLarger.size() - 1;
		int j = strSmaller.size() - 1;
		int borrow = 0;//借位标志
		for (; i >= 0; i--)
		{
			//从最低位开始减起，按照人工计算的方式
			int num1 = strLarger[i] - '0';
			int num2 = 0;
			if (j >= 0)
				num2 = strSmaller[j--] - '0';
			//判断是否要借位
			int diff = num1 - num2 - borrow;
			if (diff < 0)
			{
				//需要借位
				diff = 10 + num1 - num2 - borrow;
				borrow = 1;
			}
			else 
			{
				borrow = 0;
			}
			//拼接结果
			if (0 != diff)
			{
				bZero = false;
			}
			strRet = std::to_string(diff) + strRet;
		}
			
	}

	//拼接负号
	if (bResultMinus && !bZero)
	{
		strRet = "-" + strRet;
	}

	return strRet;
}


int main(int argc, char** argv)
{

	string str1,str2;
	while (cin >> str1 >> str2)
	{
		cout << BigIntegerAdd(str1, str2) << endl;
	}
	return 0;
}
