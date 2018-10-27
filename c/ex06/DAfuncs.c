
/*This file contains API for Dynamic Alocation data structure
 *(stack of integers).
 *All parametes of size are number of INTEGERS.
 *AUTHOR        : Timoshenko Alexander
 *LAST MODIFIED : 27.11.2017
 */

#include "DAfuncs.h"
#include <stdlib.h>
#include <stdio.h>

int* createDA(size_t size){

	return ((int*)malloc(size*sizeof(int)));
}

void destroyDA(int* ptr){

	if (ptr!=NULL) {
		free((void*)ptr);
	}
}

int insertDA(int** ptr,int data, size_t* size, size_t* num_of_elements, size_t inc_block_size){

	int* new_ptr;

	if (ptr==NULL || *ptr==NULL || size==NULL || num_of_elements==NULL) {
		return POINTER_NOT_INITIALIZED;
	}

	if (*num_of_elements > *size) {
		return DATA_OVERFLOW;
	}
	if (*num_of_elements+1>*size){
		if (inc_block_size == 0){
			return DATA_OVERFLOW;
		}
		if ((new_ptr = (int*)realloc((void*)*ptr,sizeof(int)*(*size+inc_block_size)))==NULL) {
			/*printf("%p",(void*)new_ptr);*/
			return REALLOC_FAIL;
		}
		(*size)+=inc_block_size;
		*ptr=new_ptr;
	}
	
	*(*ptr+(*num_of_elements)) = data;
	(*num_of_elements)++;

	return DA_OK;
}


int removeDA(int* ptr,int* data, size_t* num_of_elements){

	if (ptr==NULL || data==NULL || num_of_elements==NULL) {
		return POINTER_NOT_INITIALIZED;
	}

	if (*num_of_elements == 0) {
		return DATA_UNDERFLOW;
	}
	
	*data = *(ptr+(*num_of_elements)-1);
	(*num_of_elements)--;

	return DA_OK;
}

int printDA(int* ptr,size_t num_of_elements){

	int i;
	
	if (ptr==NULL) {
		return POINTER_NOT_INITIALIZED;
	}
	for (i=0 ; i<num_of_elements ; i++){
		printf("%d ",ptr[i]);
	}
	putchar('\n');

	return DA_OK;
}



