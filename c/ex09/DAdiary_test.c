

#include "DAdiary.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define PASS 0
#define FAIL 1

void run_test(int(*test)()){
 
 	printf("Test %s.\n",(test()==PASS)?"passed":"failed");
}


/*testing createDAD*/
int test1(void) {

	dad_t* ptr;
	
	/* allocation check*/
	ptr = createDAD();
	if (ptr==NULL){
		return FAIL;
	}
	destroyDAD(ptr);
	return PASS;
}

/*testing destroyDAD*/
 int test2(void) {

	dad_t* ptr;
	
	ptr = createDAD();
	if (ptr==NULL){
		fprintf(stderr,"Memory Allocation Error.\n");
		exit(1);
	}
	
	/*double destroy testing*/
	destroyDAD(ptr);
	destroyDAD(ptr);	
	
	return PASS;
}

/*testing create_meet || input check*/
int test3(void) {

	meet_t *ptr;
	
	if (create_meet(1,2,3,NULL)!=POINTER_NOT_INITIALIZED){
		return FAIL;
	}
	
	if ((create_meet(1,2,3,&ptr)!=ALLOC_FAIL)&&(ptr==NULL)){
		return FAIL;
	}
	if (create_meet(-5,2,3,&ptr)!=HOUR_TOO_EARLY){
		destroy_meet(ptr);
		return FAIL;
	}
	if (create_meet(2,-5,3,&ptr)!=HOUR_TOO_EARLY){
		destroy_meet(ptr);
		return FAIL;
	}
	if (create_meet(2,-3,3,&ptr)!=HOUR_TOO_EARLY){
		destroy_meet(ptr);
		return FAIL;
	}
	if (create_meet(25,2,3,&ptr)!=HOUR_TOO_LATE){
		destroy_meet(ptr);
		return FAIL;
	}
	if (create_meet(1,90,3,&ptr)!=HOUR_TOO_LATE){
		destroy_meet(ptr);
		return FAIL;
	}
	if (create_meet(5,2,3,&ptr)!=INCONS_HOURS){
		destroy_meet(ptr);
		return FAIL;
	}
	return PASS;
}

/*testing destroy_meet*/
 int test4(void) {

	meet_t *ptr;

	if (create_meet(1,2,3,&ptr)!=DAD_OK){
		fprintf(stderr,"Meeting creation Error.\n");
		exit(1);
	}
	/*double destroy check*/
	destroy_meet(ptr);
	destroy_meet(ptr);	
	
	return PASS;
}

/*testing insert_meet || input check*/
int test5(void) {

	dad_t* dad_ptr;
	meet_t *meet_ptr;
	
	if ((dad_ptr = createDAD())==NULL) {
		fprintf(stderr,"Memory Allocation Error.\n");
		exit(1);
	}
	
	if (create_meet(1,2,3,&meet_ptr)!=DAD_OK){
		fprintf(stderr,"Meeting creation Error.\n");
		exit(1);
	}
		
	if (insert_meet(NULL,meet_ptr)!=POINTER_NOT_INITIALIZED) {
		destroy_meet(meet_ptr);
		destroyDAD(dad_ptr);
		return FAIL;
	}
	if (insert_meet(dad_ptr,NULL)!=POINTER_NOT_INITIALIZED) {
		destroy_meet(meet_ptr);
		destroyDAD(dad_ptr);
		return FAIL;
	}
	return PASS;
}

