#ifndef __SUBSCRIBERSlISTSMANAGER_H__
#define __SUBSCRIBERSlISTSMANAGER_H__

// 
//  @file subscibersListsManager.h
//  @brief Publish events
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//



#include <map>
#include <string>

#include "registrator.h"
#include "publisher.h"
#include "subscribersList.h"

namespace advcpp
{

class SubscibersListsManager
:	public Registrator
,	public Publisher
{
public:
	SubscibersListsManager(EventsQueue& _q);

	virtual
	void Publish(Event_sp _event);
	
	virtual
	void Register(EventsReceiver& _er, Event_sp _exampleEvent);

protected:
	static
	std::string CreateSubscribtionTopic(Event_sp _event);
	
	static
	std::list<std::string>* CreateEventDetails(Event_sp _event);

private:

	std::map <std::string, SubscribersList> m_lists;
	EventsQueue& m_outEventsQ;
};

}






#endif //__SUBSCRIBERSlISTSMANAGER_H__

