#ifndef __SMARTHOUSE_H__
#define __SMARTHOUSE_H__

// 
//  @file smartHouse.h
//  @brief Setup and run the system
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//


#include "setupConfig.h"
#include "hub.h"
#include "subscibersListsManager.h"
#include "eventsWaitableQueue.h"
#include "agentsLoadersManager.h"
#include "agentsManager.h"
#include "logsHolder.h"

namespace advcpp
{

class SmartHouse
{
private:
	typedef std::tr1::shared_ptr<SmartHouse> SmartHouse_sp;

public:

	//throws exceptions !
	static void MakeSmartHouse(const SetupConfig& _sc);
		
	~SmartHouse();

private:
	//singleton
	SmartHouse(const SetupConfig& _sc);
	
	static SmartHouse_sp s_SmartHouse;
	
	EventsWaitableQueue m_inEventsQ;
	EventsWaitableQueue m_outEventsQ;
	
	SubscibersListsManager m_subscibersListsManager;
	
	Hub m_hub;
	
	LogsHolder m_logsHolder;
		
	AgentsLoadersManager m_agentsLoadersManager;
	
	AgentsManager_sp m_agentsManager;
};

}//endof namespace advcpp



#endif //__SMARTHOUSE_H__



