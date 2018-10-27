
#include <stdio.h>
#include <string.h>
#include <stdlib.h>





/*
void SwapPtr(void *_ptr1, void *_ptr2)
{
	void *temp;
	size_t s=sizeof(void*);
	
	temp = malloc(s);
	
	memcpy(temp,_ptr1,s);
	memcpy(_ptr1,_ptr2,s);
	memcpy(_ptr2,temp,s);
	
	free(temp);
}
*/

void Swap(void *_elem1, void *_elem2, size_t _elemSize)
{
	void *temp;
	
	temp = malloc(_elemSize);
	
	memcpy(temp,_elem1,_elemSize);
	memcpy(_elem1,_elem2,_elemSize);
	memcpy(_elem2,temp,_elemSize);
	
	free(temp);
}

int strCompare(const void *_str1, const void *_str2)
{
	const char *string1 = (const char*)_str1,
		 *string2 = (const char*)_str2;
		 
	return strcmp(string1,string2);
}


int main()
{

	int a=5, b=10;
	
	/*	
	int *intPtr1, *intPtr2;
	intPtr1 = intArr;
	int intArr[5];
	intPtr2 = intArr+2;
	

	printf("first ptr=%p second ptr=%p\n",(void*)intPtr1,(void*)intPtr2);
	
	Swap(&intPtr1,&intPtr2,sizeof(int*));
	
	printf("first ptr=%p second ptr=%p\n",(void*)intPtr1,(void*)intPtr2);
	*/
	printf("first num=%d second num=%d\n",a,b);
	
	Swap(&a,&b,sizeof(int));
	
	printf("first num=%d second num=%d\n",a,b);
	






	return 0;
}









