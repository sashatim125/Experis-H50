
#include <stdio.h>
#include <stdlib.h>

typedef enum {
	OK=0,
	WRONG_NAME,
	WRONG_N,
	OPEN_FILE_ERROR,
	EMPTY_FILE_ERROR
} error_t;

#define MAX_STRING_SIZE 512


static int my_tail(char* name , size_t n);
static long get_last_n_pos(FILE *file,int n);
static void print_from_pos(FILE *file,long pos);

int main(int argc, char *argv[]){

	size_t num;
	error_t stat;
	
	if (argc!=3){
		fprintf(stderr,"Wrong number of parameters.\n");
		exit(EXIT_FAILURE);
	}
	if (((num=atoi(argv[2]))==0)||(num<=0)) {
		fprintf(stderr,"Wrong number.\n");
		exit(EXIT_FAILURE);
	}
	
	stat=my_tail(argv[1],num);
	switch (stat) {
		case WRONG_NAME :
			fprintf(stderr,"Wrong name.\n");
			exit(EXIT_FAILURE);
			break;
		case WRONG_N :
			fprintf(stderr,"Wrong number.\n");
			exit(EXIT_FAILURE);
			break;
		case OPEN_FILE_ERROR :
			fprintf(stderr,"Error opening the file.\n");
			exit(EXIT_FAILURE);
			break;
		case EMPTY_FILE_ERROR :
			fprintf(stderr,"The file is empty.\n");
			exit(EXIT_FAILURE);
			break;
	}
	
	exit(EXIT_SUCCESS);
}

int my_tail(char* name , size_t n){

	FILE* file;
	long pos;
	
	/*checking params*/
	if (name==NULL){
		return WRONG_NAME;
	}
	if (n==0) {
		return WRONG_N;
	}
	/*and opening the file*/
	if((file=fopen(name,"r"))==NULL){
		return OPEN_FILE_ERROR;
	}
	
	if ((pos=get_last_n_pos(file,n))==-1L){
		return EMPTY_FILE_ERROR;
	}
	print_from_pos(file,pos);
	
	fclose(file);
	return OK;	
}

static long get_last_n_pos(FILE *file,int n){

	long *positions, res;
	int count=0;
	char buff[MAX_STRING_SIZE];
	
	n+=1L;
	
	if ((positions=(long*)malloc(n*sizeof(long)))==NULL){
		return -1L;
	}
	
	fseek(file,0,SEEK_SET);
	do{
		positions[(count)%n]=ftell(file);
		++count;
		fgets(buff,MAX_STRING_SIZE,file);
	}while(!feof(file));
	if (count>=n){
		count=(count)%n;;
	}else count=0;
	res=positions[count];
	
	free(positions);
	return res;
}

static void print_from_pos(FILE *file,long pos){

	char buff[MAX_STRING_SIZE];
	
	fseek(file,pos,SEEK_SET);
	
	fgets(buff,MAX_STRING_SIZE,file);
	while(!feof(file)){
		fputs(buff,stdout);
		fgets(buff,MAX_STRING_SIZE,file);
	}
}
