/*testing find_meet*/
int test6(void) {

	dad_t* dad_ptr;
	meet_t *meet_ptr;
	hour_t begin_h,end_h;
	int room,i;
	
	if ((dad_ptr = createDAD())==NULL) {
		fprintf(stderr,"Memory Allocation Error.\n");
		exit(1);
	}
	
	if(find_meet(dad_ptr,5,&end_h,&room)!=NO_MEETINGS){
		destroy_meet(meet_ptr);
		destroyDAD(dad_ptr);
		return FAIL;
	}
	
	if (create_meet(1,2,3,&meet_ptr)!=DAD_OK){
		fprintf(stderr,"Meeting creation Error.\n");
		exit(1);
	}
	insert_meet(dad_ptr,meet_ptr);
	
	if (find_meet(NULL,1,&end_h,&room)!=POINTER_NOT_INITIALIZED) {
		destroy_meet(meet_ptr);
		destroyDAD(dad_ptr);
		return FAIL;
	}
	if (find_meet(dad_ptr,1,NULL,&room)!=POINTER_NOT_INITIALIZED) {
		destroy_meet(meet_ptr);
		destroyDAD(dad_ptr);
		return FAIL;
	}
	if (find_meet(dad_ptr,1,&end_h,NULL)!=POINTER_NOT_INITIALIZED) {
		destroy_meet(meet_ptr);
		destroyDAD(dad_ptr);
		return FAIL;
	}
	if (find_meet(dad_ptr,-5,&end_h,&room)!=HOUR_TOO_EARLY) {
		destroy_meet(meet_ptr);
		destroyDAD(dad_ptr);
		return FAIL;
	}
	if (find_meet(dad_ptr,25,&end_h,&room)!=HOUR_TOO_LATE) {
		destroy_meet(meet_ptr);
		destroyDAD(dad_ptr);
		return FAIL;
	}
	if(find_meet(dad_ptr,1,&end_h,&room)!=DAD_OK){
		destroy_meet(meet_ptr);
		destroyDAD(dad_ptr);
		return FAIL;
	}
	if(end_h!=2 || room!=3) {
		destroy_meet(meet_ptr);
		destroyDAD(dad_ptr);
		return FAIL;
	}
	if(find_meet(dad_ptr,5,&end_h,&room)!=NO_SUCH_MEETING){
		destroy_meet(meet_ptr);
		destroyDAD(dad_ptr);
		return FAIL;
	}	
	
	destroy_meet(meet_ptr);
	destroyDAD(dad_ptr);
	return PASS;
}

/*testing insert_meet */
int test7(void) {

	dad_t* dad_ptr;
	meet_t *meet_ptr;
	hour_t end_h;
	int i,room;
	
	if ((dad_ptr = createDAD())==NULL) {
		fprintf(stderr,"Memory Allocation Error.\n");
		exit(1);
	}
	
	
	for (i=0 ; i<15 ; ++i){
		if (create_meet((float)i,(float)i+0.5,i,&meet_ptr)!=DAD_OK){
			fprintf(stderr,"Meeting creation Error.\n");
			exit(1);
		}
		if (insert_meet(dad_ptr,meet_ptr)!=DAD_OK) {
			destroy_meet(meet_ptr);
			destroyDAD(dad_ptr);
			return FAIL;
		}
	}
	for (i=0 ; i<15 ; ++i){
		if (find_meet(dad_ptr,i,&end_h,&room)!=DAD_OK){
			destroyDAD(dad_ptr);
			return FAIL;	
		}
		if ((end_h!=(float)i+0.5) || (room!=i)) {
			destroyDAD(dad_ptr);
			return FAIL;
		}
	}
	destroyDAD(dad_ptr);
	return PASS;
}


/*testing insertDA on several inputs
 *also positevly testing removeDA !
 */
/*int test4(void) {

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
/*	}

	/*also positevly testing removeDA !*/
/*	for (i=5; i>=0 ; i--){
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
/* int test5(void){
 
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
/*int test6(void) {

	da_t *ptr;
	int data;

	/*null pointer input check*/
/*	if (removeDA(NULL,&data)!=POINTER_NOT_INITIALIZED){
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
/*	if ((ptr = createDA(0,2))==NULL) {
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
/*/int test7(void) {

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
	
/*	for (i=5; i>=0 ; i--){
		ptr2=ptr;
		removeDA(ptr,&data);
		/*ptr integrity*/
/*		if (ptr!=ptr2){
			destroyDA(ptr);	
			return FAIL;
		}
		/*printDA(ptr);*/
		/*printf("data=%d;",data);*/
/*		if (data!=i){
			destroyDA(ptr);	
			return FAIL;
		};
	}

	destroyDA(ptr);	
	return PASS;
}

*/
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
