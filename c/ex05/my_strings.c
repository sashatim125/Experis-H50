
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

	size_t i,j,mid,length;

	CHECK_NULL(str)
	length = strlen(str);
	
	mid = length/2;
	for (i=0 , j=length-1 ; i<mid ; i++ , j--){
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
	
	if (num == 0) {
		putchar('0');
		return;
	}	
	for (i=get_digits(num,2) ; i>0 ; i--) {
		pow_of_two = my_pow(2,(i-1));
		digit = num/pow_of_two;
		putchar((char)digit+'0');
		num%=pow_of_two;
	}
}

int my_atoi(char* str){

	int res = 0 , sign = 1 ;
	size_t i , length;
	
	if (str == NULL) {
		return 0;
	}
	if ((length = strlen(str)) == 0) {
		return 0;
	}
	i=0;
	while (isspace(str[i]) && i<length) {
		i++;
	}
	if (i == length || (!isdigit(str[i]) && str[i] != '+' && str[i] != '-')) {
		return 0;
	}
	switch (str[i]) {
	
	case '+' :
		i++;
		break;
	case '-' : 
		sign=-1;
		i++;
		break;		  
	}
	if ((i == length) || !isdigit(str[i])) {
		return 0;
	}
	for (; isdigit(str[i]) && i<length; i++){
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
	if (num == 0) {
		strcpy(buffer,"0");
		return buffer;
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

	size_t i ,j , length1 , length2;
	char temp;

	if ((s1==NULL) || (s2==NULL) ) {
		return NULL ;
	}
	length1 = strlen(s1);
	length2 = strlen(s2);
	if (length2 == 0 || length2>length1){
		return NULL;
	}
	
	for (i=0 ; i<=length1-length2 ; i++){
		j=i+length2;
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
	}/*error*/
	
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



