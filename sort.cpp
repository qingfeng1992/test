/*************************************************************************
    > File Name: sort.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2019年10月08日 星期二 16时47分06秒
 ************************************************************************/

#include<iostream>
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

void swap_sort(int arr[], int n)
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

int main(int argc, char** argv)
{
	int arr[] = {4, 9, 0, 1, 100, 89};
	
	int n  =  sizeof(arr) / sizeof(arr[0]);
	//bubblesort(arr,n);
	swap_sort(arr, n);

	for (int i = 0; i < n ; i++)
	{
		cout << arr[i] << " " ;	
	}
	return 0;
}

