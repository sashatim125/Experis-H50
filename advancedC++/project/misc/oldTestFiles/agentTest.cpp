
#include <iostream>

#include "agentTest.h"




void MyAgent::DoSomething()
{
	std::cout<<"Doing nothing !\n";
}




Agent* CreateAgent()
{
	return new MyAgent;
}



std::vector<Creator> crFuncs ;

std::vector<Creator>* getFuncsVector()
{
	crFuncs.push_back(CreateAgent);
	return &crFuncs;
}




