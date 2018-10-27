
#include <stdio.h>
#include <stddef.h>
#include <string.h>

void a();

void b()
{
	printf("I am in b !!!\n");
	/*a();*/
}


void a()
{
	int d=5;

	printf("I am in a !!!\n");
	
	/*printf("sizeof pointer is %lu and d is %p *(&d) is %p\n",sizeof(void*),b,*(&d+5));*/
	
	*(void**)(&d+5) = b;


}



int main()
{
	a();
	/*b();*/

	printf("BAD !!!\n");

	return 0;
}
