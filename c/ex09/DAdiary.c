
/*This file contains API for Daily Appointment Diary.
 *Creating diaries , creating individual meetings,
 *inserting and removing meeting from a diary;
 *printing the diary;
 *also destroying individual meetings and diaries as well.
 *Every diary created MUST also be destroyed
 *and every meeting created and uninserted MUST also be destroyed.
 *AUTHOR        : Timoshenko Alexander
 *LAST MODIFIED : 30.11.2017
 */

#include "DAdiary.h"
#include <limits.h>/*magic number*/
#include <stdlib.h>
#include <stdio.h>

/*magic number*/
#define MAGIC_NUM INT_MAX/7
/*initial meetings array size*/
#define INIT_SIZE 10
/*inc block size*/
#define INC_BLOCK_SIZE 10

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
	size_t num_of_meet;
	
	int DDP;/*double destroy protection*/
};

struct MEET{
	hour_t b_h;
	hour_t e_h;
	int room;
	int DDP;/*double destroy protection*/
};

/*checks if 2 meetings are overlaping*/
bool_t is_meet_overlap(meet_t const *meet1, meet_t const *meet2);

/*entering the last meeting to it's appropriate place*/
void last_meet_enter(meet_t **meetings, size_t size);

/*order meetings after the removal*/
void order_meetings(meet_t **meetings, size_t size, size_t emp_el);

dad_t* createDAD(void){

	dad_t *new_dad;
	/*failed allocation*/
	if ((new_dad=(dad_t*)malloc(sizeof(dad_t)))==NULL){
		return NULL;
	}
	/*failed allocation*/
	if ((new_dad->meetings=(meet_t**)malloc(INIT_SIZE*sizeof(meet_t*)))==NULL){
		free(new_dad);
		return NULL;
	}
	new_dad->size=INIT_SIZE;
	new_dad->num_of_meet=0;
	
	new_dad->DDP=MAGIC_NUM;
	
	return new_dad;
}

void destroyDAD(dad_t* ptr){

	size_t i;
	
	if (ptr==NULL || ptr->DDP!=MAGIC_NUM){
		return;
	}
	ptr->DDP=0;
	
	for(i=0 ; i<ptr->num_of_meet ; ++i){
		destroy_meet((ptr->meetings)[i]);
	}
	
	free((void*)(ptr->meetings));
	free((void*)ptr);
}

DAD_error create_meet(hour_t begin_h, hour_t end_h,int room, meet_t **meet_ptr){

	meet_t *new_meet;
	
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
	
	new_meet->DDP=MAGIC_NUM;
	
	*meet_ptr=new_meet;
	
	return DAD_OK;
}

void destroy_meet(meet_t* ptr){
	
	if (ptr==NULL || ptr->DDP!=MAGIC_NUM){
		return;
	}
	ptr->DDP=0;
	free((void*)ptr);
}

DAD_error insert_meet(dad_t* dad_ptr,meet_t *meet_ptr ){

	size_t i;
	meet_t** new_meetings;

	POINTER_NOT_INITIALIZED_CHECK(dad_ptr)
	POINTER_NOT_INITIALIZED_CHECK(meet_ptr)
	
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
	
	dad_ptr->first_meet_begin = ((dad_ptr->meetings)[0])->b_h;
	dad_ptr->last_meet_end = ((dad_ptr->meetings)[dad_ptr->num_of_meet-1])->e_h;
	
	
	return DAD_OK;
}

DAD_error remove_meet(dad_t* ptr,hour_t begin_h){

	size_t i;

	POINTER_NOT_INITIALIZED_CHECK(ptr)
	HOUR_CHECK(begin_h)
	
	/*no meetings*/
	if (ptr->num_of_meet == 0){
		return NO_MEETINGS;
	}
	
	/*no usage of find_meeting because of the overhead*/
	for (i=0 ; i < ptr->num_of_meet ; ++i){
		if (((ptr->meetings)[i])->b_h == begin_h){
			break;/*meeting found*/
		}
	}
	if (i==ptr->num_of_meet){
		return NO_SUCH_MEETING;
	}
	
	order_meetings(ptr->meetings,ptr->num_of_meet,i);
	--(ptr->num_of_meet);

	return DAD_OK; 
}

DAD_error find_meet(dad_t const *ptr,hour_t begin_h, hour_t *end_h, int *room ){

	size_t i;

	POINTER_NOT_INITIALIZED_CHECK(ptr)
	POINTER_NOT_INITIALIZED_CHECK(end_h)
	POINTER_NOT_INITIALIZED_CHECK(room)
	HOUR_CHECK(begin_h)
	
	/*no meetings*/
	if (ptr->num_of_meet == 0){
		return NO_MEETINGS;
	}

	for (i=0 ; i < ptr->num_of_meet ; ++i){
		if (((ptr->meetings)[i])->b_h == begin_h){
			break;/*meeting found*/
		}
	}
	if (i==ptr->num_of_meet){
		return NO_SUCH_MEETING;
	}
	*end_h = ((ptr->meetings)[i])->e_h;
	*room = ((ptr->meetings)[i])->room;

	return DAD_OK; 
}

DAD_error printDAD(dad_t const *ptr){

	size_t i;

	POINTER_NOT_INITIALIZED_CHECK(ptr)
	
	printf("Daily meeting schedule:\n");
	for (i=0 ; i<ptr->num_of_meet ; ++i) {
		printf("Meeting %3lu starts at %4.2f, ends at %4.2f in the room %3d.\n",
		       i+1, ((ptr->meetings)[i])->b_h, ((ptr->meetings)[i])->e_h, ((ptr->meetings)[i])->room);
	}
	if (i == 0){
		printf("No meetins today !\n");
	}
	printf("End of daily meeting schedule.\n");
	
	return DAD_OK;
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
	
	if (size==1) {
		return;
	}
	for (i=size-2 ; i>=0 ; --i){
		if (((meetings[i])->b_h) > (new_meet->b_h)){
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






















