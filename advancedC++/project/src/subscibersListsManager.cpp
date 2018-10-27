

// 
//  @file subscibersListsManager.cpp
//  @brief Publish events
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//

#include <list>
#include <sstream>

#include "subscibersListsManager.h"

namespace advcpp
{

SubscibersListsManager::SubscibersListsManager(EventsQueue& _q)
:	m_outEventsQ(_q)
{}


void SubscibersListsManager::Publish(Event_sp _event)
{
	ListOfStrings_sp topics(CreateEventPublishingTopics(_event));
	std::map< std::string, SubscribersList>::iterator it;
	std::list<std::string>::iterator topicsIt = topics->begin();
	std::list<std::string>::iterator topicsEnd = topics->end();

	for(; topicsIt != topicsEnd; ++topicsIt)
	{
		it = m_lists.find(*topicsIt);
		if(it != m_lists.end())
		{
			(*it).second.Publish(_event);
		}
	}
}
	

void SubscibersListsManager::Register(EventsReceiver& _er, Event_sp _exampleEvent)
{
	std::string topic = CreateSubscribtionTopic(_exampleEvent);
	std::map< std::string, SubscribersList>::iterator it;
	//TODO test
	//std::cout<<"Register:next topic = "<<topic<<std::endl;
	
	it = m_lists.find(topic);
	if(it == m_lists.end())
	{
		it = m_lists.insert(std::pair< std::string, SubscribersList>(topic,SubscribersList(m_outEventsQ))).
			first;
	}
	
	(*it).second.AddSubscriber(_er);
}




std::string SubscibersListsManager::CreateSubscribtionTopic(Event_sp _event)
{
	std::ostringstream os;
	os<<_event->GetTopic()<<" , ";
	os<<_event->GetLocation().GetFloor()<<" , "<<_event->GetLocation().GetRoom();
	
	return os.str();
}



SubscibersListsManager::ListOfStrings_sp SubscibersListsManager::CreateEventPublishingTopics(Event_sp _event)
{
	ListOfStrings_sp topics(new std::list<std::string>());
	const std::string delimiter(" , ");
	const std::string emptyStr;
	
	topics->push_back(CreateSubscribtionTopic(_event));
	
	{
		std::ostringstream os;
		os<<_event->GetTopic()<<delimiter<<emptyStr<<delimiter;
		topics->push_back(os.str());
	}
	{
		std::ostringstream os;
		os<<emptyStr<<delimiter<<_event->GetLocation().GetFloor()<<delimiter<<emptyStr;
		topics->push_back(os.str());
	}
	
	{
		std::ostringstream os;
		os<<_event->GetTopic()<<delimiter<<_event->GetLocation().GetFloor()<<delimiter<<emptyStr;
		topics->push_back(os.str());
	}
	
	{
		std::ostringstream os;
		os<<emptyStr<<delimiter<<emptyStr<<delimiter<<emptyStr;
		topics->push_back(os.str());
	}

	
	return topics;
}


}//endof namespace advcpp



