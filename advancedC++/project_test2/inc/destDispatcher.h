#ifndef __DESTDISPATCHER_H__
#define __DESTDISPATCHER_H__

// 
//  @file destDispatcher.h
//  @brief Dispatch events to final destination
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//

#include "eventsQueue.h"
#include "runnable.h"
#include "stopEvent.h"

namespace advcpp
{

class DestDispatcher
: public Runnable
{
public:

	DestDispatcher(EventsQueue& _eventsQ);
	
//	~DestDispatcher();

	virtual
	void Run();

private:

	EventsQueue& m_eventsQ;
};

}









#endif //__DESTDISPATCHER_H__


