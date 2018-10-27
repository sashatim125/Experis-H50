
/*This file contains API for Daily Appointment Diary.
 *Creating diaries , creating individual meetings,
 *inserting and removing meeting from a diary;
 *printing the diary;
 *saving the diary to and loading from the file; 
 *also destroying individual meetings and diaries as well.
 *Every diary created MUST also be destroyed
 *and every meeting created and uninserted MUST also be destroyed.
 *
 *AUTHOR        : Timoshenko Alexander
 *LAST MODIFIED : 02.12.2017
 */

#include "DAdiary.h"
#include <limits.h>/*magic number*/
#include <stdlib.h>
#include <stdio.h>

/*magic number*/
#define MAGIC_NUM INT_MAX/7

/*constans for loading*/
/*buffer for loading from file*/
#define BUFF_SIZE 100

/*initial meetings array size*/
#define INIT_SIZE 10
/*inc block size*/
#define INC_SIZE 10

/*POINTER_NOT_INITIALIZED check*/
#define POINTER_NOT_INITIALIZED_CHECK(ptr)\
{\
	if (ptr==NULL) {\
		return POINTER_NOT_INITIALIZED;\
	}\
}

/*HOUR check*/
#define HOUR_CHECK(hour)\
{\
	if (hour< 0.0) {\
		return HOUR_TOO_EARLY;\
	}\
	if (hour>23.99) {\
		return HOUR_TOO_LATE;\
	}\
}

struct DAD{
	meet_t **meetings;
	hour_t first_meet_begin;
	hour_t last_meet_end;
	size_t size;
	size_t inc_size;
	size_t num_of_meet;
	
	int DDP;/*double destroy protection*/
};

struct MEET{
	hour_t b_h;
	hour_t e_h;
	int room;

	bool_t is_inserted;/*inserted meeting destroy protection*/
	int DDP;/*double destroy protection*/
};

/*checks if 2 meetings are overlaping*/
bool_t is_meet_overlap(meet_t const *meet1, meet_t const *meet2);

/*entering the last meeting to it's appropriate place*/
void last_meet_enter(meet_t **meetings, size_t size);

/*order meetings after the removal*/
void order_meetings(meet_t **meetings, size_t size, size_t emp_el);

/*find the meeting and return its number*/
DAD_error find_meet_num(dad_t const *ptr,hour_t begin_h,int *num);

dad_t* createDAD(size_t size, size_t inc_size){

	dad_t *new_dad;
	
	/*check for size=0 AND incrementation size=0*/
	if (size == 0 && inc_size == 0) {
		return Z_SIZE_Z_REALLOC;
	}
		
	/*failed allocation*/
	if ((new_dad=(dad_t*)malloc(sizeof(dad_t)))==NULL){
		return NULL;
	}
	/*failed allocation*/
	if ((new_dad->meetings=(meet_t**)malloc(size*sizeof(meet_t*)))==NULL){
		free(new_dad);
		return NULL;
	}
	new_dad->size=size;
	new_dad->inc_size=inc_size;
	new_dad->num_of_meet=0;
	
	new_dad->DDP=MAGIC_NUM;
	
	return new_dad;
}

void destroyDAD(dad_t* ptr){

	int i;
	
	if (ptr==NULL || ptr->DDP!=MAGIC_NUM){
		return;
	}
	ptr->DDP=0;
	
	for(i=0 ; i<ptr->num_of_meet ; ++i){
		((ptr->meetings)[i])->is_inserted=FALSE;
		destroy_meet((ptr->meetings)[i]);
	}
	
	free((void*)(ptr->meetings));
	free((void*)ptr);
}

