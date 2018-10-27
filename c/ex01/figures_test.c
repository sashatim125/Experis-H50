/*This file conteins the program wich tests the 
 *6 functions that print
 *geometric figures (triangles).
 */

#include "figures.h"
#include <stdio.h>

/*testing function print_down_triangle*/
#define CHECK_PRINT_FUNC(func) \
{\
	printf("Testing function "#func);\
	putchar('\n');\
	printf("Please enter character :");\
	ch=getchar();\
	printf("\nand size :");\
	scanf ("%d",&size);\
	if (func(ch,size)) {\
		printf("Wrong input!\n");\
	};\
	getchar();\
}




int main(void) {

	char ch;
	int size;

/*testing function print_triangle*/
CHECK_PRINT_FUNC(print_triangle)

/*testing function print_down_triangle*/
CHECK_PRINT_FUNC(print_down_triangle)

/*testing function print_arrow_triangle*/
CHECK_PRINT_FUNC(print_arrow_triangle)

/*testing function print_pyramid_triangle*/
CHECK_PRINT_FUNC(print_pyramid_triangle)

/*testing function print_rev_piramid_triangle*/
CHECK_PRINT_FUNC(print_rev_piramid_triangle)

/*testing function print_diamond_triangle*/
CHECK_PRINT_FUNC(print_diamond_triangle)
}
