
#include "DAstruct.h"
#include <stdio.h>
#include <limits.h>

#define PASS 0
#define FAIL 1

void run_test(int(*test)()){
 
 	printf("Test %s.\n",(test()==PASS)?"passed":"failed");
}


/*testing createDA*/
int test1(void) {

	da_t* ptr;

	/*NULL input pointer check*/
	ptr = createDA(5,1);
	if (ptr==NULL){
		return FAIL;
	}
	destroyDA(ptr);
	
	ptr = createDA(4E10,1);
	if (ptr!=NULL){
		destroyDA(ptr);
		return FAIL;
	}
	
	/*size=0 and inc_block_size=0 error check*/
	ptr = createDA(0,0);
	if (ptr!=NULL){
		destroyDA(ptr);
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

	da_t* ptr;
	
	/*data overflow check*/
	if ((ptr = createDA(1,0))==NULL) {
		fprintf(stderr,"Memoty Allocation Error.\n");
		exit(1);
	}
	insertDA(ptr,5);
	if (insertDA(ptr,2)!=DATA_OVERFLOW){
		destroyDA(ptr);
		return FAIL;
	}
	destroyDA(ptr);
	return PASS;
}

/*testing insertDA on several inputs
 *also positevly testing removeDA !
 */
int test4(void) {

	da_t* ptr;
	size_t size=2,inc_block_size=1;
	int i,data;

	if ((ptr = createDA(size,inc_block_size))==NULL) {
		fprintf(stderr,"Memoty Allocation Error.\n");
		exit(1);
	}
	for (i=0; i<6 ; i++){
		insertDA(ptr,i);
		/*printDA(ptr);*/
	}

	/*also positevly testing removeDA !*/
	for (i=5; i>=0 ; i--){
		removeDA(ptr,&data);
		if (data!=i) {
			destroyDA(ptr);	
			return FAIL;
		};
	}
}
/*realloc fail check
 *realloc test could take LONG TIME !!! (~5 min)
 */
 int test5(void){
 
	da_t *ptr;
	unsigned long big_i;
	
	if ((ptr = createDA(10,1E3))==NULL) {
		fprintf(stderr,"Memoty Allocation Error.\n");
		exit(1);
	}
	
	for (big_i=0 ; big_i<ULLONG_MAX ; ++big_i)
		if (insertDA(ptr,2)==REALLOC_FAIL){
			destroyDA(ptr);
			return PASS;
	}
	destroyDA(ptr);
	return FAIL;
}

/*testing removeDA input check*/
int test6(void) {

	da_t *ptr;
	int data;

	/*null pointer input check*/
	if (removeDA(NULL,&data)!=POINTER_NOT_INITIALIZED){
		return FAIL;
	}
	
	if ((ptr = createDA(1,2))==NULL) {
		fprintf(stderr,"Memoty Allocation Error.\n");
		exit(1);
	}
	if (removeDA(ptr,NULL)!=POINTER_NOT_INITIALIZED){
		destroyDA(ptr);
		return FAIL;
	}
	destroyDA(ptr);

	/*data underfow check*/
	if ((ptr = createDA(0,2))==NULL) {
		fprintf(stderr,"Memoty Allocation Error.\n");
		exit(1);
	}
	if (removeDA(ptr,&data)!=DATA_UNDERFLOW){
		destroyDA(ptr);
		return FAIL;
	}
	return PASS;
}

/*testing removeDA on several inputs*/
int test7(void) {

	da_t *ptr,*ptr2;
	int i, data;
	size_t size=1 ,inc_block_size=2;

	if ((ptr = createDA(size,inc_block_size))==NULL) {
		fprintf(stderr,"Memoty Allocation Error.\n");
		exit(1);
	}
	for (i=0; i<6 ; i++){
		insertDA(ptr,i);
	}
	/*printDA(ptr);*/
	
	for (i=5; i>=0 ; i--){
		ptr2=ptr;
		removeDA(ptr,&data);
		/*ptr integrity*/
		if (ptr!=ptr2){
			destroyDA(ptr);	
			return FAIL;
		}
		/*printDA(ptr);*/
		/*printf("data=%d;",data);*/
		if (data!=i){
			destroyDA(ptr);	
			return FAIL;
		};
	}

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
	run_test(test7);
/*	run_test(test8);
	run_test(test9);
	run_test(test10);
*/
	return 0;
}
