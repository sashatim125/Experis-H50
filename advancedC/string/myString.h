
#ifndef __STRING_H__
#define __STRING_H__


#include "vector.h"
#include <stdio.h> /*???*/
#include <stdlib.h>


/** 
 *  @file myString.h
 *  @brief API for various string functions
 *	
 *  @details  See the functions description
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 *  @bug NONE! 
 */


/** 
 * @brief string copy function (iterative)
 * @param[in] _str1 - destination
 * @param[in] _str2 - source
 * @return destination
 */
char* StrCpyIt(char *_str1, const char *_str2);


/** 
 * @brief string copy function (recursive)
 * @param[in] _str1 - destination
 * @param[in] _str2 - source
 * @return destination
 */
char* StrCpyRec(char *_str1, const char *_str2);

/** 
 * @brief string copy function at most n characters (iterative)
 * @param[in] _str1 - destination
 * @param[in] _str2 - source
 * @return destination
 */
char* StrNCpyIt(char *_str1, size_t _n, const char *_str2);


/** 
 * @brief string copy function at most n characters(recursive)
 * @param[in] _str1 - destination
 * @param[in] _str2 - source
 * @return destination
 */
char* StrNCpyRec(char *_str1, size_t _n, const char *_str2);

/** 
 * @brief string copy function (iterative)
 * @param[in] _str1 - string to compare
 * @param[in] _str2 - string to compare
 * @return comparison result (>0 if _str1 > _str2 ; =0 if _str1 == _str2, <0 otherwise)
 */
int StrCmpIt(const char *_str1, const char *_str2);


/** 
 * @brief string copy function (recursive)
 * @param[in] _str1 - string to compare
 * @param[in] _str2 - string to compare
 * @return comparison result (>0 if _str1 > _str2 ; =0 if _str1 == _str2, <0 otherwise)
 */
int StrCmpRec(const char *_str1, const char *_str2);


/** 
 * @brief string concatenation function
 * @param[in] _str1 - destination (to concatenate to)
 * @param[in] _str2 - source
 * @return destination
 */
char* StrCat(char *_str1, const char *_str2);


/** 
 * @brief search the string _str2 in _str1
 * @param[in] _str1 - string where to look for
 * @param[in] _str2 - the string to search
 * @return first occurence of _str2 in _str1 or NULL of not
 */
char* StrStr(const char *_str1, const char *_str2);

/** 
 * @brief fins the length of string
 * @param[in] _str - string
 * @return length of _str;
 */
size_t myStrLen(const char *_str);



#endif /*__STRING_H__*/


