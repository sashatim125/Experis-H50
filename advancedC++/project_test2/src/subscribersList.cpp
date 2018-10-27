

// 
//  @file subscribersList.cpp
//  @brief Subscribers list for agents 
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//


#include "subscribersList.h"
#include "outgoingEvent.h"

using namespace advcpp;


SubscribersList::SubscribersList(EventsQueue& _q)
:	m_outEventsQ(_q)
{}


void SubscribersList::AddSubscriber(EventsReceiver& _agent)
{
	//check if allready subscribed ?
	m_list.push_back(&_agent);	
}


void SubscribersList::Publish(Event_sp _event)
{
	std::list<EventsReceiver*>::iterator it = m_list.begin();
	std::list<EventsReceiver*>::iterator end = m_list.end();
	
	for(; it != end ; ++it)
	{
		OutgoingEvent* oe = new OutgoingEvent(_event,*(*it));
		m_outEventsQ.Enqueue(Event_sp(oe));
	}
}


