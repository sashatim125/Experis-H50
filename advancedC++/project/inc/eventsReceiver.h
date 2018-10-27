#ifndef __EVENTSRECEIVER_H__
#define __EVENTSRECEIVER_H__

#ifndef interface
#define interface struct
#endif //interface

// 
//  @file eventsReceiver.h
//  @brief Events Receiver interface  
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//

#include "event.h"

namespace advcpp
{

interface EventsReceiver
{
	virtual 
	~EventsReceiver() {}
	
//MUST be thread-safe
//recommended to be short&fast :
//store and return
	virtual
	void ReceiveEvent(Event_sp _event) =0;

};

}//endof namespace advcpp














#endif //__EVENTSRECEIVER_H__


