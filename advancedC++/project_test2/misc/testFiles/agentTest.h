#ifndef __AGEN1T_H__
#define __AGENT1_H__


#include<vector>

//interface
class Agent
{
public:

	virtual
	~Agent()
	{}
	
	virtual
	void DoSomething()=0;


};

class MyAgent
:	public Agent
{
public:

	virtual
	void DoSomething();

};



typedef Agent*(*Creator)();

extern "C"
std::vector<Creator>* getFuncsVector();




#endif //__AGEN1T_H__

