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
#include <tr1/memory>

#include "registrator.h"
#include "publisher.h"
#include "subscribersList.h"

namespace advcpp
{

class SubscibersListsManager
:	public Registrator
,	public Publisher
{
private:
	typedef std::tr1::shared_ptr <std::list<std::string> > ListOfStrings_sp;
public:
	SubscibersListsManager(EventsQueue& _q);

	virtual
	void Publish(Event_sp _event);
	
	virtual
	void Register(EventsReceiver& _er, Event_sp _exampleEvent);

protected:
	static std::string CreateSubscribtionTopic(Event_sp _event);
	
	static ListOfStrings_sp CreateEventPublishingTopics(Event_sp _event);

private:

	std::map <std::string, SubscribersList> m_lists;
	EventsQueue& m_outEventsQ;
};

}//endof namespace advcpp





#endif //__SUBSCRIBERSlISTSMANAGER_H__

