/*This file contains the prototype for lotto function.
 *AUTHOR        : Timoshenko Alexander
 *LAST MODIFIED : 04.12.2017
 */

/*Description :This function picks rundomly GUSS_NUM of numbers
 *             from LOTTO_NUMES and prints them to a file (in a table);
 *Input : name - name of filefor printing.
 *Output: prints the table and returns the status
 *Error : rellevant error.
 */

#include "lotto.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TEN 10
#define FOUR 4


/*opening the file*/ 
static error_t file_w_open(char const*name, FILE **file);

/*making the guess*/
static void make_guess(int *nums);

/*printing the table*/
static void print_table(FILE *file, int *nums); 

/*search number*/
static int search(int* arr,int size, int num);


 
error_t lotto(char const*name){
 
 	int nums[GUESS_NUMS];
 	error_t stat;
 	FILE *file;
 	
 	/*params checking*/
	if ((stat=file_w_open(name,&file))!=OK){
		return stat;
	}
	
	/*make guess*/
	make_guess(nums);
	
	/*printing the table*/
	print_table(file,nums); 
 
 	fclose(file);
 	return OK;
 }
 
error_t file_w_open(char const*name, FILE **file){

	if ((*file=fopen(name,"w"))==NULL){
		return WRONG_NAME;
	}
	return OK;
}

int search(int* arr,int size, int num){

	int j;
	for (j=0 ; j<size ; j++){
		if (arr[j]==num){
			return j;
			break;
		}
	}
	return -1;
}

void make_guess(int *nums){

	int i,next;
	
	srand(time(NULL));
	
	for(i=0 ; i<GUESS_NUMS ; ++i){
		next=rand()%LOTTO_NUMS+1;
		if (search(nums,i-1,next)>=0){
			--i;
			continue;
		}
		nums[i]=next;
	}
}

void print_table(FILE *file, int *nums){

	int i,j;
	
	/*first_line*/
	fprintf(file,"   ");
	for (i=1 ; i<=TEN ; ++i){
		fprintf(file,"%2d ",i);
	}
	fprintf(file,"\n");
	
	for (i=0 ; i<=FOUR ; ++i){
		fprintf(file,"%2d ",i);
		for (j=1 ; j<=TEN ; ++j){
			fprintf(file,"%2c ",(search(nums,GUESS_NUMS,i*TEN+j)>=0)?'+':'-');
		}
		fprintf(file,"%c",'\n');
	}
	fseek(file,-4,SEEK_END);
	fprintf(file,"    ");
}




