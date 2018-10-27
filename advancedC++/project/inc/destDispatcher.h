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


namespace advcpp
{

class DestDispatcher
:	public Runnable
{
public:

	explicit
	DestDispatcher(EventsQueue& _eventsQ);
	
//	~DestDispatcher();

	virtual
	void Run();

private:

	EventsQueue& m_eventsQ;
};

}//endof namespace advcpp









#endif //__DESTDISPATCHER_H__


