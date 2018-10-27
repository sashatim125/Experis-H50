/*This file contains the errors definitions for data structure.
 *AUTHOR        : Timoshenko Alexander
 *LAST MODIFIED : 11.12.2017
 */
 
#ifndef __ADTERROR_H__
#define __ADTERROR_H__

/*Definition of the various errors*/
typedef enum
{
    /* General ADT Errors */
    ERR_OK = 0,
    ERR_GENERAL,
    ERR_NOT_INITIALIZED,
    ERR_ALLOCATION_FAILED,
    ERR_REALLOCATION_FAILED,
    ERR_UNDERFLOW,
    ERR_OVERFLOW,
    ERR_WRONG_INDEX,
    ERR_DATA_DUPLICATION,
    ERR_ALREADY_EXISTS,
    ERR_NOT_FOUND
} ADTErr;

#endif/*__ADTERROR_H__*/
