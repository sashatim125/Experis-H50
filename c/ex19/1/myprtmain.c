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
	
	count=myprintf("My test string #%d and my %s number %f are 100%% OK!\n",1,"\"TEST STRING\"",2.0);

	myprintf("The number of characters printed is %d.\n",count);
	
	if (myprintf("Error %k string")>=0) {
		myprintf("Something wrong!\n");
	}



	return 0;
}



