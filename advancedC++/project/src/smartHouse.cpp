
// 
//  @file smartHouse.cpp
//  @brief Setup and run the system
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//


//#include <iostream> //TODO test

#include "smartHouse.h"

namespace advcpp
{

SmartHouse::SmartHouse_sp SmartHouse::s_SmartHouse;


void SmartHouse::MakeSmartHouse(const SetupConfig& _sc)
{
	if (0 != s_SmartHouse.get())
	{
		return;
	}
	s_SmartHouse = SmartHouse_sp(new SmartHouse(_sc));
}



SmartHouse::SmartHouse(const SetupConfig& _sc)
:	m_subscibersListsManager(m_outEventsQ)
,	m_hub(m_inEventsQ,m_outEventsQ,m_subscibersListsManager,m_subscibersListsManager,_sc.m_numOfInDispatchers,_sc.m_numOfOutDispatchers)
,	m_logsHolder(_sc.m_iniDir)
,	m_agentsLoadersManager(_sc.m_agentsLibDir)
{

/////setup agents////////
	
	std::tr1::shared_ptr<ConfigurationMaker> configMaker;
	
	if(_sc.m_useDB)
	{
		configMaker  = std::tr1::shared_ptr<ConfigurationMaker>(new ConfigurationMaker(*_sc.m_config));
	}else
	{
		configMaker  = std::tr1::shared_ptr<ConfigurationMaker>(new ConfigurationMaker(_sc.m_iniDir));
	}
	
	m_agentsManager = AgentsManager_sp(new AgentsManager(*configMaker,m_agentsLoadersManager,&m_hub,&m_hub));

///////start system///////

	m_hub.Start();

	m_agentsManager->Start();
}

SmartHouse::~SmartHouse()
{
	m_agentsManager->StopAndWait();
	
	m_hub.Stop();
	
	//TODO TEST
	//std::cout<<"Hub stopped !\n"<<std::endl;

	
	//TODO TEST
	//std::cout<<"~Setup finished !\n"<<std::endl;
}


}//endof namespace advcpp












