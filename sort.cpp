/*************************************************************************
    > File Name: sort.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2019年10月08日 星期二 16时47分06秒
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;

void bubblesort(int arr[], int n)
{
	for (int end = n - 1; end > 1; end--)
	{
		bool bNoExchange = true;
		for (int j = 0; j < end ; j++)
		{
			if (arr[j] > arr[j + 1])	
			{
				int temp = arr[j];
				arr[j] = arr[j +1];
				arr[j +1] = temp;
				bNoExchange = false;
			}
		}

		if (bNoExchange)
		{
			break;
		}
	}

}

void selected_sort(int arr[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		int nIndex = i;
		for (int j = i + 1; j < n; j++)
		{
			if (arr[j] < arr[nIndex])
			{
				nIndex = j;
			}
		}

		//交换
		int tmp = arr[i];
		arr[i] = arr[nIndex];
		arr[nIndex] = tmp;
	}

}

void bin_selected_sort(int arr[], int n)
{
	

}

void insertion_sort(int arr[], int n)
{
	for (int i = 1; i < n; i++)
	{
		int j = i - 1;
		int tmp = arr[i];
		while (j >= 0 && tmp < arr[j])
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = tmp;
	}

}

//希尔排序
void shell_sort(int arr[], int n)
{
	if (n < 2)
	{
		return;
	}
	//选择一个增量序列
	vector<int> seq;

	int nTmp = 2;
	while ((n / nTmp) >= 1)
	{
		seq.push_back(n /nTmp);
		nTmp *= 2; 
	}

	for (int i = 0; i < (int)seq.size(); i++)
	{
		int span = seq[i];//增量
		for (int j = 0; j < span; j++)
		{
			for (int k = j + span; k < n; k += span) //标准元素从第二个开始
			{
				int stand = arr[k];//保存标准元素
				int m = k - span;
				while ( m >= 0 && stand < arr[m])
				{
					arr[m + span] = arr[m];//元素后移
					m -= span;	
				}
				arr[m + span] = stand;//标准元素的位置
			}
			
		}
	
	}


}

int main(int argc, char** argv)
{
	int arr[] = {4, 9, 0, 1, 100, 89};
	
	int n  =  sizeof(arr) / sizeof(arr[0]);
	//bubblesort(arr,n);
	//selected_sort(arr, n);
	//insertion_sort(arr, n);
	shell_sort(arr, n);

	for (int i = 0; i < n ; i++)
	{
		cout << arr[i] << " " ;	
	}
	return 0;
}

