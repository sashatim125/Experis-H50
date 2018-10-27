/*This file contains the prototype for my printf function.
 *AUTHOR        : Timoshenko Alexander
 *LAST MODIFIED : 09.12.2017
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
 
 /*Description :small printf-like function with parameters of :
  *             %s-string, %d - integer, %f - double and %% - just prints %.
  *Input : same as printf with only parameter as described above;
  *Output: number of character printed;
  *Error : negative output for error.
  */
 int myprintf2(const char *format, ...);
 
 /*Description :turns inetger to string (ASCII);
  *Input : buff - buffer for output the sting, num - integer number;
  *Output: number of charactes has been put to the buffer;
  *Error : <0 if error.
  */
 int myitoa(char *buff, int num);
 
 
 
 #endif
