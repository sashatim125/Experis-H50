
#include "my_strings.h"
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>

#define CHECK_NULL(ptr)\
{\
	if (ptr == NULL) {\
		return NULL_POINTER_ERROR;\
	}\
}

/*swaps 2 chars and return status*/
int char_swap(char* , char*);

/*return number of digits of base "base" of non negative integer number*/
unsigned int get_digits(unsigned int , unsigned int);

/*power function*/
unsigned int my_pow(unsigned int , unsigned int);

int rev_str(char* str){

	size_t i,j,mid;

	CHECK_NULL(str)
	
	mid = strlen(str)/2;
	for (i=0 , j=strlen(str)-1 ; i<mid ; i++ , j--){
		char_swap(str+i,str+j);
	}
	return OK;
}

int is_palyndrome(char* str){

	size_t i,j,mid;
	int res=TRUE;

	CHECK_NULL(str)
	
	mid = strlen(str)/2;
	for (i=0 , j=strlen(str)-1 ; (i<mid) && res ; i++ , j--){
		if (str[i] != str[j]) {
			res=FALSE;
		}	
	}
	return res;
}


void print_binary(unsigned int num){
	
	unsigned int i, digit , pow_of_two;
	
	for (i=get_digits(num,2) ; i>0 ; i--) {
		pow_of_two = my_pow(2,(i-1));
		digit = num/pow_of_two;
		putchar((char)digit+'0');
		num%=pow_of_two;
	}
}

int my_atoi(char* str){

	int res = 0 , sign = 1 ;
	size_t i ;
	char next;
	
	if (str == NULL) {
		return 0;
	}
	i=0;
	while ((next=str[i]) != '+' && next != '-' && !isdigit(next) && i<strlen(str)) {
		i++;
	}
	if (i == strlen(str)) {
		return 0;
	}
	switch (next) {
	
	case '+' :
		i++;
		break;
	case '-' : 
		sign=-1;
		i++;
		break;		  
	}
	if ((i == strlen(str)) || !isdigit(str[i])) {
		return 0;
	}
	for (; isdigit(str[i]) ; i++){
		res=res*10+(str[i]-'0');
	}
	return res*sign;
}

char *my_itoa(int num, char* buffer){

	size_t j=0;
	unsigned int i , pow_of_ten , digit;

	if (buffer == NULL) {
		return NULL;
	}
	
	if (num < 0) {
		buffer[j++] = '-';
		num*=-1;
	}
	
	for (i=get_digits(num,10) ; i>0 ; i--,j++) {
		pow_of_ten = my_pow(10,(i-1));
		digit = num/pow_of_ten;
		buffer[j]=(char)digit+'0';
		num%=pow_of_ten;
	}
	buffer[j] = '\0';
	return buffer;
}

char* my_strstr(char* s1, char* s2){

	size_t i ,j;
	char temp;

	if ((s1==NULL) || (s2==NULL) || strlen(s2)>strlen(s1)) {
		return NULL ;
	}

	for (i=0 ; i<=strlen(s1)-strlen(s2) ; i++){
		j=i+strlen(s2);
		temp = s1[j];
		s1[j]='\0';
		if (strcmp(s1+i,s2) == 0) {
			s1[j]=temp;
			return s1+i;
		}
		s1[j]=temp;
	}
	return NULL;
}


int char_swap(char* ch1, char* ch2){

	char temp;

	CHECK_NULL (ch1)
	CHECK_NULL (ch2)
	
	temp = *ch1;
	*ch1 = *ch2;
	*ch2 = temp;
	
	return OK;
}

unsigned int get_digits(unsigned int num, unsigned int base){

	unsigned int digits = 0 ;
	
	if (base == 0) {
		return 0;
	}
	
	while (num != 0) {
		num/=base;
		digits++;
	}
	return digits;
}

unsigned int my_pow(unsigned int a, unsigned int b){

	unsigned int i,res=1;
	
	for (i=0 ; i<b ; i++) {
		res*=a;
	}
	return res;
}



