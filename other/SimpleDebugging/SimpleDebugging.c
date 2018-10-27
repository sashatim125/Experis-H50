#include <stdio.h>
#include <unistd.h>

int GlovalInt = 0;
int GlovalInt2;
char GlobalChar = 'G';
const char * Glovalchar = "This Is Global char";

int FunctionC( int FCInt, const char * FCchar)
{
	int FCIntLocal;
	for (int i=0;i<5;i++)
	{
		printf("C");
		fflush(stdout);
		sleep(5);
		printf("%c",GlobalChar);
		fflush(stdout);
		GlobalChar = '1';
		FCIntLocal = i;
	}
	return FCIntLocal;
}

int FunctionB( int FBInt, const char * FBchar)
{
	int FBIntLocal;
	for (int i=0;i<5;i++)
	{
		printf("B");
		fflush(stdout);
		sleep(1);
		printf("%c",GlobalChar);
		fflush(stdout);
		FBIntLocal = FunctionC(i,"Calling Function C");
		GlobalChar = '2';
	}
	return FBIntLocal;
}

int FunctionA( int FAInt, const char * FAchar)
{
	int FAIntLocal;
	for (int i=0;i<5;i++)
	{
		printf("A");
		fflush(stdout);
		sleep(1);
		printf("%c",GlobalChar);
		fflush(stdout);
		FAIntLocal = FunctionB(i,"Calling Function B");
		GlobalChar = '3';
	}
	return FAIntLocal;
}

int main ()
{
	int MainIntLocal;
    	puts("Starting program\n");
	for (int i=0;i<5;i++)
	{
		printf("M");
		fflush(stdout);
		sleep(1);
		printf("%c",GlobalChar);
		fflush(stdout);
		MainIntLocal = FunctionA(i,"Calling Function A");
		printf("%c",GlobalChar);
		fflush(stdout);
	}
    	puts("Press enter to terminate\n");
	getchar();
	return(MainIntLocal);
}
