
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



#define SIZE_OF_ARRAY(arr,type) (sizeof(arr)/sizeof(type))



void insertionSort(void *_arr, size_t _numOfElem, size_t _sizeOfElem, int (*_comp)(const void*,const void*))
{

	int i, j , sizeOfElem;
	void *buff;
	
	if((NULL==_arr)||(NULL==_comp))
	{
		return;
	}
	
	if(NULL==(buff = malloc(_sizeOfElem)))
	{
		return;
	}
	
	if(1 >= _numOfElem)
	{
		return;
	}
	sizeOfElem = (int)_sizeOfElem;
	
	i=0;
	
	while (i < _numOfElem-1)
	{
		memcpy(buff,(char*)_arr+sizeOfElem*(i+1),_sizeOfElem);
		j = i;
		
		while(j >= 0)
		{
			if(0 < _comp((char*)_arr+sizeOfElem*j,buff))
			{
				memcpy((char*)_arr+sizeOfElem*(j+1),(char*)_arr+sizeOfElem*j,_sizeOfElem);
				--j;
			}else
			{
				break;
			}
		}
		memcpy((char*)_arr+sizeOfElem*(j+1),buff,_sizeOfElem);
		++i;	
	}
	free(buff);
}


int intComp(const void* _intPtr1,const void* _intPtr2)
{
	return(*(int*)_intPtr1 - *(int*)_intPtr2);
}

int strCompare(const void *_str1, const void *_str2)
{
	const char *string1 = (const char*)_str1,
		 *string2 = (const char*)_str2;
		 
	return strcmp(string1,string2);
}



typedef struct Person
{
	int m_id;
	char *m_name;
} Person;



int PersonCompName(const void *_per1, const void *_per2)
{
	
	return strcmp(((Person*)_per1)->m_name,((Person*)_per2)->m_name);
}

int PersonCompId(const void *_per1, const void *_per2)
{
	
	return (((Person*)_per1)->m_id - ((Person*)_per2)->m_id);
}


int main()
{
/*
	int i, arr[]={-34,45,0,54,-567,30,-76,6,345,2,34,6456,7,43,-67,453,-785,0,674,34,754,34,65,74,54,234,532,4};

	int i,arr[]={10,9,8,7,6,5,4,3,2,1};


	for(i=0 ; i<28 ; ++i)
	{
		printf("%4d ",arr[i]);
	}
	putchar('\n');


	insertionSort(arr,SIZE_OF_ARRAY(arr,int),sizeof(int),intComp);
	
	for(i=0 ; i<28 ; ++i)
	{
		printf("%4d ",arr[i]);
	}
	putchar('\n');

	return 0;
*/
	int i;
	Person arr[]={{1,"b"},{5,"a"},{3,"k"},{10,"r"},{2,"c"}};
	
	for(i=0 ; i < SIZE_OF_ARRAY(arr,Person) ; ++i)
	{
		printf("ID = %2u name=%s.\n",arr[i].m_id,arr[i].m_name);
	}
	
	insertionSort(arr,SIZE_OF_ARRAY(arr,Person),sizeof(Person),PersonCompName);
	
	printf("\nSorted by name.\n\n");
	
	for(i=0 ; i < SIZE_OF_ARRAY(arr,Person) ; ++i)
	{
		printf("ID = %2u name=%s.\n",arr[i].m_id,arr[i].m_name);
	}

	
	insertionSort(arr,SIZE_OF_ARRAY(arr,Person),sizeof(Person),PersonCompId);
	
	printf("\nSorted by ID.\n");
	
	for(i=0 ; i < SIZE_OF_ARRAY(arr,Person) ; ++i)
	{
		printf("ID = %2u name=%s.\n",arr[i].m_id,arr[i].m_name);
	}
	
	return 0;
}




