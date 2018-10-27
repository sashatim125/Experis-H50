
#ifndef __CONF_FILE_PARSER_H__
#define __CONF_FILE_PARSER_H__

/** 
 *  @file confFileParser.h
 *  @brief Configuration file parser(of ini format)
 *	
 *  @warning The functions ARE NOT thread safe
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */
 
#include <stdio.h>


/**  
 * @brief start with a conf file in required section
 * @param[in] _filePtr - preopened file
 * @param[in] _section - the section name
 * @returns 0 on success, !=0 otherwise
 * @warning call one time before parsing the section
 * every call resets the function
 */
int ConfFileParser_GetSection(FILE* _filePtr, const char* _section);

/**  
 * @brief get next var=value pair
 * @param[in] _filePtr - preopened file
 * @param[out] _var - the var
 * @param[out] _value -correspondint to the var
 * @returns 0 on success, !=0 otherwise (like no more pairs)
 * @warning do not call any function working on this file
 */
int ConfFileParser_GetNextPair(FILE* _filePtr, char* _var, char* _value);


#endif /*__CONF_FILE_PARSER_H__*/
