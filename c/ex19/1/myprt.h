/*This file contains the prototype for my printf function.
 *AUTHOR        : Timoshenko Alexander
 *LAST MODIFIED : 08.12.2017
 */
 
#ifndef _MYPRT_H_
#define _MYPRT_H_

 
 /*Description :small printf-like function with parameters of :
  *             %s-string, %d - integer, %f - double and %% - just prints %.
  *Input : same as printf with only parameter as described above;
  *Output: number of character printed;
  *Error : negative output for error.
  */
 int myprintf(const char *format, ...);
 #endif
