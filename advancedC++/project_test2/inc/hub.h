#ifndef __HUB_H__
#define __HUB_H__

// 
//  @file hub.h
//  @brief Evens Hub
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//
//TODO TEST
#include <iostream>
#include <vector>

#include "eventsQueue.h"
#include "eventsReceiver.h"
#include "registrator.h"
#include "publisher.h"
#include "dispatcher.h"
#include "destDispatcher.h"
#include "pthread_class.h"

namespace advcpp
{

class Hub 
:	public EventsReceiver
,	public Registrator
{
public:

	Hub(EventsQueue& _inQ, EventsQueue& _outQ,
		Registrator& _r, Publisher& _p,
		size_t _numOfInDispatchers, size_t _numOfOutDispatchers);

//TODO TEST	~Hub(){std::cout<<"~Hub finished !\n"<<std::endl;}

	void Start();

//Use with EXTREME CAUTION !
//Events may be LOST !!!
	void Stop();

	virtual
	void ReceiveEvent(Event_sp _event);
	
	virtual	
	void Register(EventsReceiver& _er, Event_sp _exampleEvent);

private:

	Hub(const Hub&);
	Hub& operator=(const Hub&);

	EventsQueue& m_inEventsQ;
	EventsQueue& m_outEventsQ;
	Registrator& m_reg;
	Publisher& m_pub;
	
	std::vector<PThread_sp> m_inDispatchers;
	std::vector<PThread_sp> m_outDispatchers;
};

}







#endif //__HUB_H__