DAD_error create_meet(hour_t begin_h, hour_t end_h,int room, meet_t **meet_ptr){

	meet_t *new_meet;
	
	/*params check*/
	POINTER_NOT_INITIALIZED_CHECK(meet_ptr)
	HOUR_CHECK(begin_h)
	HOUR_CHECK(end_h)
	/*inconsistent hours*/
	if (begin_h>=end_h) {
		return INCONS_HOURS;
	}
		
	/*failed allocation*/
	if ((new_meet=(meet_t*)malloc(sizeof(meet_t)))==NULL){
		return ALLOC_FAIL;
	}
	new_meet->b_h=begin_h;
	new_meet->e_h=end_h;
	new_meet->room=room;
	
	new_meet->is_inserted=FALSE;
	new_meet->DDP=MAGIC_NUM;
	
	*meet_ptr=new_meet;
	
	return DAD_OK;
}

void destroy_meet(meet_t* ptr){
	
	if (ptr==NULL || ptr->DDP!=MAGIC_NUM || ptr->is_inserted==TRUE){
		return;
	}
	ptr->DDP=0;
	free((void*)ptr);
}

DAD_error insert_meet(dad_t* dad_ptr,meet_t *meet_ptr ){
/*TODO make more functions*/
	int i;
	meet_t** new_meetings;
	
	/*params check*/
	POINTER_NOT_INITIALIZED_CHECK(dad_ptr)
	POINTER_NOT_INITIALIZED_CHECK(meet_ptr)
	/*TODO something more effective*/
	if (dad_ptr->num_of_meet>0) {
		/*a new meeting isn't before or afer all meetings*/
		if (!((meet_ptr->e_h < dad_ptr->first_meet_begin) ||
		      (meet_ptr->b_h > dad_ptr->last_meet_end   ))){
			/*check for meetings overlaping*/
			for(i=0 ; i < dad_ptr->num_of_meet ; ++i){
				if (is_meet_overlap((dad_ptr->meetings)[i],meet_ptr)){
					return MEETINGS_OVERLAP;
				}
			}
		}
	}
	/*is there enought place?*/
	if (dad_ptr->size == dad_ptr->num_of_meet) {
		if ((new_meetings=(meet_t**)realloc((dad_ptr->meetings),(dad_ptr->size+INC_BLOCK_SIZE)*sizeof(meet_t*)))==NULL){
			return REALLOC_FAIL;
		}
		(dad_ptr->size)+=INC_BLOCK_SIZE;
		(dad_ptr->meetings)=new_meetings;
	}
	(dad_ptr->meetings)[dad_ptr->num_of_meet]=meet_ptr;
	++(dad_ptr->num_of_meet);
	last_meet_enter(dad_ptr->meetings,dad_ptr->num_of_meet);
	meet_ptr->is_inserted=TRUE;
	
	/*first/last meetings update*/
	dad_ptr->first_meet_begin = ((dad_ptr->meetings)[0])->b_h;
	dad_ptr->last_meet_end = ((dad_ptr->meetings)[dad_ptr->num_of_meet-1])->e_h;
	
	
	return DAD_OK;
}

DAD_error remove_meet(dad_t* ptr,hour_t begin_h){

	int num;
	DAD_error stat;

	POINTER_NOT_INITIALIZED_CHECK(ptr)
	HOUR_CHECK(begin_h)
	
	if ((stat=find_meet_num(ptr,begin_h,&num))!=DAD_OK){
		return stat;
	}
	
	((ptr->meetings)[num])->is_inserted=FALSE;
	destroy_meet((ptr->meetings)[num]);
	order_meetings(ptr->meetings,ptr->num_of_meet,num);
	--(ptr->num_of_meet);

	return DAD_OK; 
}

