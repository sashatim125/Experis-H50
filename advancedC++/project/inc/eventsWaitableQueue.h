
#ifndef __EVENTSWAITABLEQUEUE_H__
#define __EVENTSWAITABLEQUEUE_H__

// 
//  @file eventsWaitableQueue.h
//  @brief Waitable queue of events (shared_ptr<Event>)
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//


#include "eventsQueue.h"
#include "waitableQueue.h"

namespace advcpp
{

class EventsWaitableQueue
:	public EventsQueue
{
public:

	EventsWaitableQueue()
	{}

//	virtual
//	~EventsWaitableQueue();

	virtual inline
	void Enqueue(Event_sp _event);
	
	//_waitTime in msec
	virtual inline
	Event_sp TryDequeue(long _msWaitTime = 0);
	
	virtual inline
	Event_sp Dequeue();
	
private:
	//uncopyable objects
	EventsWaitableQueue(const EventsWaitableQueue&);
	EventsWaitableQueue& operator=(const EventsWaitableQueue&);

	WaitableQueue <Event_sp> m_q;
};


inline
void EventsWaitableQueue::Enqueue(Event_sp _event)
{
	m_q.Enqueue(_event);
}

inline
Event_sp EventsWaitableQueue::TryDequeue(long _msWaitTime)
{
	return m_q.TryDequeue(_msWaitTime);
}
	
inline
Event_sp EventsWaitableQueue::Dequeue()
{
	return m_q.Dequeue();
}

}//endof namespace advcpp


#endif //__EVENTSWAITABLEQUEUE_H__


