
#ifndef __EVENTSQUEUE_H__
#define __EVENTSQUEUE_H__

#ifndef interface
#define interface struct
#endif //interface

// 
//  @file eventsQueue.h
//  @brief Queue of events interface
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//


#include "event.h"
#include "eventsReceiver.h"

namespace advcpp
{

interface EventsQueue
{
	virtual
	~EventsQueue()
	{}

	virtual
	void Enqueue(Event_sp _event) =0;

	//_waitTime in msec
	virtual
	Event_sp TryDequeue(long _msWaitTime = 0) =0;
	
	virtual
	Event_sp Dequeue() =0;
};

}




#endif //__EVENTSQUEUE_H__


