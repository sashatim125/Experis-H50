

// 
//  @file dispatcher.cpp
//  @brief Dispatch events
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//

#include <iostream> //TODO test

#include "dispatcher.h"

using namespace advcpp;


Dispatcher::Dispatcher(EventsQueue& _eventsQ, Publisher& _publisher)
:	m_eventsQ(_eventsQ)
,	m_publisher(_publisher)
{}



void Dispatcher::Run()
{
//TODO TEST	std::cout<<"Dispatcher's ON!\n";
	for(;;)
	{
		Event_sp e_sp = m_eventsQ.Dequeue();
		
		if(dynamic_cast<StopEvent*>(e_sp.get()))
		{
			m_eventsQ.Enqueue(e_sp);
			break;
		}
				
		m_publisher.Publish(e_sp);
	}//TODO TEST	std::cout<<"Dispatcher's OFF!\n";
}


