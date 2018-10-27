#ifndef __AGENT1_H__
#define __AGENT1_H__

#include <iostream>



class Agent
{
public:

	virtual
	~Agent()
	{}
	
	virtual
	void DoHello() =0;
	
	virtual
	void DoMore() =0;




};


class MyAgent : public Agent
{


	virtual
	void DoHello() ;
	
	virtual
	void DoMore();

};

extern "C"
{


Agent* CreateAgent();


void DestroyAgent(Agent* _a);


}




















#endif //__AGENT1_H__

