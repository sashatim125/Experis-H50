
/*This file contains the prototypes for bitwise functions.
 *AUTHOR        : Timoshenko Alexander
 *LAST MODIFIED : 06.12.2017
 */
 
#ifndef _BITEX_H_
#define _BITEX_H_

typedef enum {
	OK=0,
	ERROR=-1
} error_t;


#define CHAR_SIZE 8 /*8 bint in char*/

 
 /*Description :This function makes bitwise complementation on input;
 *Input : c - char;
 *Output: prints the bitwise complementation of char;
 *Error : NONE.
 */
 void bit_comp(unsigned char c);

 /*Description :This function make the bitwise rotation(left or right);
 *Input : c - char , n - number of rotations (positive=right, negative=left);
 *Output: prints the result;
 *Error : NONE.
 */
 void bit_rot(unsigned char c,int n); 
 
 /*Description :This function sets in c bits from i to j by value;
 *Input : c - (pointer to) char , i to j - numbers, value - 0 for 0 , non0 for 1.
 *Output: modifies c and return status ;
 *Error : wrong parameters return ERROR.
 */
 error_t set_bits(unsigned char *c,unsigned int i,unsigned int j,unsigned int value); 
 
 /*Description :This function prints num in binary;
 *Input : num - binary number.
 *Output: as in description ;
 *Error : NONE.
 */
 void print_binary(const unsigned char num);

#endif /*_BITEX_H*/

