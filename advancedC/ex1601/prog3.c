
#include <stdio.h>
#include <dlfcn.h>
#include "./lib/libDemo.h"

int main()
{

	void *libHandle;
	
	void (*DemoFunction)(void);
	
	libHandle = dlopen("./lib/libDemo.so",RTLD_LAZY);
	
	if(NULL==libHandle)
	{
		perror("Wrong file !\n");
	}
	
	*(void**)&DemoFunction = dlsym(libHandle,"demoFunc1");

	
	DemoFunction();

	

	dlclose(libHandle);


	return 0;
}
