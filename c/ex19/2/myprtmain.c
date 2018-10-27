/*This file contains the main for my printf function.
 *AUTHOR        : Timoshenko Alexander
 *LAST MODIFIED : 09.12.2017
 */
 
#include "myprt.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

int main(){

	int count;
	
	count=myprintf("My test string #%d and my %s number %f are 100%% OK!\n",1,"\"TEST STRING\"",2.15);

	myprintf("The number of characters printed is %d.\n",count);
	
	if (myprintf("Error %k string")>=0) {
		myprintf("Something wrong!\n");
	}

	myprintf2("Now using %%%%%%strtok%%%%%%=>\n");
	count=myprintf2("My test string #%d and my %s number %f are 100%% OK!\n",1,"\"TEST STRING\"",2.125521);
	
	myprintf2("The number of characters printed is %d.\n",count);
	
	if (myprintf2("Error %k string")>=0) {
		myprintf("Something wrong!\n");
	}
	return 0;
}



