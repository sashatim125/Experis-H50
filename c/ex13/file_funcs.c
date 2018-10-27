/*This file contains API for some file using function.
 *AUTHOR        : Timoshenko Alexander
 *LAST MODIFIED : 03.12.2017
 */
 
#include "file_funcs.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_FILE_NAME_SIZE 50
#define ENG_LETTERS 26

typedef struct bst_node {
	char word[MAX_STRING_SIZE];
	int counter;
	struct bst_node *left, *right;
} bst_node ;

error_t add_word(bst_node **words_bst, char *next);

/*file name check*/
error_t file_r_open(char*, FILE**);

/*empty file check*/
error_t empty_file_check(FILE*);

/*word counter*/
int word_counter(FILE* ,char*); 

/*parsing the words tree*/
error_t parse(bst_node *words_bst);
 

/*Description :This function compairs the strings (of maximum size MAX_STRING_SIZE)
 *             in files name1 and name2
 *             and prints the different strings
 *Input : name1 , name2 - names of files to be compaired.
 *Output: prints different strings and returns the status
 *Error : rellevant error.
 */
error_t diff_strings(char* name1, char* name2){

	FILE *file1, *file2;
	error_t stat;
	char buff1[MAX_STRING_SIZE+1], buff2[MAX_STRING_SIZE+1];
	int i=1;

	/*params checking*/
	if ((stat=file_r_open(name1,&file1))!=OK){
		return stat;
	}
	if ((stat=file_r_open(name2,&file2))!=OK){
		fclose(file1);
		return stat;
	}
	if ((stat=empty_file_check(file1))!=OK){
		fclose(file1);
		fclose(file2);
		return stat;
	}
	if ((stat=empty_file_check(file2))!=OK){
		fclose(file1);
		fclose(file2);
		return stat;
	}
	/*reading strings one by one and compairing*/
	while (fgets(buff1,MAX_STRING_SIZE,file1)!=NULL && fgets(buff2,MAX_STRING_SIZE,file2)!=NULL){
		if (strcmp(buff1,buff2)!=0){
			printf("String %d from file %s is:%s\nand from file %s is:%s\n",i,name1,buff1,name2,buff2);
		}
		++i;
	}
	fclose(file1);
	fclose(file2);
	return OK;
}

/*Description :This function accepts the name of file which contains pairs of "file_name word"
 *             and counts the number of the "word" if appropriate "file".
 *Input : name - name of the file that contains pairs.
 *Output: prints the results of counting and returns the status.
 *Error : rellevant error.
 */
error_t file_word_count(char *name){

	FILE *file,*next_file;
	error_t stat;
	char buff[MAX_STRING_SIZE+1], file_name[MAX_FILE_NAME_SIZE+1], word[MAX_STRING_SIZE-MAX_FILE_NAME_SIZE+1];

	/*params checking*/
	if ((stat=file_r_open(name,&file))!=OK){
		return stat;
	}
	if ((stat=empty_file_check(file))!=OK){
		fclose(file);
		return stat;
	}
	/*parsing the file*/
	while (fgets(buff,MAX_STRING_SIZE,file)!=NULL){
		/*read new string*/
		if (sscanf(buff,"%s %s",file_name,word)!=2){
			fclose(file);
			return BAD_FILE;
		}
		/*empty word*/
		if (strlen(word)==0){
			continue;
		}
		/*open file*/
		if ((stat=file_r_open(file_name,&next_file))!=OK){
			fclose(file);
			return stat;
		}
		
		/*count the word in the file*/
		printf("In the file %s the word %s occurs %5d times.\n",
		       file_name,word,word_counter(next_file,word));
		fclose(next_file);
	}
	
	fclose(file);
	return OK;
}

/*Description :This function accepts the name of file
 *             and counts the frequency of each alphabet character in that file.
 *Input : name - name of the files.
 *Output: prints the results of counting and returns the status.
 *Error : rellevant error.
 */
error_t char_count(char *name){

	FILE *file;
	error_t stat;
	int lower[ENG_LETTERS]={0} ,upper[ENG_LETTERS]={0};
	int next, i;

	/*params checking*/
	if ((stat=file_r_open(name,&file))!=OK){
		return stat;
	}
	/*characters counting*/
	while((next=fgetc(file))!=EOF){
		if(islower(next)){
			++lower[next-'a'];
		}else if(isupper(next)){
			++upper[next-'A'];
		}
	}
	/*printing counters*/
	for(i=0 ; i<ENG_LETTERS ; ++i){
		if(lower[i]!=0){
			printf("The character %c occurs %3d times in file %s.\n",i+'a',lower[i],name);
		}
		if(upper[i]!=0){
			printf("The character %c occurs %3d times in file %s.\n",i+'A',upper[i],name);
		}
	}
	fclose(file);
	return OK;
}

/*Description :This function accepts the name of file
 *             and counts the frequency of each word in that file.
 *Input : name - name of the files.
 *Output: prints the results of counting and returns the status.
 *Error : rellevant error.
 */
error_t word_count(char *name){

	FILE *file;
	error_t stat;
	char next[MAX_STRING_SIZE];
	bst_node *words_bst=NULL;

	/*params checking*/
	if ((stat=file_r_open(name,&file))!=OK){
		return stat;
	}
	/*parsing the file*/
	while(fscanf(file,"%s",next)!=EOF){
		add_word(&words_bst,next);
	}
	/*printing counters*/
	printf("In the file %s :\n",name);
	parse(words_bst);

	fclose(file);
	return OK;
}


error_t file_r_open(char*name, FILE **file){

	if ((*file=fopen(name,"r"))==NULL){
		return WRONG_NAME;
	}
	return OK;
}

error_t empty_file_check(FILE* file){
	fseek(file,0,SEEK_END);
	if (ftell(file)==0) {
		return EMPTY_FILE_ERROR;
	}
	fseek(file,0,SEEK_SET);
	return OK;
}

int word_counter(FILE *file ,char *word){

	int count=0;
	char buff[MAX_STRING_SIZE+1],*next;
	size_t len=strlen(word);
	
	while (fscanf(file,"%s",buff)!=EOF){
		next=buff;
		while ((next=strstr(next,word))!=NULL){
			++count;
			next+=len;
		}
	}
	return count;
}
 
error_t add_word(bst_node **words_bst, char *next){

	int res;

	if (*words_bst==NULL){
		*words_bst=/*(*bst_node)*/malloc(sizeof(bst_node));
		if (*words_bst==NULL){
			return ALLOC_ERROR;
		}
		strcpy((*words_bst)->word,next);
		(*words_bst)->counter=1;
		(*words_bst)->left=(*words_bst)->right=NULL;
		return OK;
	}
	res=strcmp((*words_bst)->word,next);
	if (res==0){
		++((*words_bst)->counter);
	}else if (res>0){
		add_word(&((*words_bst)->left),next);
	}else add_word(&((*words_bst)->right),next);
	
	return OK;
}

error_t parse(bst_node *words_bst){

	if (words_bst==NULL){
		return OK;
	}
	parse(words_bst->left);
	printf("The word %s occures %d times.\n",words_bst->word,words_bst->counter);
	parse(words_bst->right);
	return OK;
}
















 
