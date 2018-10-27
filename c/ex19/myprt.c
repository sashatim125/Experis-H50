/*This file contains the my printf function.
 *AUTHOR        : Timoshenko Alexander
 *LAST MODIFIED : 07.12.2017
 */
#include "myprt.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define MAX_STRING_SIZE 1024

int myprintf(const char *form, ...){
 
	va_list args;
	char *perc="%", tc='\0', text[MAX_STRING_SIZE]={'\0'} , *str ;
	int text_pos=0, next;
	
 	if (form==NULL) {
 		return -1;
 	}
 	if (*form==tc) {
 		return 0;
 	}
 	
 	va_start (args,form);

	while(*(form)!=tc){		
		
		next=strcspn(form,perc);
		printf("next=%d ",next);
		printf("form=%s ",form);
		strncpy(text+text_pos,form,next);
		text_pos+=next;
		form+=next;
		
		printf("text=%s ",text);
		printf("form=%s ",form);
		
		
 		if (*form==*perc){
 	
 			++form;
		 	switch (*form){
		 		case 'd':
					text_pos+=sprintf(text+text_pos,"%d%c",va_arg(args,int),tc);
	 				break;
	 			case 'f':
		 			text_pos+=sprintf(text+text_pos,"%f%c",va_arg(args,double),tc);
		 			break;
		 		case 's':
		 			str=va_arg(args,char*);
		 			printf("string arg=%s \n",str);
		 			strcpy(text+text_pos,str);
		 			text_pos+=strlen(str);
					break;
	 			case '%':
	 				*text='%';
		 			*(text+1)='\0';
		 			text_pos+=2;
		 		default :
		 			return -2;
					break;
	 		}
	 		++form;
	 		
 		}else text[text_pos]=tc;
 		
 		putchar('\n');
 		getchar();
 	}
 	
 	va_end(args);
 
	fputs(text,stdout);
	return text_pos;
}
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
