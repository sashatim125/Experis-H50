
#ifndef __WAITABLE_QUEUE_H__
#define __WAITABLE_QUEUE_H__

// 
//  @file waitableQueue.h
//  @brief Waitable template queue 
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//

#include <queue>

extern "C"
{
#include <unistd.h>
#include <time.h>
}

#include "mutex.h"
#include "cv.h"

namespace advcpp
{

	class WaitableQueueError : public std::runtime_error
	{
	public:
		WaitableQueueError(const std::string& _whatArg) :
			std::runtime_error(_whatArg)
		{}
	};
	
	class WaitableQueueEnqueueError : public WaitableQueueError
	{
	public:
		WaitableQueueEnqueueError(const std::string& _whatArg) :
			WaitableQueueError(_whatArg)
		{}
	};
	
	class WaitableQueueDequeueError : public WaitableQueueError
	{
	public:
		WaitableQueueDequeueError(const std::string& _whatArg) :
			WaitableQueueError(_whatArg)
		{}
	};
	
	class WaitableQueueTimedoutDequeueError : public WaitableQueueDequeueError
	{
	public:
		WaitableQueueTimedoutDequeueError(const std::string& _whatArg) :
			WaitableQueueDequeueError(_whatArg)
		{}
	};


//The queue holds T type
template <class T>
class WaitableQueue{

public:

	WaitableQueue();

	//unsafe if there are waiting threads
	//~WaitableQueue();

	void Enqueue(const T& _item) throw(WaitableQueueEnqueueError);

	//_waitTime in msec
	T TryDequeue(long _msWaitTime = 0) throw(WaitableQueueTimedoutDequeueError, WaitableQueueDequeueError);
	
	T Dequeue() throw(WaitableQueueDequeueError);
	
	bool IsEmpty() const;

private:
	//uncopyable object
    
	mutable Mutex m_mutex;
	
	CV m_cv;
		
    std::queue<T>  m_items;
    
    static
    void AddToTime(timespec& ts, long _ms);
};
}

using namespace advcpp;

//public

template <class T>
WaitableQueue<T>::WaitableQueue() :
	m_cv(m_mutex)
{}


template <class T>
void WaitableQueue<T>::Enqueue(const T& _item) throw(WaitableQueueEnqueueError)
{
	bool wasFirstItem;
	{
		MutexGuard mg(m_mutex);

		wasFirstItem = m_items.empty();

		try
		{
			m_items.push(_item);
		}
		catch(...)
		{
			throw WaitableQueueEnqueueError("queue put error");
		}
	}	
	if(wasFirstItem)
	{
		m_cv.Broadcast();
	}
}

template<class T>
class IsEmptyFunc
{
public:
	IsEmptyFunc(std::queue<T>*_q) : m_q(_q) 
	{}
	
	bool operator()()
	{
		return m_q->empty();
	}
private:
	std::queue<T>* m_q;
};

template <class T>
T WaitableQueue<T>::TryDequeue(long _waitTime) throw(WaitableQueueTimedoutDequeueError, WaitableQueueDequeueError)
{	
	MutexGuard mg(m_mutex);

	timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	AddToTime(ts,_waitTime);
		
	try
	{
		IsEmptyFunc<T> predFunc(&m_items);
		m_cv.TimedWait(predFunc,ts);
	}
	catch(CVWaitTimedoutError _e)
	{
		throw WaitableQueueTimedoutDequeueError(_e.what());
	}
	catch(CVWaitError _e)
	{
		throw WaitableQueueDequeueError(_e.what());
	}
		
	T item(m_items.front());
	m_items.pop();
	
	return item;
}

template <class T>
T WaitableQueue<T>::Dequeue() throw(WaitableQueueDequeueError)
{
	MutexGuard mg(m_mutex);
	
	try
	{
		IsEmptyFunc<T> predFunc(&m_items);
		m_cv.Wait(predFunc);
	}
	catch(CVWaitError _e)
	{
		throw WaitableQueueDequeueError(_e.what());
	}
	
	T item(m_items.front());
	m_items.pop();
	
	return item;
}

//private
template <class T>
void WaitableQueue<T>::AddToTime(timespec& ts, long _ms)
{

	ts.tv_sec += _ms/1000;
	ts.tv_nsec+= (_ms%1000)*1000000;
	ts.tv_sec+= ts.tv_nsec/1000000000;
	ts.tv_nsec%= 1000000000;
}

template <class T>
bool WaitableQueue<T>::IsEmpty() const
{
	MutexGuard mg(m_mutex);
	
	return m_items.empty();
}


#endif /*__WAITABLE_QUEUE_H__*/



