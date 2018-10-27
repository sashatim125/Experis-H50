
/*This file contains main for functions from "bitmap.h".
 *
 *AUTHOR        : Timoshenko Alexander
 *LAST MODIFIED : 05.12.2017
 */
#include "bitmap.h"
#include <stdio.h>
#include <stdlib.h>

#define SIZEBITS 70U

int main (){

	const bitfunc_t bit_funcs[]={bitON,bitOFF,isbitON};

	bitmap_t *mybm;
	int choice, pos;

	if ((mybm=create_bitmap(SIZEBITS-1)) == NULL){
		perror("Error!\n");
		exit(EXIT_FAILURE);
	}
	while(1){
		printf("\n\nWelcome to the bitmap program !\n");
		printf("Menu :\n");
		printf("1 - set bit ON ;\n");
		printf("2 - set bit OFF ;\n");
		printf("3 - check bit ;\n");
		printf("4 - print the bitmap ;\n");
		printf("5 - exit.\n");
		printf("Make your choice :");
		scanf("%d",&choice);
	
		switch (choice){
			case 1 :
				printf("Which one (0-%u)?",SIZEBITS-1);
				scanf("%u",&pos);
				if ((bit_funcs[0])(mybm,pos)==OK){
					printf("The bit is ON.\n");
				}else printf("Wrong input.\n");
				break;	
			case 2 :
				printf("Which one (0-%u)?",SIZEBITS-1);
				scanf("%u",&pos);
				if ((bit_funcs[1])(mybm,pos)==OK){
					printf("The bit is OFF.\n");
				}else printf("Wrong input.\n");
				break;
			case 3 :
				printf("Which one (0-%u)?",SIZEBITS-1);
				scanf("%u",&pos);
				if ((bit_funcs[2])(mybm,pos)) {
					printf("Its ON.\n");
				}else printf("Its OFF.\n");
				break;
			case 4 :
				print_bitmap(mybm);
				break;	
			default :
				destroy_bitmap(mybm);
				exit(EXIT_SUCCESS);
				break;	
		}
	}
	return 0;
}
