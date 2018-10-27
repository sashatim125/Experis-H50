

#include <iostream>
#include <set>
#include <list>
#include <cstdlib>
#include "stopwatch.h"

#include "waitableQueue.h"


extern "C"
{
#include "mu_test.h"
}


using namespace advcpp;


const static long TIMEOUT_TOLERANCE = 5;
const static long TIMEOUT_VALUE = 1123;
const static size_t QSIZE = 1000;
const static int MAXRANDOM = 1578;
enum ExceptionFlavor {
		EXCEPT_NONE,
		EXCEPT_CORRECT,
		EXCEPT_WRONG
};


UNIT(TryDequeueOnEmptyQueue_ShouldThrowTest)

	WaitableQueue<long> q;
	long r = -12850;
	ExceptionFlavor ef = EXCEPT_NONE;
	try
	{
		r = q.TryDequeue();
	}
	catch (WaitableQueueTimedoutDequeueError)
	{
		ef = EXCEPT_CORRECT;				
	}
	catch(...)
	{
		ef = EXCEPT_WRONG;
	}
	
	ASSERT_THAT(ef == EXCEPT_CORRECT);
	ASSERT_THAT(r == -12850);
	
END_UNIT


UNIT(TryDequeueOnEmptyQueue_ShouldWaitTimeTest)

	WaitableQueue<long> q;
	long r = -12850;
	long timeOutms = TIMEOUT_VALUE;
	Stopwatch sw;
	
	try
	{
		sw.Mark();
		r =	q.TryDequeue(timeOutms);	
	}
	catch (WaitableQueueTimedoutDequeueError )
	{

		long dt = sw.Stop();

		ASSERT_THAT(r == -12850);
		ASSERT_THAT(dt >= timeOutms);
		ASSERT_THAT(dt < timeOutms + TIMEOUT_TOLERANCE);
	}
	catch(...)
	{
		ASSERT_THAT(false);
	}
	
END_UNIT

struct TestMaterial
{ 
	WaitableQueue<long> m_q;
	std::list<long> m_list;
	long(*m_func)(int);
	
	TestMaterial(size_t _size, long (*f)(int))
	: m_list(_size), m_func(f)
	{		
		std::list<long>::iterator it = m_list.begin();
		std::list<long>::iterator end = m_list.end();
		
		for( ; it != end; ++it){
			*it = m_func(MAXRANDOM);
		}
	}	
};

//random number from 1 to max >1
long GetRamdom(int _max)
{
	return static_cast<long>(rand()%_max +1);
}

UNIT(SingleThreadTest)

	TestMaterial ts(QSIZE, GetRamdom);
	std::list<long>::iterator it = ts.m_list.begin();
	std::list<long>::iterator end = ts.m_list.end();
		
	for( ; it != end; ++it){
	
		try
		{
			ts.m_q.Enqueue(*it);
		}
		catch(...)
		{
			ASSERT_THAT(0);
		}
	}
	for(it = ts.m_list.begin() ; it != end; ++it){

		try
		{
			long d = ts.m_q.Dequeue();
			ASSERT_THAT(*it == d);
		}
		catch(...)
		{
			ASSERT_THAT(0);
		}
	}
	
	ASSERT_THAT(ts.m_q.IsEmpty());

END_UNIT

static void* PutToQueue(void* _cntxt)
{
	TestMaterial* tm = static_cast<TestMaterial*>(_cntxt);
	std::list<long>::const_iterator it = tm->m_list.begin();
	std::list<long>::const_iterator end = tm->m_list.end();
	bool ok = true;

	for(; it != end; ++it)
	{
		try
		{
			(tm->m_q).Enqueue(*it);
		}
		catch (...)
		{
			ok = false;
			break;
		}
	}
	return (ok) ? 0 : (void*)(&ok);
}

static void* GetFromQueue(void* _cntxt)
{
	TestMaterial* tm = static_cast<TestMaterial*>(_cntxt);
	std::list<long>::const_iterator it = tm->m_list.begin();
	std::list<long>::const_iterator end = tm->m_list.end();
	bool ok = true;

	for(; it != end; ++it)
	{
		long d;
		try
		{
			d = tm->m_q.Dequeue();
		}
		catch(...)
		{
			ok = false;
			break;
		}
		
		if(d != *it){
			ok = false;
			break;
		}
	}
	
	try
	{
		ok = ok && tm->m_q.IsEmpty();
	}
	catch(...)
	{
		ok = false;
	}
	
	return (ok) ? 0 : (void*)(&ok);
}

