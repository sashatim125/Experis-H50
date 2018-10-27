/*This file contains the menu for simple calculator.
 *AUTHOR        : Timoshenko Alexander
 *LAST MODIFIED : 12.12.2017
 */
 
#include "calc.h"
#include <stdio.h>

#define BUFF_SIZE 256

int main()
{
	char buff1[BUFF_SIZE], buff2[BUFF_SIZE];
	int res;
	
	ADTErr status;
	
	printf("Enter your calculations :\n");
	scanf("%s",buff1);
	
	status=InfixToPostFix(buff1,buff2);
	if(status!=ERR_OK)
		{
			return 1;
		}
	printf("Reverse Polish notation is %s\n",buff2);

	status=MyCalc(buff2,&res);
	if(status!=ERR_OK)
		{
			return 1;
		}
	printf ("The result is %d.\n",res);

	return 0;
}




