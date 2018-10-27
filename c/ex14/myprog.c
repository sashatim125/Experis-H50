
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>

typedef enum {FALSE=0,TRUE=1} bool_t;

void print_err(void);

bool_t is_leg_name(char*);
bool_t is_leg_num(char*);


int main(int argc,char*argv[]){

	int age;
	char *name;

	if (argc != 3){
		print_err();
		return 1;
	}
	if (is_leg_name(argv[1])&&is_leg_num(argv[2])){
		name=argv[1];
		age=atoi(argv[2]);
	}
	else if (is_leg_name(argv[2])&&is_leg_num(argv[1])) {
		name=argv[2];
		age=atoi(argv[1]);
		}
	else {
		print_err();
		return 1;
	}
	printf("%s is of age %d.\n",name,age);
	
	return 0;
}

void print_err(void){
	fprintf(stderr,"\nParameters error\n");
}

bool_t is_leg_name(char* str){

	size_t i;

	if (str[0]=='\0'){
		return FALSE;
	}
	if (!isupper(str[0])){
		return FALSE;
	}
	i=1;
	while(str[i]!='\0'){
		if (!islower(str[i])){
			return FALSE;
		}
		++i;
	}
	return TRUE;
}

bool_t is_leg_num(char* str){

	size_t i;

	if (str[0]=='\0'){
		return FALSE;
	}
	i=0;
	while(str[i]!='\0'){
		if (!isdigit(str[i])){
			return FALSE;
		}
		++i;
	}
	return TRUE;
}