DAD_error find_meet(dad_t const *ptr,hour_t begin_h, hour_t *end_h, int *room ){

	int num;
	DAD_error stat;

	POINTER_NOT_INITIALIZED_CHECK(ptr)
	POINTER_NOT_INITIALIZED_CHECK(end_h)
	POINTER_NOT_INITIALIZED_CHECK(room)
	HOUR_CHECK(begin_h)
	
	if ((stat=find_meet_num(ptr,begin_h,&num))!=DAD_OK){
		return stat;
	}
	
	*end_h = ((ptr->meetings)[num])->e_h;
	*room = ((ptr->meetings)[num])->room;

	return DAD_OK; 
}
/*TODO: accept NAME of FILE*/
DAD_error fprintDAD(FILE *f_ptr,dad_t const *ptr){

	int i;

	POINTER_NOT_INITIALIZED_CHECK(f_ptr)
	POINTER_NOT_INITIALIZED_CHECK(ptr)
	
	if (f_ptr == stdout) {
		fprintf(f_ptr,"Daily meeting schedule:\n");
	}
	for (i=0 ; i<ptr->num_of_meet ; ++i) {
		fprintf(f_ptr,"Meeting %3d starts at %05.2f, ends at %05.2f in the room %3d .\n",
		       i+1, ((ptr->meetings)[i])->b_h, ((ptr->meetings)[i])->e_h, ((ptr->meetings)[i])->room);
	}
	if ((i == 0) && (f_ptr==stdout)){
		printf("No meetings today !\n");
	}
	if (f_ptr==stdout) {
		printf("End of daily meeting schedule.\n");
	}
	return DAD_OK;
}

dad_t* floadDAD(FILE* dad_file){

	int room ,i=0;
	hour_t b_h,e_h;
	char buff[BUFF_SIZE];
	dad_t *new_d;
	meet_t *new_m;
	
	/*param check*/
	if (dad_file == NULL) {
		return NULL;
	}
	/*new diary creation*/
	if ((new_d=createDAD(INIT_SIZE,INC_SIZE))==NULL) {
		return NULL;
	}	
	/*file parsing*/
	while (fgets(buff,BUFF_SIZE,dad_file) !=NULL) {
		 if (sscanf(buff,"Meeting %d starts at %f, ends at %f in the room %d .\n",
		     &i,&b_h,&e_h,&room)!=4) {
		 	destroyDAD(new_d);
		 	return NULL;
		 }
		 if (create_meet(b_h,e_h,room,&new_m)!=DAD_OK) {
		 	destroyDAD(new_d);
		 	return NULL;
		 }
		 if (insert_meet(new_d,new_m)!=DAD_OK){
		 	destroyDAD(new_d);
		 	return NULL;
		 }
	}
	/*no meetings*/
	if (i==0) {
		destroyDAD(new_d);
		return NULL;
	}
	
	return new_d;
}

/*checks if 2 meetings are overlaping*/
bool_t is_meet_overlap(meet_t const *meet1, meet_t const *meet2){

	if ((meet1->e_h <= meet2->b_h) || (meet1->b_h >=meet2->e_h)) {
		return FALSE;
	} 
	return TRUE;
}

/*entering the last meeting to it's appropriate place*/
void last_meet_enter(meet_t **meetings, size_t size){

	int i;
	meet_t *new_meet = meetings[size-1];
	hour_t b_h = new_meet->b_h;
	
	if (size==1) {
		return;
	}
	for (i=size-2 ; i>=0 ; --i){
		if (((meetings[i])->b_h) > b_h){
			meetings[i+1]=meetings[i];
		} else break;
	}
	meetings[i+1]=new_meet;
}

/*order meetings after the removal*/
void order_meetings(meet_t **meetings, size_t size, size_t emp_el){

	size_t i;

	for (i=emp_el+1 ; i<size ; ++i){
		meetings[i-1]=meetings[i];
	}
}

/*find the meeting and return its number*/
DAD_error find_meet_num(dad_t const *ptr,hour_t begin_h,int *num){

	int i,j,k;
	hour_t next;

	POINTER_NOT_INITIALIZED_CHECK(ptr)
	POINTER_NOT_INITIALIZED_CHECK(num)
	HOUR_CHECK(begin_h)

	/*no meetings*/
	if (ptr->num_of_meet == 0){
		return NO_MEETINGS;
	}
	/*binary search*/
	for (i=0 ,j=ptr->num_of_meet-1 ; i<=j ; ){
		k=(i+j)/2;
		next = ((ptr->meetings)[k])->b_h;
		if (begin_h == next){
			break;
		} else if (begin_h > next){
			i=k+1;
		} else /*begin_h < next*/ 
			j=k-1;
	}
	if (i>j){
		return NO_SUCH_MEETING;
	}
	
	*num=k;
	return DAD_OK;
}




















