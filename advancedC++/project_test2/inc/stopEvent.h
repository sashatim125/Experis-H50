#ifndef __STOPEVENT_H__
#define __STOPEVENT_H__


// 
//  @file stopEvent.h
//  @brief stop the dispatchers on receit
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

struct StopEvent
:	public Event
{

	inline explicit
	StopEvent(const std::string& _payload = "");
	
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

private:

	Timestamp m_timestamp;
	std::string m_topic;
	Location m_loc;
	std::string m_senderId;
	std::string m_payload;
	
};


}

using namespace advcpp;

inline
StopEvent::StopEvent(const std::string& _payload)
:	m_loc(Location("",""))
,	m_payload(_payload)
{}


inline
const Timestamp& StopEvent::GetTimestamp() const
{
	return m_timestamp;
}

inline
const std::string& StopEvent::GetTopic() const
{
	return m_topic;
}
	
inline
const Location& StopEvent::GetLocation() const
{
	return m_loc;
}

inline
const std::string& StopEvent::GetSenderID() const
{
	return m_senderId;
}

inline
const std::string& StopEvent::GetPayload() const
{
	return m_payload;
}





#endif //__STOPEVENT_H__


