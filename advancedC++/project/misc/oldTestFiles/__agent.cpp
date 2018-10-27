

#include "agent.h"


Agent* CreateAgent()
{
	return new MyAgent;
}


void DestroyAgent(Agent* _a)
{
	delete _a;
}

void MyAgent::DoHello()
{
	std::cout<<"Hello World!"<<std::endl;

}





void MyAgent::DoMore()
{
	std::cout<<"Hello HELLO HeLlO !!! World!"<<std::endl;

}








