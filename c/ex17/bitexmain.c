
/*This file contains main for functions from "bitex.h".
 *
 *AUTHOR        : Timoshenko Alexander
 *LAST MODIFIED : 06.12.2017
 */
#include "bitex.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main (){

	unsigned int big_c,val,i,j;
	unsigned char c;
	int n,choice;
	

	while(1){
		printf("\n\nWelcome to the bit games program !\n");
		printf("Menu :\n");
		printf("1 - make bitwise complement ;\n");
		printf("2 - rotate bitwise ;\n");
		printf("3 - set ON/OFF bits ;\n");
		printf("4 - exit.\n");
		printf("Make your choice :");
		scanf("%d",&choice);
	
		switch (choice){
			case 1 :
				printf("Enter your number (0-%u)?",UCHAR_MAX);
				scanf("%u",&big_c);
				c=big_c;
				printf("The result is :");
				bit_comp(c);
				putchar('\n');
				break;	
			case 2 :
				printf("Enter the number (0-%u) and\n",UCHAR_MAX);
				printf("the number of rotation (positive for right, negative for left).\n");
				scanf("%u %d",&big_c,&n);
				c=big_c;
				printf("The result is :");
				bit_rot(c,n);
				putchar('\n');
				break;
			case 3 :
				printf("Enter the number (0-%u) and\n",UCHAR_MAX);
				printf("from position(0-%u) to position(0-%u) and value(0 or 1).\n",CHAR_SIZE-1,CHAR_SIZE-1);
				scanf("%u %u %u %u",&big_c,&i,&j,&val);
				c=big_c;
				if (set_bits(&c,i,j,val)!=OK) {
					printf("Wrong parameters !\n");
				} else {
					printf("The result is :");
					print_binary(c);
					putchar('\n');
				}
				break;
			default :
				exit(EXIT_SUCCESS);
				break;	
		}
	}
	return 0;
}
