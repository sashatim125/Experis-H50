
/*This file contains tests for Daily Appointment Diary API from "DADiary.h".
 *
 *AUTHOR        : Timoshenko Alexander
 *LAST MODIFIED : 02.12.2017
 */

#include "DAdiary.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define PASS 0
#define FAIL 1

/*initial meetings array size*/
#define INIT_SIZE 10
/*inc block size*/
#define INC_BLOCK_SIZE 10

void run_test(int i,int(*test)()){
 
 	printf("Test #%02d %s.\n",i,(test()==PASS)?"passed":"failed");
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
		exit(EXIT_FAILURE);
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
		exit(EXIT_FAILURE);
	}
	
	if (create_meet(1,2,3,&meet_ptr)!=DAD_OK){
		fprintf(stderr,"Meeting creation Error.\n");
		exit(EXIT_FAILURE);
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
		exit(EXIT_FAILURE);
	}
	
	if(find_meet(dad_ptr,5,&end_h,&room)!=NO_MEETINGS){
		destroy_meet(meet_ptr);
		destroyDAD(dad_ptr);
		return FAIL;
	}
	
	if (create_meet(1,2,3,&meet_ptr)!=DAD_OK){
		fprintf(stderr,"Meeting creation Error.\n");
		exit(EXIT_FAILURE);
	}
	if (insert_meet(dad_ptr,meet_ptr)!=DAD_OK) {
		fprintf(stderr,"Meeting insertion Error.\n");
		exit(EXIT_FAILURE);
	}
	
	
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
		exit(EXIT_FAILURE);
	}
	
	
	for (i=0 ; i<15 ; ++i){
		if (create_meet((float)i,(float)i+0.5,i,&meet_ptr)!=DAD_OK){
			fprintf(stderr,"Meeting creation Error.\n");
			exit(EXIT_FAILURE);
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




/*testing remove_meet check*/
int test8(void) {

	dad_t* dad_ptr;
	meet_t *meet_ptr;
	hour_t end_h;
	int i,room;

	if ((dad_ptr = createDAD())==NULL) {
		fprintf(stderr,"Memory Allocation Error.\n");
		exit(EXIT_FAILURE);
	}

	/*null pointer input check*/
	if (remove_meet(NULL,0)!=POINTER_NOT_INITIALIZED){
		destroyDAD(dad_ptr);
		return FAIL;
	}
	/*hour input check*/
	if (remove_meet(dad_ptr,-1)!=HOUR_TOO_EARLY){
		destroyDAD(dad_ptr);
		return FAIL;
	}
	if (remove_meet(dad_ptr,25)!=HOUR_TOO_LATE){
		destroyDAD(dad_ptr);
		return FAIL;
	}
	if (remove_meet(dad_ptr,2)!=NO_MEETINGS){
		destroyDAD(dad_ptr);
		return FAIL;
	}
	
	for (i=0 ; i<15 ; ++i){
		if (create_meet((float)i,(float)i+0.5,i,&meet_ptr)!=DAD_OK){
			fprintf(stderr,"Meeting creation Error.\n");
			exit(EXIT_FAILURE);
		}
		if (insert_meet(dad_ptr,meet_ptr)!=DAD_OK) {
			fprintf(stderr,"Meeting insertion Error.\n");
			exit(EXIT_FAILURE);
		}
	}
	/*removing wrong meeting)*/
	if (remove_meet(dad_ptr,20)!=NO_SUCH_MEETING){
			destroyDAD(dad_ptr);
			return FAIL;	
	}
	/*removing meetings*/
	for (i=14 ; i>=0 ; --i){
		if (remove_meet(dad_ptr,(hour_t)i)!=DAD_OK){
			destroyDAD(dad_ptr);
			return FAIL;	
		}
	}
	
	destroyDAD(dad_ptr);
	return PASS;
}

/*testing fprintDAD input*/
 int test9(void) {

	FILE *file;
	dad_t *dad_ptr;
	
	if ((dad_ptr = createDAD())==NULL) {
		fprintf(stderr,"Memory Allocation Error.\n");
		exit(EXIT_FAILURE);
	}
	
	if ((file=fopen("test_file","w"))==NULL){
			fprintf(stderr,"File opening error.\n");
			exit(EXIT_FAILURE);
	}
	
	if (fprintDAD(NULL,dad_ptr)!=POINTER_NOT_INITIALIZED){
			fclose(file);
			destroyDAD(dad_ptr);
			return FAIL;	
	}
	if (fprintDAD(file,NULL)!=POINTER_NOT_INITIALIZED){
			fclose(file);
			destroyDAD(dad_ptr);
			return FAIL;	
	}
	
	destroyDAD(dad_ptr);
	return PASS;
}

/*testing floadDAD */
 int test10(void) {

	FILE *file;
	dad_t* dad_ptr;
	meet_t *meet_ptr;
	hour_t end_h;
	int i,room;
	
	/*input check*/
	if (floadDAD(NULL)!=NULL){
		return FAIL;	
	}
	/*creating new diary*/
	if ((file=fopen("test_file","w"))==NULL){
			fprintf(stderr,"File opening error.\n");
			exit(EXIT_FAILURE);
	}
	if ((dad_ptr = createDAD())==NULL) {
		fprintf(stderr,"Memory Allocation Error.\n");
		exit(EXIT_FAILURE);
	}
		
	for (i=0 ; i<15 ; ++i){
		if (create_meet((hour_t)i,(hour_t)i+0.5,i,&meet_ptr)!=DAD_OK){
			fprintf(stderr,"Meeting creation Error.\n");
			exit(EXIT_FAILURE);
		}
		if (insert_meet(dad_ptr,meet_ptr)!=DAD_OK) {
			fprintf(stderr,"Meeting insertion Error.\n");
			exit(EXIT_FAILURE);
		}
	}
	/*saving the diary*/
	if (fprintDAD(file,dad_ptr)!=DAD_OK){
		fprintf(stderr,"Diary saving error.\n");
		exit(EXIT_FAILURE);		
	}
	if (fclose(file)!=0){
			fprintf(stderr,"File closing error.\n");
			exit(EXIT_FAILURE);
	}
	destroyDAD(dad_ptr);
	dad_ptr=NULL;
	
	/*loading the diary*/
	if ((file=fopen("test_file","r"))==NULL){
			fprintf(stderr,"File opening error.\n");
			exit(EXIT_FAILURE);
	}
	if ((dad_ptr=floadDAD(file))==NULL){
		fclose(file);
		return FAIL;	
	}
	if (fclose(file)!=0){
		fprintf(stderr,"File closing error.\n");
		exit(EXIT_FAILURE);
	}
	/*checking the loaded diary*/
	for (i=0 ; i<15 ; ++i){
		if (find_meet(dad_ptr,(hour_t)i,&end_h,&room)!=DAD_OK){
			destroyDAD(dad_ptr);
			return FAIL;	
		}
		if ((end_h!=(hour_t)i+0.5) || (room!=i)) {
			destroyDAD(dad_ptr);
			return FAIL;
		}
	}
	
	destroyDAD(dad_ptr);
	return PASS;
}


int main() {

	run_test(1,test1);
	run_test(2,test2);
	run_test(3,test3);
	run_test(4,test4);
	run_test(5,test5);
	run_test(6,test6);
	run_test(7,test7);
	run_test(8,test8);
	run_test(9,test9);
	run_test(10,test10);

	return 0;
}
