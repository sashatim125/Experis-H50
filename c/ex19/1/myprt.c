/*This file contains the my printf function.
 *AUTHOR        : Timoshenko Alexander
 *LAST MODIFIED : 08.12.2017
 */
#include "myprt.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define MAX_STRING_SIZE 1024

int myprintf(const char *form, ...){
 
	va_list args;
	char *perc="%", tc='\0', text[MAX_STRING_SIZE] , *str ;
	int text_pos=0, next;
	
 	if (form==NULL) {
 		return -1;
 	}
 	if (*form==tc) {
 		return 0;
 	}
 	
 	va_start (args,form);

	while(*form!=tc){
		
		/*printing until % or end of string*/
		next=strcspn(form,perc);
		strncpy(text+text_pos,form,next);
		text_pos+=next;
		form+=next;	
		
		/*if not the end*/
 		if (*form==*perc){
 
		 	switch (*++form){
		 		case 'd':
					text_pos+=sprintf(text+text_pos,"%d",va_arg(args,int));
	 				break;
	 			case 'f':
		 			text_pos+=sprintf(text+text_pos,"%f",va_arg(args,double));
		 			break;
		 		case 's':
		 			str=va_arg(args,char*);
		 			strcpy(text+text_pos,str);
		 			text_pos+=strlen(str);
					break;
	 			case '%':
	 				*(text+text_pos++)='%';
	 				break;
		 		default :
		 			return -1;
					break;
	 		}
	 		++form;	
 		}
 	}
 	text[text_pos]=tc;
 	
 	va_end(args);
 
	fputs(text,stdout);
	return text_pos;
}
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
