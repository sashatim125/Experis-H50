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
public:

	//throws exceptions !
	static
	void MakeSmartHouse(const SetupConfig& _sc);
		
	~SmartHouse();

private:

	SmartHouse(const SetupConfig& _sc);
	
	typedef std::tr1::shared_ptr<SmartHouse> SmartHouse_sp;
	static
	SmartHouse_sp s_SmartHouse;
	
	EventsWaitableQueue m_q1, m_q2;
	
	SubscibersListsManager m_slm;
	
	Hub m_hub;
	
	LogsHolder m_logsHolder;
		
	AgentsLoadersManager m_agentsLoadersManager;
	
	AgentsManager_sp m_agentsManager;
};

}



#endif //__SMARTHOUSE_H__



