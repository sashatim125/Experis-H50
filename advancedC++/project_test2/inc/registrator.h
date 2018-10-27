#ifndef __REGISTRATOR_H__
#define __REGISTRATOR_H__

#ifndef interface
#define interface struct
#endif //interface

// 
//  @file registrator.h
//  @brief Registrator interface
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//

#include "eventsReceiver.h"

namespace advcpp
{

interface Registrator
{
	virtual
	~Registrator() {}
	
	virtual
	void Register(EventsReceiver& _er, Event_sp _exampleEvent) =0;
};

}
















#endif //__REGISTRATOR_H__

