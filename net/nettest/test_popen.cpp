/*************************************************************************
    > File Name: test_popen.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2018年08月31日 星期五 08时43分36秒
 ************************************************************************/

#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;

int main(int argc, char** argv)
{
	char buff[256] = {0};
	cout << "输入命令：";
	//cin.getline(buff, 256);
	cin.get(buff, 256);
	int len = strlen(buff);
	if (buff[len - 1] == '\n')
	{
		cout << "结尾有回车符" << endl;
	}
	//cin >> noskipws >> buff;
	FILE *fp = popen(buff, "r");
	
	while(fgets(buff, 256, fp) != NULL)
	{
		fputs(buff, stdout);
	}
	pclose(fp);

	return 0;
}
