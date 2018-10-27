
// 
//  @file agentsManager.cpp
//  @brief Agents Manager
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//



#include "agentsManager.h"

namespace advcpp
{


AgentsManager::AgentsManager(
	const ConfigurationMaker& _configMaker,
	AgentsLoadersManager& _alm,
	Registrator* _r,
	EventsReceiver* _er)
{
	const std::list<Configuration>& agentsConfigList = _configMaker.GetConfigList();
	std::list<Configuration>::const_iterator it = agentsConfigList.begin();
	std::list<Configuration>::const_iterator end = agentsConfigList.end();
	
	for(; it != end; ++it)
	{
		PThread_sp newAgent(new PThread(_alm.CreateAgent(*it,_r,_er)));
		if(0 == newAgent->GetRunnable().get())
		{
			std::ostringstream os;
			os<<"The agent with id: '"<<it->m_id<<"', type: '"<<it->m_type<<"' can't be created."<<std::endl;
			throw std::runtime_error(os.str());
		}
		m_agents.push_back(newAgent);
	}
	
	_alm.ReleaseUnusedAgentsLoaders();
}


void AgentsManager::Start()
{
	size_t i=0 , vecSize = m_agents.size();
	for(; i < vecSize ; ++i)
	{
		m_agents[i]->Start();
	}
}



	
void AgentsManager::StopAndWait()
{
	size_t i=0 , vecSize = m_agents.size();
	//TODO TEST
	//std::cout<<"Num of agents "<<vecSize<<"\n"<<std::endl;
	Agent *nextAgent;
	for(; i < vecSize ; ++i)
	{
		nextAgent = static_cast<Agent*>(((m_agents[i])->GetRunnable()).get());
		nextAgent->Stop();
	}
	
	//TODO TEST
	//std::cout<<"Agents stopped !\n"<<std::endl;
	for(i=0; i < vecSize ; ++i)
	{
		m_agents[i]->Join();
	}
	//TODO TEST
	//std::cout<<"Agents joined !\n"<<std::endl;
}


}//endof namespace advcpp










