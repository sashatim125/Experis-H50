#ifndef __AGENTEX_H__
#define __AGENTEX_H__

// 
//  @file agentExample.h
//  @brief Agent Example
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//

#include <iostream>
#include <sstream>

extern "C"
{
#include <unistd.h>
}
//#include "eventsReceiver.h"
//#include "eventsSender.h"

#include "sensor.h"
#include "controller.h"
#include "simpleEvent.h"

class AgentExample 
:	public Controller
,	public Sensor
{
public:

	inline
	AgentExample();

//	virtual 
//	~AgentExample() {}
	
	virtual inline	
	void SetReceiver(EventsReceiver& _er);
	
	virtual inline	
	void ReceiveEvent(Event_sp _event);
	
	virtual inline	
	void Run();
	
protected:
	
	virtual inline	
	void SendEvent(Event_sp _event);
	
private:
	EventsReceiver* m_er;
};

inline
AgentExample::AgentExample()
{}

inline
void AgentExample::SetReceiver(EventsReceiver& _er)
{
	m_er = &_er;
}
	

inline
void AgentExample::Run()
{
	for(int i=0; i<5; ++i)
	{
		sleep(1);
		
		Location loc("1","57");
		Event *event = new SimpleEvent("important",loc);
		SendEvent(Event_sp(event));
		std::cout<<"Event sent!"<<std::endl;
	}
}
	

inline
void AgentExample::SendEvent(Event_sp _event)
{
	m_er->ReceiveEvent(_event);
}


inline
void AgentExample::ReceiveEvent(Event_sp _event)
{
	std::cout<<"Event received!"<<std::endl;
	std::cout<<"topic : "<<_event->GetTopic()<<"\n";
}









	




#endif //__AGENTEX_H__


