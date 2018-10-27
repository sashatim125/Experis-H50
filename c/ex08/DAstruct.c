
/*This file contains API for Dynamic Alocation data structure
 *(stack of integers).
 *All parametes of size are number of INTEGERS.
 *AUTHOR        : Timoshenko Alexander
 *LAST MODIFIED : 28.11.2017
 */

#include "DAstruct.h"
#include <stdlib.h>
#include <stdio.h>

struct DA {
	int*   array;
	size_t size;
	size_t num_of_elements;
	size_t inc_block_size;
};

da_t* createDA(size_t size,size_t inc_block_size){

	da_t *new_da;
	/*size = 0 and inc_block_size = 0 ===> ERROR*/
	if (size==0 && inc_block_size==0){
		return NULL;
	}
	/*failed allocation*/
	if ((new_da=(da_t*)malloc(sizeof(da_t)))==NULL){
		return NULL;
	}
	/*failed allocation*/
	if ((new_da->array=(int*)malloc(size*sizeof(int)))==NULL){
		free(new_da);
		return NULL;
	}
	new_da->size=size;
	new_da->num_of_elements=0;
	new_da->inc_block_size=inc_block_size;
	return new_da;
}

void destroyDA(da_t* ptr){

	if (ptr!=NULL) {
		free((void*)(ptr->array));
		free((void*)ptr);
	}
}

DA_error insertDA(da_t* ptr,int data){

	int* new_array;

	if (ptr==NULL) {
		return POINTER_NOT_INITIALIZED;
	}

	if (ptr->num_of_elements == ptr->size){
		if (ptr->inc_block_size == 0){
			return DATA_OVERFLOW;
		}
		if ((new_array = (int*)realloc((void*)ptr->array,sizeof(int)*(ptr->size+ptr->inc_block_size)))==NULL) {
			return REALLOC_FAIL;
		}
		(ptr->size)+=(ptr->inc_block_size);
		ptr->array=new_array;
	}
	
	*((ptr->array)+(ptr->num_of_elements)) = data;
	(ptr->num_of_elements)++;

	return DA_OK;
}


DA_error removeDA(da_t* ptr,int* data){

	if (ptr==NULL || data==NULL) {
		return POINTER_NOT_INITIALIZED;
	}

	if (ptr->num_of_elements == 0) {
		return DATA_UNDERFLOW;
	}
	(ptr->num_of_elements)--;
	*data = *((ptr->array)+(ptr->num_of_elements));

	return DA_OK;
}

DA_error printDA(da_t* ptr){

	size_t i;
	
	if (ptr==NULL) {
		return POINTER_NOT_INITIALIZED;
	}
	for (i=0 ; i<(ptr->num_of_elements) ; i++){
		printf("%d ",(ptr->array)[i]);
	}
	putchar('\n');

	return DA_OK;
}



