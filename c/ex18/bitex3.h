
/*This file contains the prototypes for bitwise functions.
 *AUTHOR        : Timoshenko Alexander
 *LAST MODIFIED : 06.12.2017
 */
 
#ifndef _BITEX3_H_
#define _BITEX3_H_

 
 /*Description :Some language contains only 16 letters:  a b c d e f g h i j k l m n o p.
  *             So it's enough to give only 4 bits for each letter instead of 8 as in ASCII set.
  *             Write a function that receives as a parameter 'C' string and compresses it
  *             in a way that each letter takes only 4 bits ( it means, that in each byte/char will be 2 letters);
  *             !!! without bitfields !!!;
  *Input : s - string of 'a'-'p' ONLY;
  *Output: as described above,IN PLACE;
  *Error : null pointer input error.
  */
 error_t compress_str1(char *s);
 
 /*Description :Some language contains only 16 letters:  a b c d e f g h i j k l m n o p.
  *             So it's enough to give only 4 bits for each letter instead of 8 as in ASCII set.
  *             Write a function that receives as a parameter 'C' string and compresses it
  *             in a way that each letter takes only 4 bits ( it means, that in each byte/char will be 2 letters);
  *             !!! with bitfields !!!;
  *Input : s - string of 'a'-'p' ONLY;
  *Output: as described above,IN PLACE;
  *Error : null pointer input error.
  */
 error_t compress_str2(char *s);
 
 
 /*Description :This function setbits(x,p,n,y) that returns x with the n bits 
 *              that begin at position p set to the rightmost n bits of an unsigned char variable y
 *              (leaving other bits unchangedmakes bitwise complementation on input;
 *Input : as described above;
 *Output: as described above;
 *Error : ERROR for wrong parameters(like n>8).
 */
 error_t my_setbits(unsigned char *x, unsigned int p, unsigned int n,unsigned char y);


#endif /*_BITEX3_H*/

