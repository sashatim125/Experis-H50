/*This file contains the main and hanoi towers function.
 *AUTHOR        : Timoshenko Alexander
 *LAST MODIFIED : 13.12.2017
 */

#include <stdio.h>


void Hanoi(int _n,char _from, char _to, char _via)
{
	if (_n==0)
	{
		return;
	}
	Hanoi(_n-1,_from,_via,_to);
	printf("Move %d from %c to %c.\n",_n,_from,_to);
	Hanoi(_n-1,_via,_to,_from);
}



int main()
{
	int n;
	
	printf("Welcome to Hanoi Tower Solver !\n");
	printf("Please enter the number of rings :");
	scanf("%d",&n);
	Hanoi(n,'A','B','C');

	return 0;
}










