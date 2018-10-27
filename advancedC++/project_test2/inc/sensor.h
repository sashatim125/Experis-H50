
#ifndef __SENSOR_H__
#define __SENSOR_H__

#ifndef interface
#define interface struct
#endif //interface

// 
//  @file sensor.h
//  @brief Sensor Interface
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//

#include "agent.h"
#include "eventsSender.h"

namespace advcpp
{

interface Sensor
:	virtual public Agent
,	public EventsSender
{
public:
//	virtual
//	void Run() =0;

//	virtual
//	void Stop() =0;

//	virtual
//	void SetReceiver(EventsReceiver& _er) =0;
	
protected:
	
//	virtual
//	void SendEvent(Event_sp _event) =0;

};

}









#endif //__SENSOR_H__

