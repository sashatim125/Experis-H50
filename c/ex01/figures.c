/*Description :
 *This file conteins 6 functions that print
 *geometric figures (triangles)
 *of chars "ch" and of size "size";
 *
 *Input :
 *"ch" should be printable and
 *"size" should be MIN_SIZE..MAX_SIZE
 *
 *Return :
 *They return the status value defined below.
 */

#include "figures.h"
#include <stdio.h>
#include <ctype.h>

/*Paraments checking function :
 *return status as defined in figures.h.
 */
int check_params(char ch , int size);
/*Printing string "s" n times,
 *assuming "n"=MIN_SIZE..MAX_SIZE and "s" is printable.
 */
void printnstring (char* s, int n);

/*Parments checking by check_params function.*/
#define PARAMS_CHECK(ch,size) \
{\
	int res;\
	if ((res=check_params(ch,size))!=OK) {\
		return res;\
	}\
}

/*This function prints the following type of triangle :
 *  +
 *  ++
 *  +++
 */
int print_triangle (char ch, int size){

	int i;
	char s[2]={ch,'\0'};

	PARAMS_CHECK(ch,size)

	for (i=1 ; i<=size ; i++){
		printnstring(s,i);
		putchar('\n');
	}

	return OK;
}

/*This function prints the following type of triangle :
 *  +++
 *  ++
 *  +
 */
int print_down_triangle (char ch, int size){

	int i;
	char s[2]={ch,'\0'};

	PARAMS_CHECK(ch,size)

	for (i=size ; i>0 ; i--){
		printnstring(s,i);
		putchar('\n');
	}

	return OK;
}

/*This function prints the following type of triangle :
 *  +
 *  ++
 *  +++
 *  ++
 *  +
 */
int print_arrow_triangle (char ch, int size){

	int res;
	if ((res=print_triangle(ch,size))!=OK) {
		return res; 
	}
	if (check_params(ch,size-1)==OK) {
		print_down_triangle(ch,size-1);
	}
	return OK;

}

/*This function prints the following type of triangle :
 *    +
 *   + +
 *  + + +
 */
int print_pyramid_triangle (char ch, int size){

	int i;
	char s1[2]={' ','\0'} , s2[3]={ch,' ','\0'};

	PARAMS_CHECK(ch,size)

	for (i=1 ; i<=size ; i++) {
		printnstring(s1,size-i);
		printnstring(s2,i);
		putchar('\n');	
	}
	return OK;
}

/*This function prints the following type of triangle :
 *  + + +
 *   + +
 *    +
 */
int print_rev_piramid_triangle (char ch, int size){

	int i;
	char s1[2]={' ','\0'} , s2[3]={ch,' ','\0'};

	PARAMS_CHECK(ch,size)

	for (i=size ; i>=1 ; i--) {
		printnstring(s1,size-i);
		printnstring(s2,i);
		putchar('\n');	
	}
	return OK;
}

/*This function prints the following type of (double) triangle :
 *    +
 *   + +
 *  + + +
 *   + +
 *    +
 */
int print_diamond_triangle (char ch, int size){

	int i;
	char s1[2]={' ','\0'} , s2[3]={ch,' ','\0'};

	PARAMS_CHECK(ch,size)

	print_pyramid_triangle(ch,size);

	if (check_params(ch,size-1)==OK) {
		for (i=size-1 ; i>=1 ; i--) {
			printnstring(s1,size-i);
			printnstring(s2,i);
			putchar('\n');	
		}
	}
	return OK;
}

/*Paraments checking function :
 *return status as defined in figures.h.
 */
int check_params(char ch , int size) {

	if (!isprint(ch) || ch==' ') {
		return INPUT_CHAR_ERROR;
	}
	if (size<MIN_SIZE || size>MAX_SIZE) {
		return INPUT_SIZE_ERROR;
	}
	return OK;
}

/*Printing string "s" n times,
 *assuming "n"=MIN_SIZE..MAX_SIZE and "s" is printable.
 */
void printnstring (char* s, int n){

	int i;
	for (i=0 ; i<n ; i++) {
		printf("%s",s);
	}
}




