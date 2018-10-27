
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
 *LAST MODIFIED : 01.12.2017
 */
 
#ifndef _DADIARY_H_
#define _DADIARY_H_

#include <stdio.h>

/*boolean type*/
typedef enum {FALSE=0,TRUE} bool_t;

//errors list*/ 
typedef enum   {DAD_OK=0,
		/*common error*/
		POINTER_NOT_INITIALIZED,
		/*meetings errors*/
		HOUR_TOO_EARLY,
		HOUR_TOO_LATE,
		INCONS_HOURS,
		ALLOC_FAIL,
		/*diary errors*/
		Z_SIZE_Z_REALLOC,
		OVERFLOW,
		REALLOC_FAIL,
		NO_MEETINGS,
		NO_SUCH_MEETING,
		MEETINGS_OVERLAP
		} DAD_error;
/*hours type*/
typedef float hour_t;
              
typedef struct DAD dad_t;
typedef struct MEET meet_t;
 
/*Description :This function creates the Daily Appointment Diary .
 *Input : NONE.
 *Output: pointer to newely created Daily Appointment Diary.
 *Error : NULL if unsuccessful (for any reason).
 */
 dad_t* createDAD(size_t size, size_t inc_size);
 
/*Description :This function destroys the existing Daily Appointment Diary
 *             including ALL the meetings.
 *             Double destroy protection EXISTS.
 *Input : ptr - pointer to the Daily Appointment Diary to be destoyed.
 *Output: NONE.
 *Error : **do nothing** if null pointer error.
 */
void destroyDAD(dad_t* ptr);
 
/*Description :This function creates the meeting.
 *Input : begin_h - begin hour HH.MM ,end_h - end hour HH.MM, meet_prt - pointer to pointer to a new meeting.
 *Output: a new meeting to the parameter meet_ptr and status (one of DAD_error).
 *Error : rellevant DAD_error.
 */
DAD_error create_meet(hour_t begin_h, hour_t end_h,int room, meet_t **meet_ptr);

/*Description :This function destroys the existing meeting.
               DO NOT destroy inserted meeting
               (although the protection exists).
 *             Double destroy protection EXISTS.
 *Input : ptr - pointer to the meeting to be destoyed.
 *Output: NONE.
 *Error : **do nothing** if null pointer error.
 */
void destroy_meet(meet_t* ptr);

/*Description :This function add new element to the Daily Appointment Diary.
 *Input : dad_ptr - pointer to Daily Appointment Diary, meet_ptr - pointer to a meeting.
 *Output: status (one of DAD_error).
 *Error : rellevant DAD_error.
 */
DAD_error insert_meet(dad_t* dad_ptr,meet_t *meet_ptr );

/*Description :This function removes the the meeting which start in begin_h.
 *Input : ptr - pointer to to Daily Appointment Diary, begin_h - start of the removed meeting.
 *Output: status (one of DAD_error).
 *Error : rellevant DAD_error.
 */
DAD_error remove_meet(dad_t* ptr,hour_t begin_h);

/*Description :This function finds the meeting which starts in begin_h.
 *Input : ptr - pointer to Daily Appointment Diary, begin_h - begin hour HH.MM ,
 *        end_h - pointer to end hour HH.MM(output),room - pointer to room number(output).
 *Output: end_h - pointer to end hour HH.MM,room - pointer to room number;
 *        returns status (one of DAD_error).
 *Error : rellevant DAD_error.
 */
DAD_error find_meet(dad_t const *ptr,hour_t begin_h, hour_t *end_h, int *room );

/*Description :This function prints all the meetings in increasing order by start hour to the file.
 *Input : dad_file - pointer to the PREOPENED EMPTY file (with "w"),ptr - pointer to Daily Appointment Diary.
 *Output: prints to dad_file the meetings list;
 *        returns status (one of DAD_error).
 *Error : rellevant DAD_error.
 */
DAD_error fprintDAD(FILE* dad_file,dad_t const *ptr);

/*Description :This function load the Daily Appointment Diary from the file.
 *Input : dad_file - pointer to the PREOPENED file (with "r").
 *Output: pointer to loaded Daily Appointment Diary.
 *Error : NULL if unsuccessful (for any reason).
 */
dad_t* floadDAD(FILE* dad_file);


 
#endif /*_DADIARY_H_*/
