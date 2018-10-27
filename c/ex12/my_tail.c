
#include <stdio.h>
#include <stdlib.h>

typedef enum {
	OK=0,
	WRONG_NAME,
	WRONG_N,
	OPEN_FILE_ERROR,
	EMPTY_FILE_ERROR
} error_t;


int my_tail(char* name , size_t n);

int main(int argc, char *argv[]){

	size_t num=atoi(argv[2]);
	error_t status;
	
	if (argc!=3){
		fprintf(stderr,"Wrong number of parameters.\n");
		exit(EXIT_FAILURE);
	}
	
	status=my_tail(argv[1],num);
	switch (status) {
		case WRONG_NAME :
			fprintf(stderr,"Wrong name.\n");
			break;
		case WRONG_N :
			fprintf(stderr,"Wrong number.\n");
			break;
		case OPEN_FILE_ERROR :
			fprintf(stderr,"Error opening the file.\n");
			break;
		case EMPTY_FILE_ERROR :
			fprintf(stderr,"The file is empty.\n");
			break;
	}
	
	exit(EXIT_SUCCESS);
}

int my_tail(char* name , size_t n){

	FILE* file;
	size_t i=0;
	int next;
	
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
	/*is the file empty?*/
	fseek(file,0,SEEK_SET);
	if(ftell(file)==EOF){
		fclose(file);
		return EMPTY_FILE_ERROR;
	}
	/*going back*/
	fseek(file,0,SEEK_END);
	while(i<n){
		while ((ftell(file)>0)&&(fgetc(file)!='\n')){
			fseek(file,-2,SEEK_CUR);
		}
		++i;
		/*begining of file*/
		if (ftell(file)<=0){
			break;
		}
		/*last char was '\n'*/
		fseek(file,-2,SEEK_CUR);
	}
	if (ftell(file)!=0){
		fseek(file,2,SEEK_CUR);
	}
	/*printing the n lines	*/
	while (!feof(file)){
		if ((next=getc(file))!=EOF){
			fputc(next,stdout);
		}
	}
	
	fclose(file);
	return OK;	
}

