/*This file contains the prototype for lotto function.
 *AUTHOR        : Timoshenko Alexander
 *LAST MODIFIED : 04.12.2017
 */
 
#ifndef _LOTTO_H_
#define _LOTTO_H_

typedef enum {
	OK=0,
	WRONG_NAME,
} error_t;


#define LOTTO_NUMS 49
#define GUESS_NUMS 6

/*Description :This function picks rundomly GUSS_NUM of numbers
 *             from LOTTO_NUMES and prints them to a file (in a table);
 *Input : name - name of filefor printing.
 *Output: prints the table and returns the status
 *Error : rellevant error.
 */
 error_t lotto(char const*name);
 
 #endif /*LOTTO_H*/
