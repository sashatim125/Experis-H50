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

#include "configurationMaker.h"
#include "agentsLoadersManager.h"
#include "eventsReceiver.h"
#include "registrator.h"
#include "pthread_class.h"

namespace advcpp
{

class AgentsManager
{
public:

	//throws runtime_error on wrong config
	//and when can't create an agent
	AgentsManager(
		const ConfigurationMaker& _configMaker,
		AgentsLoadersManager& _alm,
		Registrator* _r,
		EventsReceiver* _er);


//	~AgentsManager();
	
	void Start();
	
	void StopAndWait();

private:
	//uncopyable objects
	AgentsManager(const AgentsManager&);
	AgentsManager& operator=(const AgentsManager&);

	std::vector<PThread_sp> m_agents;

};

typedef std::tr1::shared_ptr<AgentsManager> AgentsManager_sp;


}//endof namespace advcpp











#endif //__AGENTSMANAGER_H__

