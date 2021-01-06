/*************************************************************************
    > File Name: merge_link.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2020年08月01日 星期六 15时22分39秒
 ************************************************************************/

#include<iostream>
using namespace std;

struct Node
{
	Node(int val) { this->val = val;}
	int val;
	Node *next;
};

Node* sort(Node* a, Node* b)
{
	if (NULL == a && NULL == b)
	{
		return NULL;
	}

	if (NULL == a && NULL != b)
		return b;
	if (NULL != a && NULL == b)
		return a;
	Node *h = a;
	Node *tmp;
	if (b->val < h->val)
	{
		h = b;	
		tmp = b->next;
		b->next = a;
		b = tmp;
	}
	Node *pre = h;
	Node *cur = pre->next;

	while (b != NULL)
	{
		tmp = NULL;
	
		if (cur->val >= b->val)
		{
			pre->next = b;
			tmp = b->next;
			b->next = cur;
			pre = pre->next;
		}
		else 
		{
			while (cur != NULL && cur->val < b->val)
			{
				pre = pre->next;
				cur = cur->next;
			}
			
			if (NULL == cur)
			{
				pre->next = b;
				break;
			}
			else 
			{	
				//插入到cur结点前面
				pre->next = b;
				tmp = b->next;
				b->next = cur;
				pre = pre->next;
			}
		}
		b = tmp;
	}
	return h;
}

int main (int argc, char** argv)
{
	
	Node *a = new Node(2);
	Node *a1 = new Node(2);
	a->next = a1;
	Node *a2 = new Node(3);
	a1->next = a2;
	Node *a3 = new Node(5);
	a2->next = a3;

	Node* b = new Node(1);
	Node* b1 = new Node(4);
	b->next = b1;
	Node* b2 = new Node(6);
	b1->next = b2;
	Node* b3 = new Node(7);
	b2->next = b3;


	Node *ret = sort(a, b);
	
	while (ret != NULL)
	{
		cout << ret->val << " ";
		Node *tmp = ret;
		ret = ret->next;
		delete tmp;
	}

	return 0;
}


