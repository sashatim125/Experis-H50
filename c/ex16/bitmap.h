
/*This file contains the prototypes for bitmap functions.
 *AUTHOR        : Timoshenko Alexander
 *LAST MODIFIED : 05.12.2017
 */
 
#ifndef _BITMAP_H_
#define _BITMAP_H_

typedef enum {
	OK=0,
	ERROR=-1
} error_t;

typedef enum {
	FALSE=0,
	TRUE
} bool_t;

typedef struct bitMAP bitmap_t;
typedef int (*bitfunc_t)(bitmap_t* bm,unsigned int pos);


#define BYTE_SIZE 8


/*Description :This function creates new bitfield structure;
 *Input : nobits - number of bits required.
 *Output: new bitmap structure.
 *Error : NULL for failure for reason .
 */
 bitmap_t* create_bitmap(unsigned int nobits);
 
 /*Description :This function destroys the bitfield structure;
 *Input : bm - bitmap structuire, nobits - number of bits required.
 *Output: nothing.
 *Error : nothing .
 */
 void destroy_bitmap(bitmap_t* bm);
 
 /*Description :This function put the bit #pos ON;
 *Input : bm - bitmap structuire, pos - position.
 *Output: status.
 *Error : inside the status .
 */
 int bitON(bitmap_t* bm,unsigned int pos);
 
 /*Description :This function put the bit #pos OFF;
 *Input : bm - bitmap structuire, pos - position.
 *Output: status.
 *Error : inside the status .
 */
 int bitOFF(bitmap_t* bm,unsigned int pos);
 
 /*Description :This function check of the bit #pos is ON;
 *Input : bm - bitmap structuire, pos - position.
 *Output: is the bit ON (0 for NO , NON0 for YES)
 *Error : 0 if error for any reason.
 */
 int isbitON(bitmap_t* bm,unsigned int pos);
 
 
 /*Description :This function prints the bitmap;
 *Input : bm - bitmap structuire.
 *Output: NO.
 *Error : nothing on NULL pointer error.
 */
 void print_bitmap(bitmap_t *bm);
 

#endif /*_BITMAP_H*/

