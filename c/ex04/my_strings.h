
/*This file contains 6 function working on strings*/


#define OK 10
#define NULL_POINTER_ERROR 11

#define TRUE 1
#define FALSE 0


/*Description :This function reverses the string "str" order.
 *Input : string "str"
 *Output: reversed string in place of "str".
 *Error : OK of appropriate error code.
 */
int rev_str(char* str);

/*Description :This function checks if the string "str" is palyndrome.
 *Input : string "str"
 *Output: reversed string in place of "str".
 *Error : OK of appropriate error code.
 */
int is_palyndrome(char* str);


/*Description :This function prints the number "num" in binary format.
 *Input : non negative integer num
 *Output: prints the number in binary format to stdout
 *Error : ---.
 */
void print_binary(unsigned int num);

/*Description :This function returns number in the string.
 *Input : integer number as a sting.
 *Output: the number as integer
 *Error : 0 is error;
 */
int my_atoi(char* str);

/*Description :This function returns the string representation of number.
 *Input : integer number.
 *Output: string representation of the number
 *Error : NULL is error;
 */
char *my_itoa(int , char*);

/*Description :This function finds first occurence of s2 in s1.
 *Input : 2 strings.
 *Output: pointer to the first occurence of s1 in s2
 *Error : NULL is error;
 */
char *my_strstr(char* , char*);








