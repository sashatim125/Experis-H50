
#ifndef __EVENT_H__
#define __EVENT_H__

#ifndef interface
#define interface struct
#endif //interface

// 
//  @file event.h
//  @brief Event interface
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//


#include <string>
#include <tr1/memory>

#include "location.h"
#include "timestamp.h"

namespace advcpp
{

interface Event;
typedef std::tr1::shared_ptr<Event> Event_sp;

interface Event
{
	virtual
	~Event() {}
	
	virtual
	const Timestamp& GetTimestamp() const =0;

	virtual
	const std::string& GetTopic() const =0;
	
	virtual
	const Location& GetLocation() const =0;
	
	virtual
	const std::string& GetSenderID() const =0;

private:
//	Timestamp m_timestamp;
//	std::string m_topic;
//	Location m_loc;
//	std::string m_senderId;
};

}









#endif //__EVENT_H__


