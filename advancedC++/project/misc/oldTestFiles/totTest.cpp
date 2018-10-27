



#include <iostream>



#include "agentsLoader.h"
#include "agentExample.h"

//#include "configuration.h"
#include "iniFileParser.h"

//#include "subscribersList.h"
#include "subscibersListsManager.h"
#include "hub.h"
#include "eventsWaitableQueue.h"
//#include "simpleEvent.h"
#include "pthread_class.h"

using namespace advcpp;

//use name.out .ini_library .so_library
int main(int argc, char *argv[])
{
	IniFileParser parser1(std::string(argv[1])+"log_config.ini");
	const std::map<std::string, IniFileSection>& logSections =
		parser1.GetIniSections();
	
	std::vector<Zlog*> logs;	
	
	for (std::map<std::string, IniFileSection>::const_iterator it = logSections.begin();
		it != logSections.end() ;++it)
	{
		LogConfig logConf(it->second);
		logs.push_back(new Zlog (logConf));
	}
	
	EventsWaitableQueue q1;
	EventsWaitableQueue q2;
	SubscibersListsManager slm(q2);
	
	Hub hub(q1,q2,slm,slm,5,7);

	IniFileParser parser(std::string(argv[1])+"sys_config.ini");
	
	AgentsLoader al1(std::string(argv[2])+"LgSensorsLib.so");
	AgentsLoader al2(std::string(argv[2])+"PhillipsControllersLib.so");
	
	const std::map<std::string, IniFileSection>& sections =
		parser.GetIniSections();
	//std::map<std::string, IniFileSection>::const_iterator it = sections.begin();
	//std::map<std::string, IniFileSection>::const_iterator end = sections.end();
	
	Configuration conf(sections.find("Temperature-1-a")->second);
	Agent* tempSensor = al1.CreateAgent(conf,0,&hub);
	PThread_sp tempSensorThread = PThread_sp(new PThread(Runnable_sp(tempSensor,AgentsDeleter(al1))));
		
	conf = Configuration(sections.find("fire-drill-test")->second);
	Agent* fireSensor = al1.CreateAgent(conf,0,&hub);
	PThread_sp fireSensorThread = PThread_sp(new PThread(Runnable_sp(fireSensor,AgentsDeleter(al1))));

	conf = Configuration(sections.find("hvac-a-1")->second);
	Agent* hvacController = al2.CreateAgent (conf,&hub,0);
	PThread_sp hvacControllerThread = PThread_sp(new PThread(Runnable_sp(hvacController,AgentsDeleter(al2))));
	
	conf = Configuration(sections.find("sprinkler-1-a")->second);
	Agent* sprinkerController = al2.CreateAgent (conf,&hub,0);
	PThread_sp sprinkerControllerThread = PThread_sp(new PThread(Runnable_sp(sprinkerController,AgentsDeleter(al2))));
	
	hub.Run();

	tempSensorThread->Start();
	fireSensorThread->Start();
	hvacControllerThread->Start();
	sprinkerControllerThread->Start();
	
/*	
	tempSensorThread->Join();
	fireSensorThread->Join();
	sleep(5);
	hvacControllerThread->Join();
	sprinkerControllerThread->Join();
*/
	std::string a;
	std::cin>>a;
	
	


	return 0;
}


