

#include "myString.h"
#include <stdio.h>
#include <string.h>


#define BUFFER_SIZE 1024


int main()
{
	const char *str1 = "xyzabcdefg_HIJK";
	const char *str2 = "abcde";
	const char *str3 = "abc";
	
	char buff[BUFFER_SIZE];

	StrCpyIt(NULL,str1);
	
	printf("Buffers is : \"%s\".\n",buff);
	
	memset(buff,0,BUFFER_SIZE);
	
	printf("Buffers is : \"%s\".\n",buff);
	
	StrCpyRec(buff,str1);
	
	printf("Buffers is : \"%s\".\n",buff);
	
	
	printf("Buffers is : \"%s\".\n",buff);
	
	memset(buff,0,BUFFER_SIZE);
	printf("Buffers is : \"%s\".\n",buff);

	printf("\nStrCpy tests done.\n\n");
	

	StrNCpyIt(buff,5,str1);
	
	printf("Buffers is : \"%s\".\n",buff);
	
	memset(buff,0,BUFFER_SIZE);
	
	printf("Buffers is : \"%s\".\n",buff);
	
	StrNCpyIt(buff,50,str1);
	
	printf("Buffers is : \"%s\".\n",buff);
	
	memset(buff,0,BUFFER_SIZE);
	
	printf("Buffers is : \"%s\".\n",buff);
	
	printf("\nStrNCpyIt tests done.\n\n");
	
	
	
	StrNCpyRec(buff,5,str1);
	
	printf("Buffers is : \"%s\".\n",buff);
	
	memset(buff,0,BUFFER_SIZE);
	
	printf("Buffers is : \"%s\".\n",buff);
	
	StrNCpyRec(buff,50,str1);
	
	printf("Buffers is : \"%s\".\n",buff);
	
	memset(buff,0,BUFFER_SIZE);
	
	printf("Buffers is : \"%s\".\n",buff);
	
	
	printf("\n\nstring %s is in relation of %d to strinf %s.\n\n",str1,StrCmpIt(str1,str1),str1);
	
	printf("\n\nstring %s is in relation of %d to strinf %s.\n\n",str1,StrCmpIt(str1,str2),str2);
	
	printf("\n\nstring %s is in relation of %d to strinf %s.\n\n",str3,StrCmpIt(str3,str1),str1);
	
	printf("\n\nstring %s is in relation of %d to strinf %s.\n\n",str1,StrCmpRec(str1,str1),str1);
	
	printf("\n\nstring %s is in relation of %d to strinf %s.\n\n",str1,StrCmpRec(str1,str2),str2);
	
	printf("\n\nstring %s is in relation of %d to strinf %s.\n\n",str3,StrCmpRec(str3,str1),str1);
	
	
	
	StrNCpyIt(buff,50,str1);
	printf("Buffers is : \"%s\".\n",buff);
	
	StrCat(buff,str2);
	
	printf("Buffers is : \"%s\".\n\n",buff);
	
	memset(buff,0,BUFFER_SIZE);
	
	printf("the string %s is on string %s in %s.\n\n",str2,str1,StrStr(str1,str2));
	
	printf("the string %s is on string %s in %s.\n\n",str3,str2,StrStr(str2,str3));
	
	printf("the string %s is on string %s in %s.\n\n",str1,str2,StrStr(str2,str1));
	
	







	return 0;
}



