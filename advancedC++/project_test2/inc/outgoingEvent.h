#ifndef __OUTGOINGEVENT_H__
#define __OUTGOINGEVENT_H__


// 
//  @file outgoingEvent.h
//  @brief outgoing event (with destination)
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//


#include "eventsReceiver.h"

namespace advcpp
{

struct OutgoingEvent
:	public Event
{
	inline
	OutgoingEvent(Event_sp _event, EventsReceiver& _dest);

	virtual inline
	const Timestamp& GetTimestamp() const ;
	
	virtual inline
	const std::string& GetTopic() const;
	
	virtual inline
	const Location& GetLocation() const;
	
	virtual inline
	const std::string& GetSenderID() const;
	
	inline
	EventsReceiver& GetDestination();
	
	inline
	Event_sp GetEvent();

private:

	Event_sp m_event;
	EventsReceiver* m_dest;	
};

}

using namespace advcpp;

inline
OutgoingEvent::OutgoingEvent(Event_sp _event, EventsReceiver& _dest)
:	m_event(_event)
,	m_dest(&_dest)
{}

inline
const Timestamp& OutgoingEvent::GetTimestamp() const
{
	return m_event->GetTimestamp();
}

inline
const std::string& OutgoingEvent::GetTopic() const
{
	return m_event->GetTopic();
}
	
inline
const Location& OutgoingEvent::GetLocation() const
{
	return m_event->GetLocation();
}

inline
const std::string& OutgoingEvent::GetSenderID() const
{
	return m_event->GetSenderID();
}


inline
EventsReceiver& OutgoingEvent::GetDestination()
{
	return *m_dest;
}

inline
Event_sp OutgoingEvent::GetEvent()
{
	return m_event;
}




#endif //__OUTGOINGEVENT_H__


