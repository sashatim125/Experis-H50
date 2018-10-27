#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#ifndef interface
#define interface struct
#endif //interface

// 
//  @file controller.h
//  @brief Controller Interface
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//

#include "agent.h"
#include "eventsReceiver.h"

namespace advcpp
{

interface Controller
:	virtual public Agent
,	public EventsReceiver
{
	~Controller() {}

//	virtual
//	void Run() =0;

//	virtual
//	void Stop() =0;

//	virtual
//	void ReceiveEvent(Event_sp _event) =0;
};

}//endof namespace advcpp









#endif //__CONTROLLER_H__

