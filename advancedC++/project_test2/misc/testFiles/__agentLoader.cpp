#ifndef __AGENT1LOADER_H__
#define __AGENT1LOADER_H__

extern "C"
{
#include <dlfcn.h>
#include <stdio.h>
}
#include "agent.h"




int main()
{

	void *libHandle;
	
	Agent* (*CreateFunction)(void);
	
	void (*DestroyFunction)(Agent*);
	
	libHandle = dlopen("agent.so",RTLD_NOW);
	
	if(NULL==libHandle)
	{
		printf("Wrong file !\n");
	}
	
	*(void**)&CreateFunction = dlsym(libHandle,"CreateAgent");
	
	*(void**)&DestroyFunction = dlsym(libHandle,"DestroyAgent");
	
	Agent* a = CreateFunction();
	
	a->DoHello();
	
	a->DoMore();

	//DestroyFunction(a);

	dlclose(libHandle);


	return 0;
}

















#endif//__AGENT1LOADER_H__

