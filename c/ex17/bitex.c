/*This file contains the bitwise functions.
 *AUTHOR        : Timoshenko Alexander
 *LAST MODIFIED : 06.12.2017
 */

#include "bitex.h"
#include <stdio.h>

 


void bit_comp(unsigned char c){

	c^=(~(unsigned char)0);
	print_binary(c);
}

void bit_rot(unsigned char c,int n){

	unsigned char c1=c;
	
	if (n>0) {
		n%=CHAR_SIZE;
		c>>=n;
		c1<<=CHAR_SIZE-n;
		c|=c1;

	}
	if (n<0){
		n*=-1;
		n%=CHAR_SIZE;
		c<<=n;
		c1>>=CHAR_SIZE-n;
		c|=c1;
	}
	print_binary(c);	
}


error_t set_bits(unsigned char *cptr,unsigned int i,unsigned int j,unsigned int value){

	unsigned char c1=~(unsigned char)0,c2=~(unsigned char)0;

	if ((cptr==NULL)||(i>=CHAR_SIZE)||(j>=CHAR_SIZE)||(i>j)){
		return ERROR;
	}

	c1<<=i;
	c2>>=CHAR_SIZE-j-1;

	if (value!=0) {
		(*cptr)|=(c1&c2);
	}else 
		(*cptr)&=(~(c1&c2));

	return OK;
}



void print_binary(const unsigned char num){

	unsigned char mask=((unsigned char)1<<(CHAR_SIZE-1));

	
	while(mask){
		putchar((((mask&num)!=0)?1:0)+'0');
		mask>>=1;
	}
}





