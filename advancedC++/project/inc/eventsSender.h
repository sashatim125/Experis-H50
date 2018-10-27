#ifndef __EVENTSSENDER_H__
#define __EVENTSSENDER_H__

#ifndef interface
#define interface struct
#endif //interface

// 
//  @file eventsSender.h
//  @brief Events Sender interface  
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

interface EventsSender
{
	virtual 
	~EventsSender() {}
	
	virtual
	void SetReceiver(EventsReceiver& _er) =0;
	
protected:
	
	virtual
	void SendEvent(Event_sp _event) =0;
	
//private:
//	EventsReceiver& m_er;
};

}//endof namespace advcpp









#endif //__EVENTSSENDER_H__


