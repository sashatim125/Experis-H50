#ifndef __AGENTSMANAGER_H__
#define __AGENTSMANAGER_H__

// 
//  @file agentsManager.h
//  @brief Agents Manager
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//

#include <tr1/memory>

#include "DBConnection.h"
#include "agentsLoadersManager.h"
#include "eventsReceiver.h"
#include "registrator.h"
#include "pthread_class.h"

namespace advcpp
{

class AgentsManager
{
public:

	//throws runtime_error on wrong dir
	AgentsManager(
		const std::string& _iniDir,
		AgentsLoadersManager& _alm,
		Registrator* _r,
		EventsReceiver* _er);

	//throws runtime_error on wrong configuration
	AgentsManager(
		const DBConnectionConfig& _config,
		AgentsLoadersManager& _alm,
		Registrator* _r,
		EventsReceiver* _er);

//	~AgentsManager();
	
	void Start();
	
	void StopAndWait();

private:

	std::vector<PThread_sp> m_agents;

};

typedef std::tr1::shared_ptr<AgentsManager> AgentsManager_sp;


}











#endif //__AGENTSMANAGER_H__

