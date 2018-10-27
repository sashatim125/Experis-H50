#ifndef __SUBSCLIST_H__
#define __SUBSCLIST_H__

// 
//  @file subscribersList.h
//  @brief Subscribers list for agents 
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//

#include <list>

#include "eventsReceiver.h"
#include "publisher.h"
#include "eventsQueue.h"

namespace advcpp
{

class SubscribersList
:	public Publisher
{
public:

	SubscribersList(EventsQueue& _q);

//	~SubscribersList();

	void AddSubscriber(EventsReceiver& _agent);

	virtual
	void Publish(Event_sp _event);

private:

	std::list<EventsReceiver*> m_list;
	EventsQueue& m_outEventsQ;
};

}















#endif //__SUBSCLIST_H__

