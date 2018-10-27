
#include <iostream>

extern "C"
{
#include <dlfcn.h>
}

#include "agentsLoader.h"
#include "agentExample.h"

#include "configuration.h"
#include "iniFileParser.h"


//#include "event.h"

int main()
{
	
	IniFileParser parser("./config.ini");

	const std::map<std::string, IniFileSection>& sections =
		parser.GetIniSections();
		
		
	std::map<std::string, IniFileSection>::const_iterator it = sections.begin();
	std::map<std::string, IniFileSection>::const_iterator end = sections.end();

	Configuration conf(sections.find("Temperature-1-a")->second);
/*	
		std::cout<<"m_id= "<<conf.m_id<<"\n";
		std::cout<<"m_type= "<<conf.m_type<<"\n";
		std::cout<<"m_floor= "<<conf.m_floor<<"\n";
		std::cout<<"m_room= "<<conf.m_room<<"\n";
		std::cout<<"m_log= "<<conf.m_log<<"\n";
		std::cout<<"m_config= "<<conf.m_config<<"\n";
		std::cout<<std::endl;
*/	
	AgentsLoader al("./LgSensorsLib.so");

	AgentExample a2;
	
	Agent* agent1 = al.CreateAgent
		(conf,0,&a2);

	agent1->Run();

	al.DestroyAgent(agent1);
	
	std::cout<<std::endl;
	
	conf = Configuration(sections.find("fire-drill-test")->second);
	
	Agent* agent2 = al.CreateAgent
		(conf,0,&a2);

	agent2->Run();


	al.DestroyAgent(agent2);














/*
	void *libHandle;
	
	std::vector<Creator>* (*getFuncs)();
	
	libHandle = dlopen("./agentTest.so",RTLD_LAZY);
	
	if(0==libHandle)
	{
		std::cout<<"Wrong file !\n";
	}
	
	*(void**)&getFuncs = dlsym(libHandle,"getFuncsVector");

	std::vector<Creator>* cr= getFuncs();
	Agent* a = ((*cr)[0])();
	
	a->DoSomething();

	dlclose(libHandle);
*/
	return 0;
}







