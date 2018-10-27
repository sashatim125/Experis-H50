/*This file contains the bitmap functions.
 *AUTHOR        : Timoshenko Alexander
 *LAST MODIFIED : 05.12.2017
 */
 
#include "bitmap.h"
#include <stdlib.h>
#include <stdio.h>

struct bitMAP{
 	/*array of uints = the bitfield*/
 	unsigned int *map;
 	/*number of bits used*/
 	unsigned int nobits;
 	/*number of blocks(uints) used*/
 	unsigned int noblocks;
};

typedef enum {
	ON,
	OFF,
	ISON
} oper_t;

static int bit_oper(bitmap_t* bm,unsigned int pos, oper_t op);
static error_t checkptr(void *ptr);
static error_t poscheck(bitmap_t* bm,unsigned int pos);
static void print_binary(unsigned int num);
 
 
bitmap_t* create_bitmap(unsigned int nobits){
 
	bitmap_t *newbm;
 	size_t map_size/*blocks*/,block_size/*bits*/;
 	
 	if ((newbm=(bitmap_t*)malloc(sizeof(bitmap_t)))==NULL){
 		return NULL;
 	}
 	
 	block_size=(sizeof(unsigned int)*BYTE_SIZE);
 	map_size=nobits/block_size + ((nobits%block_size>0)?1:0);
 	
 	if ((newbm->map=(unsigned int*)calloc(map_size,sizeof(unsigned int)))==NULL){
 		free(newbm);
 		return NULL;
 	}
 	newbm->nobits=nobits;
 	newbm->noblocks=map_size;
 	return newbm; 
}
 
void destroy_bitmap(bitmap_t* bm){

	if (bm==NULL){
		return;
	}
	free(bm->map);
	free(bm);
}

int bitON(bitmap_t* bm,unsigned int pos){

	return bit_oper(bm,pos,ON);
}

int bitOFF(bitmap_t* bm,unsigned int pos){

	return bit_oper(bm,pos,OFF);
}

int isbitON(bitmap_t* bm,unsigned int pos){

	return bit_oper(bm,pos,ISON);
}

error_t checkptr(void *ptr){

	if (ptr==NULL){
		return ERROR;
	}else return OK;
}
error_t poscheck(bitmap_t* bm,unsigned int pos){

	if (pos > bm->nobits) {
		return ERROR;
	}
	return OK;
}

int bit_oper(bitmap_t* bm,unsigned int pos, oper_t op){

	int block_num , offset/*from the begining*/;
	size_t block_size/*bits*/;
	unsigned int mask=1u;

	if (checkptr((void*)bm)!=OK) {
		return ERROR;
	}
	if (poscheck(bm,pos)!=OK){
		return ERROR;
	}
	block_size=(sizeof(unsigned int)*BYTE_SIZE);

	offset=pos/block_size;
	pos%=block_size;/*relative*/
	
	switch (op){
		case ON :
			mask<<=pos;
			(bm->map[offset])|=mask;	
			return OK;		
			break;
		case OFF :
			mask<<=pos;
			mask=~mask;
			(bm->map[offset])&=mask;
			return OK;
			break;
		case ISON :
			mask<<=pos;
			mask&=(bm->map[offset]);
			return (mask!=0)?TRUE:FALSE;
			break;
	}
}

void print_binary(unsigned int num){
	
	size_t block_size=(sizeof(unsigned int)*BYTE_SIZE);
	unsigned int mask=(1U<<(block_size-1));
	int i;
	
	for (i=block_size-1 ; i>=0 ; --i){
		putchar((((mask&num)!=0)?1:0)+'0');
		mask>>=1;
	}
}


void print_bitmap(bitmap_t *bm){

	int i;

	if (bm==NULL){
		return;
	}
	
	for(i=bm->noblocks-1 ; i>=0 ; --i){
		print_binary((bm->map)[i]);
		putchar(' ');
	}
	putchar('\n');
}


