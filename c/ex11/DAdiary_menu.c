
/*This file contains the running menu for Daily Appointment Diary.
 *Creating the diary , creating individual meetings,
 *inserting and removing meeting from a diary;
 *printing the diary;
 *saving the diary to and loading from the file; 
 *also deleting individual meetings and the diary as well.
 *
 *AUTHOR        : Timoshenko Alexander
 *LAST MODIFIED : 02.12.2017
 */

#include "DAdiary.h"
#include <stdlib.h>
#include <stdio.h>

/*initial meetings array size*/
#define INIT_SIZE 10
/*inc block size*/
#define INC_SIZE 10

#define DIARY_FILE "dfile.data"

#define DIARY_DOESNT_EXISTS_CHECK(diary)\
{\
	if (diary ==NULL){\
		printf("The diary doesn't exist.\n");\
		break;\
	}\
}

enum choice {
	CR_DIARY=1,
	DEL_DIARY=2,
	CR_MEET=3,
	DEL_MEET=4,
	INS_MEET=5,
	REM_MEET=6,
	FIND_MEET=7,
	PR_DIARY=8,
	SAVE_DIARY=9,
	LOAD_DIARY=10,
	EXIT_APP=11
}

int main() {

	dad_t *diary=NULL;
	meet_t *meeting=NULL;
	int menu , room;
	hour_t begin_hour , end_hour;
	DAD_error meet_err;
	FILE *dad_file;


	while(TRUE){
		printf("\n\nWelcome to the Daily Appointment Diary !\n");
		printf("MENU :\n");
		printf("1  - create the new diary;\n");
		printf("2  - delete the diary;\n");
		printf("3  - create the new meeting for the diary;\n");
		printf("4  - delete the meeting;\n");
		printf("5  - insert the meeting to the diary;\n");
		printf("6  - remove a meeting from the diary;\n");
		printf("7  - find the meeting in the diary;\n");
		printf("8  - print the diary.\n");
		printf("9  - save the diary to the file.\n");
		printf("10 - Load the diary from the file.\n");
		printf("11 - exit the diary program.\n");
		printf("Make your choise :");

		if (scanf("%d",&menu)!=1){
			menu=-1;
		}
		/*use #define or enum*/
		switch (menu) {
			case CR_DIARY : 
				if (diary !=NULL){
					printf("The diary allready exists\n");
					break;	
				}
				if ((diary=createDAD())==NULL) {
					printf("Diary creating error !\n");
					exit(EXIT_FAILURE);
				}
				printf("Diary created !\n");
				break;
			case DEL_DIARY :
				DIARY_DOESNT_EXISTS_CHECK(diary)
				
				destroyDAD(diary);
				diary=NULL;
				printf("The diary deleted.\n");
				break;
			case CR_MEET :
				if (meeting !=NULL){
					printf("The meeting allready exists.\n");
					break;	
				}
				printf("Please enter the start hour :");
				scanf("%f",&begin_hour);
				printf("Please enter the end hour :");
				scanf("%f",&end_hour);
				printf("Please enter the room number :");
				scanf("%d",&room);
				
				meet_err=create_meet(begin_hour,end_hour,room,&meeting);
				switch (meet_err) {
					case DAD_OK :
						printf("Meeting created!\n");
						break;
					case HOUR_TOO_EARLY:
					case HOUR_TOO_LATE :
					case INCONS_HOURS :
						printf("Wrong hours!\n");
						break;
					case ALLOC_FAIL:
					printf("Memory allocation error!\n");
					break;
				}	
				break;
			case DEL_MEET :
				if (meeting==NULL){
					printf("The meeting doesn't exist.\n");
					break;
				}
				destroy_meet(meeting);
				meeting=NULL;
				printf("The meeting deleted.\n");
				break;
			case INS_MEET :
				DIARY_DOESNT_EXISTS_CHECK(diary)
				
				if (meeting==NULL){
					printf("The meeting doesn't exist.\n");
					break;
				}
				meet_err=insert_meet(diary,meeting);
				switch (meet_err) {
					case DAD_OK :
						printf("Meeting inserted!\n");
						meeting=NULL;
						break;
					case MEETINGS_OVERLAP:
						printf("It overlaps with one of the meetings!\n");
						break;
					case REALLOC_FAIL:
					printf("Memory allocation error!\n");
					break;
				}	
				break;
			case REM_MEET :
				DIARY_DOESNT_EXISTS_CHECK(diary)
				
				printf("Please enter the start hour :");
				scanf("%f",&begin_hour);
				meet_err=remove_meet(diary,begin_hour);
				switch (meet_err) {
					case DAD_OK :
						printf("Meeting removed!\n");
						break;
					case HOUR_TOO_EARLY:
					case HOUR_TOO_LATE :
						printf("Wrong hours!\n");
						break;
					case NO_MEETINGS :
					printf("No meetings at all!\n");
					break;
					case NO_SUCH_MEETING :
					printf("No such meeting!\n");
					break;
				}
				break;
			case FIND_MEET :
				DIARY_DOESNT_EXISTS_CHECK(diary)
				
				printf("Please enter the start hour :");
				scanf("%f",&begin_hour);
				meet_err=find_meet(diary,begin_hour,&end_hour,&room);
				switch (meet_err) {
					case DAD_OK :
						printf("The meeting starts at %4.2f, ends at %4.2f in the room %3d.\n",
						       begin_hour,end_hour,room);
						break;
					case HOUR_TOO_EARLY:
					case HOUR_TOO_LATE :
						printf("Wrong hours!\n");
						break;
					case NO_MEETINGS :
					printf("No meetings at all!\n");
					break;
					case NO_SUCH_MEETING :
					printf("No such meeting!\n");
					break;
				}
				break;
			case PR_DIARY :
				DIARY_DOESNT_EXISTS_CHECK(diary)
				
				if ((meet_err=fprintDAD(stdout,diary))!=DAD_OK) {
					printf("Printing failed!\n");
				}
				break;
			case SAVE_DIARY :
				DIARY_DOESNT_EXISTS_CHECK(diary)
				
				if (((dad_file=fopen(DIARY_FILE,"w"))==NULL) || ((meet_err=fprintDAD(dad_file,diary))!=DAD_OK)) {
					printf("Save failed!\n");
				}
				printf("The diary saved.\n");
				if (fclose(dad_file)!=0) {
					fprintf(stderr,"File closing error!\n");
					exit(EXIT_FAILURE);
				}
				break;
			case LOAD_DIARY :
				if (diary !=NULL){
					destroyDAD(diary);
					diary=NULL;
					printf("The current diary deleted.\n");
				}
				if (((dad_file=fopen(DIARY_FILE,"r"))==NULL) || ((diary=floadDAD(dad_file))==NULL)) {
					printf("Loading failed\n");
					if ((dad_file!=NULL) && (fclose(dad_file)!=0)) {
						fprintf(stderr,"File closing error!\n");
						exit(EXIT_FAILURE);
					}
					break;
				}
				printf("The diary loaded.\n");
				if (fclose(dad_file)!=0) {
					fprintf(stderr,"file closing error!\n");
					exit(EXIT_FAILURE);
				}
				break;
				
			case EXIT_APP :
				exit(EXIT_SUCCESS);
				break;
						
			default : 
				printf("Wrong choise !\n");
				exit(EXIT_FAILURE);
				break;
		}
	}
	return 0;
}

