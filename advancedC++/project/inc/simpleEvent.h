#ifndef __SIMPLEEVENT_H__
#define __SIMPLEEVENT_H__


// 
//  @file simpleEvent.h
//  @brief the most simple event
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//


#include "event.h"

namespace advcpp
{

struct SimpleEvent
:	public Event
{
	inline
	friend std::ostream& operator<<(std::ostream& _os, const SimpleEvent& _event);

	inline
	SimpleEvent(const std::string& _topic,
		const Location& _loc,
		const std::string& _senderId,
		const std::string& _payload = "");
	
	virtual inline
	const Timestamp& GetTimestamp() const ;

	virtual inline
	const std::string& GetTopic() const;
	
	virtual inline
	const Location& GetLocation() const;
	
	virtual inline
	const std::string& GetSenderID() const;
	
	virtual inline
	const std::string& GetPayload() const;
	
	inline
	std::string ToString() const;

private:

	Timestamp m_timestamp;
	std::string m_topic;
	Location m_loc;
	std::string m_senderId;
	std::string m_payload;
	
};

inline
std::ostream& operator<<(std::ostream& _os, const SimpleEvent& _event)
{
	_os<<"timestamp: "<<_event.GetTimestamp().ToString()<<"\n";
	_os<<"topic: "<<_event.GetTopic()<<"\n";
	_os<<_event.GetLocation()<<"\n";
	_os<<"payload: "<<_event.GetPayload()<<"\n";

	return _os;
}


inline
SimpleEvent::SimpleEvent(const std::string& _topic,
		const Location& _loc,
		const std::string& _senderId,
		const std::string& _payload)
:	m_topic(_topic)
,	m_loc(_loc)
,	m_senderId(_senderId)
,	m_payload(_payload)
{}


inline
const Timestamp& SimpleEvent::GetTimestamp() const
{
	return m_timestamp;
}

inline
const std::string& SimpleEvent::GetTopic() const
{
	return m_topic;
}
	
inline
const Location& SimpleEvent::GetLocation() const
{
	return m_loc;
}

inline
const std::string& SimpleEvent::GetSenderID() const
{
	return m_senderId;
}

inline
const std::string& SimpleEvent::GetPayload() const
{
	return m_payload;
}

inline
std::string SimpleEvent::ToString() const
{
	std::ostringstream os;
	os<<"timestamp: "<<GetTimestamp().ToString()<<";";
	os<<"topic: "<<GetTopic()<<";";
	os<<GetLocation()<<";";
	os<<"payload: "<<GetPayload()<<".";
	
	return os.str();
}


}//endof namespace advcpp


#endif //__SIMPLEEVENT_H__


