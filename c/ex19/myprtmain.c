/*This file contains the main for my printf function.
 *AUTHOR        : Timoshenko Alexander
 *LAST MODIFIED : 07.12.2017
 */
 
#include "myprt.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

int main(){

	int count;
	
	count=myprintf("My test string #%d and my %s number %f is 100%% OK!",1,"TEST STRING",1.5);

	printf("count=%d.\n",count);



	return 0;
}



