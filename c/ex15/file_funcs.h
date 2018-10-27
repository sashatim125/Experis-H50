/*This file contains API for some file using function.
 *AUTHOR        : Timoshenko Alexander
 *LAST MODIFIED : 04.12.2017
 */
 
#ifndef _FILE_FUNCS_H_
#define _FILE_FUNCS_H_

typedef enum {
	OK=0,
	WRONG_NAME,
	OPEN_FILE_ERROR,
	EMPTY_FILE_ERROR,
	BAD_FILE,
	ALLOC_ERROR
} error_t;


#define MAX_STRING_SIZE 512

/*Description :This function compairs the strings (of maximum size MAX_STRING_SIZE)
 *             in files name1 and name2
 *             and prints the different strings
 *Input : name1 , name2 - names of files to be compaired.
 *Output: prints different strings and returns the status
 *Error : rellevant error.
 */
error_t diff_strings(char const* name1, char const* name2);

/*Description :This function accepts the name of file which contains pairs of "file_name word"
 *             and counts the number of the "word" if appropriate "file".
 *Input : name - name of the file that contains pairs.
 *Output: prints the results of counting and returns the status.
 *Error : rellevant error.
 */
error_t file_word_count(char const*name);

/*Description :This function accepts the name of file
 *             and counts the frequency of each alphabet character in that file.
 *Input : name - name of the file.
 *Output: prints the results of counting and returns the status.
 *Error : rellevant error.
 */
error_t char_count(char const*name);

/*Description :This function accepts the name of file
 *             and counts the frequency of each word in that file.
 *Input : name - name of the files.
 *Output: prints the results of counting and returns the status.
 *Error : rellevant error.
 */
error_t word_count(char const*name);

#endif /*_FILE_FUNCS_H_*/
