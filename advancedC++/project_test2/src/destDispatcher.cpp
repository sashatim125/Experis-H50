
// 
//  @file destDispatcher.cpp
//  @brief Dispatch events to final destination
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//


#include <iostream> //TODO test

#include "eventsReceiver.h"
#include "outgoingEvent.h"
#include "destDispatcher.h"


using namespace advcpp;

DestDispatcher::DestDispatcher(EventsQueue& _eventsQ)
:	m_eventsQ(_eventsQ)
{}


void DestDispatcher::Run()
{
//TODO TEST	std::cout<<"DestDispatcher's ON!\n";
	for(;;)
	{
		Event_sp e_sp = m_eventsQ.Dequeue();
		
		if(dynamic_cast<StopEvent*>(e_sp.get()))
		{
			m_eventsQ.Enqueue(e_sp);
			break;
		}
		
		OutgoingEvent *e = dynamic_cast<OutgoingEvent*>(e_sp.get());
		if(0 == e)
		{
			continue;
		}
		
		e->GetDestination().ReceiveEvent(e->GetEvent());
	}//TODO TEST	std::cout<<"DestDispatcher's OFF!\n";
}
