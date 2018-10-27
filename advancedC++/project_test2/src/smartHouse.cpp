
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
#include <set>
#include <cstring>

#include "smartHouse.h"

using namespace advcpp;

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
:	m_slm(m_q2)
,	m_hub(m_q1,m_q2,m_slm,m_slm,_sc.m_numOfInDispatchers,_sc.m_numOfOutDispatchers)
,	m_logsHolder(_sc.m_iniDir)
,	m_agentsLoadersManager(_sc.m_agentsLibDir)
{

/////setup agents////////
	if(_sc.m_useDB)
	{
		m_agentsManager = AgentsManager_sp(new AgentsManager(*_sc.m_config,m_agentsLoadersManager,&m_hub,&m_hub));
	}else
	{
		m_agentsManager = AgentsManager_sp(new AgentsManager(_sc.m_iniDir,m_agentsLoadersManager,&m_hub,&m_hub));
	}

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















