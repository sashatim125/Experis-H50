

#include "DAdiary.h"
#include <stdlib.h>
#include <stdio.h>

int main() {

	dad_t *diary=NULL;
	meet_t *meeting=NULL;
	
	int menu , room;
	hour_t begin_hour , end_hour;
	DAD_error meet_err;


	while(TRUE){
		printf("\n\nWelcome to the Daily Appointment Diary !\n");
		printf("MENU :\n");
		printf("1 - create the new diary;\n");
		printf("2 - delete the diary;\n");
		printf("3 - create the new meeting for the diary;\n");
		printf("4 - delete the meeting;\n");
		printf("5 - insert the meeting to the diary;\n");
		printf("6 - remove a meeting from the diary;\n");
		printf("7 - find the meeting in the diary;\n");
		printf("8 - print the diary.\n");
		printf("9 - exit the diary program.\n");
		printf("Make your choise :");
		
		scanf("%d",&menu);
		
		switch (menu) {
			case 1 : 
				if (diary !=NULL){
					printf("The diary allready exists\n");
					break;	
				}
				if ((diary=createDAD())==NULL) {
					printf("Diary creating error !\n");
					exit(1);
				}
				printf("Diary created !\n");
				break;
			case 2 :
				if (diary ==NULL){
					printf("The diary doesn't exist.\n");
					break;
				}
				destroyDAD(diary);
				diary=NULL;
				printf("The diary deleted.\n");
				break;
			case 3 :
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
			case 4 :
				if (meeting==NULL){
					printf("The meeting doesn't exist.\n");
					break;
				}
				destroy_meet(meeting);
				meeting=NULL;
				printf("The meeting deleted.\n");
				break;
			case 5 :
				if (diary ==NULL){
					printf("The diary doesn't exist.\n");
					break;
				}
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
			case 6 :
				if (diary ==NULL){
					printf("The diary doesn't exist.\n");
					break;
				}
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
			case 7 :
				if (diary ==NULL){
					printf("The diary doesn't exist.\n");
					break;
				}
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
			case 8 :
				if (diary ==NULL){
					printf("The diary doesn't exist.\n");
					break;
				}
				meet_err=printDAD(diary);
				break;
			case 9 :
				return 0;
				break;
						
			default : 
				printf("Wrong choise !\n");
				return 1;;

		}
	}
	return 0;
}

