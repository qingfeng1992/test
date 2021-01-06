/*************************************************************************
    > File Name: threadpool.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2020年09月17日 星期四 09时02分39秒
 ************************************************************************/

#include<iostream>
#include<pthread.h>
using namespace std;

//采用头插法
#define LL_ADD(item, list) do{   \
	item->pre = NULL;			 \
	item->next = list;           \
	if (list != NULL)            \
		list->pre = item;        \
	list = item;                 \
} while(0)

//双向链表的删除，只是宏替换，跟函数的值传递不一样,可以删除双向链表中的任意一个节点
#define LL_REMOVE(item, list) do {						 \
	if (item->pre != NULL) item->pre->next = item->next;  \
	if (item->next != NULL) item->next->pre = item->pre;  \
	if (item == list) list = item->next;                 \
	item->pre = item->next = NULL;                        \
}while (0)

typedef struct NWORKER
{
	pthread_t threadid;
	int terminate;
	struct NWORKER *pre;
	struct NWORKER *next;
	struct NMANAGER *pool;//线程想要访问到队列，必须有线程管理对象的指针

} nWorker;

typedef struct NJOB
{
	void (*fun)(void* arg);
	void *user_data;

	struct NJOB *pre;
	struct NJOB *next;
} nJob;

typedef struct NMANAGER
{
	nWorker *workers;
	nJob *jobs;

	pthread_mutex_t jobs_mtx;
	pthread_cond_t jobs_cond;
} nManager;

typedef nManager nThreadPool;

int nCreateThreadPool(nThreadPool *pool, int threadnum);//创建线程池
int nThreadPoolJobPush(nThreadPool *pool, nJob* pJob);
int nThreadPoolShutdown(nThreadPool *pool);
