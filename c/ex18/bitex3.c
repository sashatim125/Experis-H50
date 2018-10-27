
/*This file contains the bitwise functions.
 *AUTHOR        : Timoshenko Alexander
 *LAST MODIFIED : 06.12.2017
 */

#include "bitex.h"
#include "bitex3.h"
#include <stdio.h>

struct half_char{
	unsigned int ms :4;
	unsigned int ls :4;
};

typedef union {
	char c;
	struct half_char hc;
} my_char;

error_t compress_str1(char *s){

 	int i,j;
 	unsigned char mask=0xF;
	
 	if ((s==NULL)||(*s=='\0')){
 		return ERROR;
 	}
 	for (i=0,j=0;(s[i]!='\0')&&(s[i+1]!='\0');i+=2,++j){

 		s[j]=(s[i]<<4)|((s[i+1])&mask);
 	}
 	if(s[i+1]=='\0'){

 		s[j]=(s[i]<<4);
 	}
	
 	return OK;
 }

 
 error_t compress_str2(char *s){

 	int i,j;
 	my_char next;
 	
 	if ((s==NULL)||(*s=='\0')){
 		return ERROR;
 	}
 	for (i=0,j=0;(s[i]!='\0')&&(s[i+1]!='\0');i+=2,++j){
 		next.hc.ls=s[i];
 		next.hc.ms=s[i+1];
 		s[j]=next.c;
 	}
 	if(s[i+1]=='\0'){
 		next.hc.ls=s[i];
 		next.hc.ms=0;
 		s[j]=next.c;
 	}
 	
 	return OK;
 }
 
 
 
 
 error_t my_setbits(unsigned char *x, unsigned int p, unsigned int n,unsigned char y){
 
 	unsigned char mask=~((~0)<<n);

 
 	if ((p>CHAR_SIZE)||(n>CHAR_SIZE)){
 		return ERROR;
 	}
 	
 	y&=mask;
 	y<<=(p-n);
 	mask<<=(p-n);
 	(*x)&=~mask;
 	(*x)|=y;

 	return OK;
 }
 
 
 
 
 
 
 
