#ifndef __DISPATCHER_H__
#define __DISPATCHER_H__

// 
//  @file dispatcher.h
//  @brief Dispatch events
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//


#include "eventsQueue.h"
#include "publisher.h"
#include "runnable.h"
#include "stopEvent.h"

namespace advcpp
{

class Dispatcher
:	public Runnable
{
public:

	Dispatcher(EventsQueue& _eventsQ, Publisher& _publisher);
	
//	~Dispatcher();

	virtual
	void Run();

private:

	EventsQueue& m_eventsQ;
	Publisher& m_publisher;
};

}








#endif //__DISPATCHER_H__


