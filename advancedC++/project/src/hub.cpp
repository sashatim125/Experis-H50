
// 
//  @file hub.cpp
//  @brief Evens Hub
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//


#include "hub.h"

//#include<iostream>//TODO TEST
#include<stdexcept>

namespace advcpp
{


Hub::Hub(EventsQueue& _inQ, EventsQueue& _outQ,
		Registrator& _r, Publisher& _p,
		size_t _numOfInDispatchers, size_t _numOfOutDispatchers)
:	m_inEventsQ(_inQ)
,	m_outEventsQ(_outQ)
,	m_reg(_r)
,	m_pub(_p)
{
	Dispatcher* dispatcherPtr;
	PThread * threadPtr;
	for(size_t i=0 ; i < _numOfInDispatchers ; ++i)
	{
		dispatcherPtr = new Dispatcher(m_inEventsQ, m_pub);
		threadPtr = new PThread(Runnable_sp(dispatcherPtr));
		
		m_inDispatchers.push_back(PThread_sp(threadPtr));
	}
	
	DestDispatcher* destDispatcherPtr;
	for(size_t i=0 ; i < _numOfOutDispatchers ; ++i)
	{
		destDispatcherPtr = new DestDispatcher(m_outEventsQ);
		threadPtr = new PThread(Runnable_sp(destDispatcherPtr));
		
		m_outDispatchers.push_back(PThread_sp(threadPtr));
	}
}


void Hub::ReceiveEvent(Event_sp _event)
{
	m_inEventsQ.Enqueue(_event);
}

void Hub::Register(EventsReceiver& _er, Event_sp _exampleEvent)
{
	m_reg.Register(_er, _exampleEvent);
}

void Hub::Start()
{	
	size_t numOfDispatchers = m_inDispatchers.size();
	
	for(size_t i=0; i < numOfDispatchers ; ++i)
	{
		m_inDispatchers[i]->Start();
	}
	
	size_t numOfDestDispatchers = m_outDispatchers.size();
	
	for(size_t i=0; i < numOfDestDispatchers ; ++i)
	{
		m_outDispatchers[i]->Start();
	}
}

void Hub::Stop()
{
	Event_sp stopEvent(new StopEvent("STOP!!!"));

	m_inEventsQ.Enqueue(stopEvent);
	m_outEventsQ.Enqueue(stopEvent);

	size_t numOfDispatchers = m_inDispatchers.size();
	
	for(size_t i=0; i < numOfDispatchers ; ++i)
	{
		m_inDispatchers[i]->Join();
	}
	
	size_t numOfDestDispatchers = m_outDispatchers.size();
	
	for(size_t i=0; i < numOfDestDispatchers ; ++i)
	{
		m_outDispatchers[i]->Join();
	}
	//TODO TEST
	//std::cout<<"Dispatchers+log joined !\n"<<std::endl;
	for(;;)
	{
		try
		{
			Event_sp esp(m_inEventsQ.TryDequeue());
//			std::cout<<esp->GetTopic()<<std::endl;
		}
		catch(std::runtime_error re)
		{
			//TODO TEST
			//std::cout<<re.what()<<std::endl;
			//std::cout<<"m_inEventsQ.TryDequeue() finished !\n"<<std::endl;
			break;
		}
	}
	for(;;)
	{
		try
		{
			Event_sp esp(m_outEventsQ.TryDequeue());
//			std::cout<<esp->GetTopic()<<std::endl;
		}
		catch(std::runtime_error re)
		{
			//TODO TEST
			//std::cout<<re.what()<<std::endl;
			//std::cout<<"m_outEventsQ.TryDequeue() finished !\n"<<std::endl;
			break;
		}
	}
}

}//endof namespace advcpp





