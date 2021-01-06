/*************************************************************************
    > File Name: threadpool.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2020年09月17日 星期四 16时00分15秒
 ************************************************************************/

#include "threadpool.h"
#include <stdlib.h>
#include <memory.h>
using namespace std;

//线程回调函数
static void* threadCallback(void* arg)
{
	nWorker *pWorker = (nWorker*)arg;

	while (1)
	{
		//检查队列中是否有任务
		
		//先加锁
		pthread_mutex_lock(&pWorker->pool->jobs_mtx);
		while (pWorker->pool->jobs == NULL)
		{
			//投入睡眠
			if (pWorker->terminate) break;//如果线程需要退出，就不睡眠
			pthread_cond_wait(&pWorker->pool->jobs_cond, &pWorker->pool->jobs_mtx);
		}
		if (pWorker->terminate)
		{
			pthread_mutex_unlock(&pWorker->pool->jobs_mtx);
			break;
		}
		nJob *pJob = pWorker->pool->jobs;//取出队头的一个任务
		LL_REMOVE(pJob, pWorker->pool->jobs);
		pthread_mutex_unlock(&pWorker->pool->jobs_mtx);//取到任务了就解锁
		//执行任务
		pJob->fun(pJob);//把任务返回回去
	}

	free(pWorker);
	cout << "线程退出" << pthread_self() <<endl;
	//线程结束要释放内存
	return 0;
}

int nCreateThreadPool(nThreadPool *pool, int threadnum)
{
	if (pool == NULL || threadnum < 1)
		return -1;

	//初始化互斥锁和条件变量
	pthread_mutex_init(&pool->jobs_mtx, NULL);
	pthread_cond_init(&pool->jobs_cond, NULL);
	//初始化指针
	pool->workers = NULL;
	pool->jobs = NULL;

	//初始化线程
	for (int i = 0; i < threadnum; i++)
	{
		nWorker *pWorker = (nWorker*)malloc(sizeof(nWorker));		
		if (NULL == pWorker)
		{
			for (nWorker* tmp = pool->workers; tmp != NULL; tmp = tmp->next)
			{
				tmp->terminate = 1;//让线程自动退出
			}
			return -1;
		}
		memset(pWorker, 0, sizeof(nWorker));//给新申请的内存空间填0
		//初始化线程
		pthread_create(&pWorker->threadid, NULL, threadCallback, pWorker);
		pthread_detach(pWorker->threadid);//不需要等待线程结束，不需要调用pthread_join()
		pWorker->pool = pool;
		//加入队列
		LL_ADD(pWorker, pool->workers);
	}

	return 0;
}


int nThreadPoolJobPush(nThreadPool *pool, nJob* pJob)
{
	//给任务队列加锁
	pthread_mutex_lock(&pool->jobs_mtx);
	LL_ADD(pJob, pool->jobs);
	//唤醒线程
	pthread_cond_signal(&pool->jobs_cond);//此处值唤醒一个等待中的线程即可
	pthread_mutex_unlock(&pool->jobs_mtx);
	return 0;
}


int nThreadPoolShutdown(nThreadPool *pool)
{
	for (nWorker *p = pool->workers; p != NULL; p = p->next)
		p->terminate = 1;
	//锁住互斥锁再广播
	pthread_mutex_lock(&pool->jobs_mtx);
	//队列置空
	pool->workers = NULL;
	pool->jobs = NULL;//欠考虑，应该把这个job里面的东西要free掉，否则不回调给用户线程就释放不了，造成内存泄漏
	pthread_cond_broadcast(&pool->jobs_cond);
	pthread_mutex_unlock(&pool->jobs_mtx);
	return 0;
}

