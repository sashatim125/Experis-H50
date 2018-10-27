/*This file contains the API for simple calculator.
 *AUTHOR        : Timoshenko Alexander
 *LAST MODIFIED : 12.12.2017
 */
 
#ifndef __CALC_H__
#define __CALC_H__

#include "../ADTErr.h"

 
/*Description :converts the Infix arithmetic notation to Postfix;
 *Params :_ifString - Infix string , _pfString - Postfix string;
 *Return: status;
 *Error : ERR_OK,ERR_GENERAL,ERR_NOT_INITIALIZED.
 */
ADTErr InfixToPostFix(char *_ifString, char *_pfString);

/*Description :calculate the Postfix expression;
 *Params :_pfString - Postfix string, _res - result;
 *Return: status;
 *Error : ERR_OK,ERR_GENERAL,ERR_NOT_INITIALIZED.
 */
ADTErr MyCalc(char *_pfString, int *_res);

#endif/*__CALC_H__*/

