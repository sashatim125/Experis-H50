
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define ASSERT1(exp) \
	do\
	{\
		!(exp)?\
			(fprintf(stderr,"\nI am in file %s, line %d and expression %s.\n",__FILE__,__LINE__,#exp),\
			fprintf(stderr,"My PID is %u.\n\n",getpid()),\
			abort(),1) : 0;\
	}\
	while(0)
	
	
#define ASSERT8(exp)   (exp)? 0 : (3,abort(),1) 


int main()
{
	
	ASSERT8(0);

}


