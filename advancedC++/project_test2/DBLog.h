#ifndef __DBLOG_H__
#define __DBLOG_H__

// 
//  @file DBLog.h
//  @brief log events to DB
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//

#include <iostream> //TODO TEST
//TODO TEST


#include <sstream>

#include "eventsWaitableQueue.h"
#include "DBConnection.h"
#include "runnable.h"

namespace advcpp
{
//The Log is thread_safe
class DBLog
:	public Runnable
{
public:

	explicit
	DBLog(const DBConnectionConfig& _config);

	//throw runtime_error on mysql error
	void WriteToLog(Event_sp _event);

	virtual
	void Run();

private:
	
	DBConnection m_dbconn;

	EventsWaitableQueue m_q;
};

}





#endif //__DBLOG_H__

