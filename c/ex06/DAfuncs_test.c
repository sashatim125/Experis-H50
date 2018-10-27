
#include "DAfuncs.h"
#include <stdio.h>

#define PASS 0
#define FAIL 1

void run_test(int(*test)()){
 
 	printf("Test %s.\n",(test()==PASS)?"passed":"failed");
}


/*testing createDA*/
 int test1(void) {

	/*NULL input pointer check*/
	int* ptr = createDA(5);
	if (ptr!=NULL){
		free((void*)ptr);
	}
	ptr = createDA(4E10);
	if (ptr!=NULL){
		free((void*)ptr);
		return FAIL;
	}
	return PASS;
}

/*testing destroyDA*/
 int test2(void) {

	return PASS;/*nothing to test :)*/
}

/*testing insertDA input check*/
int test3(void) {

	int arr[10] , data=5 , *ptr=arr;
	size_t size=10 , num_of_elements=5, inc_block_size=2;

	/*null input pointer check*/
	if (insertDA(NULL,data,&size,&num_of_elements,inc_block_size)!=POINTER_NOT_INITIALIZED){
		return FAIL;
	}
	if (insertDA(&ptr,data,NULL,&num_of_elements,inc_block_size)!=POINTER_NOT_INITIALIZED){
		return FAIL;
	}
	if (insertDA(&ptr,data,&size,NULL,inc_block_size)!=POINTER_NOT_INITIALIZED){
		return FAIL;
	}
	/*data overflow check*/
	size=1;num_of_elements=5;
	if (insertDA(&ptr,data,&size,&num_of_elements,inc_block_size)!=DATA_OVERFLOW){
		return FAIL;
	}
	size=5;num_of_elements=5;
	
	if (insertDA(&ptr,data,&size,&num_of_elements,0)!=DATA_OVERFLOW){
		return FAIL;
	}

	return PASS;
}

/*testing insertDA on several inputs*/
int test4(void) {

	int *ptr ,*ptr2, i;
	size_t size=1 , num_of_elements=0, inc_block_size=2;

	if ((ptr = createDA(size))==NULL) {
		fprintf(stderr,"Memoty Allocation Error.\n");
		exit(1);
	}
	for (i=0; i<6 ; i++){
		insertDA(&ptr,i,&size,&num_of_elements,inc_block_size);
		/*printDA(ptr,num_of_elements);*/
	}
	if (num_of_elements!=6 || size!=7){
		destroyDA(ptr);	
		return FAIL;
	}
	for (i=0; i<6 ; i++){
		if (ptr[i]!=i) {
			destroyDA(ptr);	
			return FAIL;
		};
	}
	
	/*ptr integrity check*/
	ptr2=ptr;
	insertDA(&ptr,6,&size,&num_of_elements,inc_block_size);
	if (ptr!=ptr2){
		destroyDA(ptr);	
		return FAIL;
	}
	
	/*realloc fail check*/
	if (insertDA(&ptr,7,&size,&num_of_elements,4E10)!=REALLOC_FAIL){
		destroyDA(ptr);	
		return FAIL;
	}
	
	/*printDA(ptr,num_of_elements);*/
	destroyDA(ptr);	
	return PASS;
}

/*testing removeDA input check*/
int test5(void) {

	int arr[5] , data , *ptr=arr;
	size_t size=10 , num_of_elements=5;

	/*null pointer input check*/
	if (removeDA(NULL,&data,&num_of_elements)!=POINTER_NOT_INITIALIZED){
		return FAIL;
	}
	if (removeDA(ptr,NULL,&num_of_elements)!=POINTER_NOT_INITIALIZED){
		return FAIL;
	}
	if (removeDA(ptr,&data,NULL)!=POINTER_NOT_INITIALIZED){
		return FAIL;
	}
	/*data underfow check*/
	num_of_elements=0;
	if (removeDA(ptr,&data,&num_of_elements)!=DATA_UNDERFLOW){
		return FAIL;
	}
	return PASS;
}

/*testing removeDA on several inputs*/
int test6(void) {

	int *ptr,*ptr2 , i, data;
	size_t size=1 , num_of_elements=0, inc_block_size=2;

	if ((ptr = createDA(size))==NULL) {
		fprintf(stderr,"Memoty Allocation Error.\n");
		exit(1);
	}
	for (i=0; i<6 ; i++){
		insertDA(&ptr,i,&size,&num_of_elements,inc_block_size);
	}
	/*printDA(ptr,num_of_elements);*/
	
	for (i=5; i>=0 ; i--){
		ptr2=ptr;
		removeDA(ptr,&data,&num_of_elements);
		/*ptr integrity*/
		if (ptr!=ptr2){
			destroyDA(ptr);	
			return FAIL;
		}
		/*printDA(ptr,num_of_elements);
		printf("data=%d;",data);*/
		if (data!=i){
			destroyDA(ptr);	
			return FAIL;
		};
	}
	if (num_of_elements!=0){
		destroyDA(ptr);	
		return FAIL;
	}
/*	printDA(ptr,num_of_elements);*/
	destroyDA(ptr);	
	return PASS;
}


int main() {

	run_test(test1);
	run_test(test2);
	run_test(test3);
	run_test(test4);
	run_test(test5);
	run_test(test6);
/*	run_test(test7);
	run_test(test8);
	run_test(test9);
	run_test(test10);
	run_test(test11);
*/
	return 0;
}
