




#include <iostream>
#include <signal.h>


#include "smartHouse.h"




int main()
{
	//using SIGUSR2 to simulate fire
	sigset_t sigset;
	sigemptyset(&sigset);
	sigaddset(&sigset,SIGUSR2);
	pthread_sigmask(SIG_BLOCK,&sigset,0);


	DBConnectionConfig DBConf("tcp://127.0.0.1:3306", "root", "student");
	SetupConfig sc("./ini","./lib/agents",5,5,&DBConf,false);

	SmartHouse::MakeSmartHouse(sc);

	std::cout<<"Enter 'stop' to stop."<<std::endl;
	std::string a;
	std::cin>>a;

	return 0;
}



