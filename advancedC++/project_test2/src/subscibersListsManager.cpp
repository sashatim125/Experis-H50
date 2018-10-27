

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

using namespace advcpp;

SubscibersListsManager::SubscibersListsManager(EventsQueue& _q)
:	m_outEventsQ(_q)
{}


void SubscibersListsManager::Publish(Event_sp _event)
{
	std::list<std::string>* details = CreateEventDetails(_event);
	std::map< std::string, SubscribersList>::iterator it;
	std::list<std::string>::iterator detIt = details->begin();
	std::list<std::string>::iterator detEnd = details->end();

	for(; detIt != detEnd; ++detIt)
	{
		it = m_lists.find(*detIt);
		if(it != m_lists.end())
		{
			(*it).second.Publish(_event);
		}
	}
	
	delete details;
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



std::list<std::string>* SubscibersListsManager::CreateEventDetails(Event_sp _event)
{
	std::list<std::string>* details = new std::list<std::string>();
	std::string delimiter(" , ");
	std::string emptyStr;
	
	details->push_back(CreateSubscribtionTopic(_event));
	
	{
		std::ostringstream os;
		os<<_event->GetTopic()<<delimiter<<emptyStr<<delimiter;
		details->push_back(os.str());
	}
	{
		std::ostringstream os;
		os<<emptyStr<<delimiter<<_event->GetLocation().GetFloor()<<delimiter<<emptyStr;
		details->push_back(os.str());
	}
	
	{
		std::ostringstream os;
		os<<_event->GetTopic()<<delimiter<<_event->GetLocation().GetFloor()<<delimiter<<emptyStr;
		details->push_back(os.str());
	}
	
	{
		std::ostringstream os;
		os<<emptyStr<<delimiter<<emptyStr<<delimiter<<emptyStr;
		details->push_back(os.str());
	}

	
	return details;
}