UNIT(SingleConsumerSingleProducer_Test)

	pthread_t putThread, getThread;
	TestMaterial tm(QSIZE,GetRamdom);
	void *res1, *res2;

	pthread_create(&getThread,0,GetFromQueue,&tm);
	pthread_create(&putThread,0,PutToQueue,&tm);
	
	pthread_join(putThread,&res1);
	pthread_join(getThread,&res2);
	
	ASSERT_THAT(res1 == 0);
	ASSERT_THAT(res2 == 0);
	
	
END_UNIT


std::set<long> s;
Mutex mutex;
static void* Prod1(void* _q)
{
	bool ok = true;

	for(int i=1; i<=1000; ++i)
	{
		{	
			MutexGuard mg(mutex);
			if(!s.insert(i).second)
			{
				ok = false;
				break;
			}
		}
		
		try
		{
			((WaitableQueue<long>*)_q)->Enqueue(i);
		}
		catch (WaitableQueueEnqueueError& _e)
		{
			ok = false;
			break;
		}
	}
	return (ok) ? 0 : (void*)(&ok);
}

static void* Prod2(void* _q)
{
	bool ok = true;

	for(int i=2001; i<=3000; ++i)
	{
		{	
			MutexGuard mg(mutex);
			if(!s.insert(i).second)
			{
				ok = false;
				break;
			}
		}
		
		try
		{
			((WaitableQueue<long>*)_q)->Enqueue(i);
		}
		catch (WaitableQueueEnqueueError& _e)
		{
			ok = false;
			break;
		}
	}
	return (ok) ? 0 : (void*)(&ok);
}
static void* Prod3(void* _q)
{
	bool ok = true;

	for(int i=4001; i<=5000; ++i)
	{
		{	
			MutexGuard mg(mutex);
			if(!s.insert(i).second)
			{
				ok = false;
				break;
			}
		}
		
		try
		{
			((WaitableQueue<long>*)_q)->Enqueue(i);
		}
		catch (WaitableQueueEnqueueError& _e)
		{
			ok = false;
			break;
		}
	}
	return (ok) ? 0 : (void*)(&ok);
}

static void* Cons(void* _q)
{
	bool ok = true;

	for(int i=1; i<=1000; ++i)
	{
		long k;
		std::set<long>::iterator it;
		
		try
		{
			 k = ((WaitableQueue<long>*)_q)->Dequeue();
		}
		catch (WaitableQueueDequeueError& _e)
		{
			ok = false;
			break;
		}
		{
			MutexGuard mg(mutex);
			if((it=s.find(k)) == s.end())
			{
				ok = false;
				break;
			}else
			{
				s.erase(it);
			}
		}
	}
	return (ok) ? 0 : (void*)(&ok);
}

UNIT(MultyConsumersMultyProducers_Test)

	pthread_t prod[3], cons[3];
	WaitableQueue<long> q;
	void *res1, *res2;

	pthread_create(prod+0,0,Prod1,&q);
	pthread_create(prod+1,0,Prod2,&q);
	pthread_create(prod+2,0,Prod3,&q);
	
	for(int i=0 ; i<3; ++i)
	{
		pthread_create(cons+i,0,Cons,&q);
	}
	
	for(int i=0 ; i<3; ++i)
	{
		pthread_join(prod[i],&res1);
		pthread_join(cons[i],&res2);
		ASSERT_THAT(res1 == 0);
		ASSERT_THAT(res2 == 0);
	}

	ASSERT_THAT(s.empty() == true);
	
END_UNIT


TEST_SUITE(WaitableQueueTests)

	TEST(TryDequeueOnEmptyQueue_ShouldThrowTest)
	TEST(TryDequeueOnEmptyQueue_ShouldWaitTimeTest)
	TEST(SingleThreadTest)
	TEST(SingleConsumerSingleProducer_Test)
	TEST(MultyConsumersMultyProducers_Test)


END_SUITE






