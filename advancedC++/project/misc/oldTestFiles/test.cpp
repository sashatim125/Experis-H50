





#include "agentExample.h"
#include "subscribersList.h"
#include "subscibersListsManager.h"
#include "hub.h"
#include "eventsQueue.h"
#include "eventsWaitableQueue.h"
#include "simpleEvent.h"




int main()
{
	
	EventsQueue *q = new EventsWaitableQueue;
	SubscibersListsManager *slm = new SubscibersListsManager;
	
	Hub hub(*q,*slm,*slm);
	AgentExample agent, agent2;
	
	agent.SetReceiver(hub);
	agent2.SetReceiver(hub);
	{
	Location loc("5","");
	Event *event = new SimpleEvent("important",loc);
	
	hub.Register(agent,Event_sp(event));
	}
	
	{
	Location loc("1","");
	Event *event = new SimpleEvent("",loc);
	
	hub.Register(agent2,Event_sp(event));
	}
	agent.Run();
	

	hub.Run();
	
	

	return 0;
}


