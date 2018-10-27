
/*This file contains main for functions from "bitex3.h".
 *
 *AUTHOR        : Timoshenko Alexander
 *LAST MODIFIED : 06.12.2017
 */
 #include "bitex.h"
#include "bitex3.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_STRING_SIZE 20

int main (){

	int i,j;
	int choice;
	char s[MAX_STRING_SIZE];
	unsigned int p,n,big_x,big_y;
	unsigned char x,y;
	

	while(1){
		printf("\n\nWelcome to the bit games program !\n");
		printf("Menu :\n");
		printf("1 - compress without bitfields ;\n");
		printf("2 - compress with bitfields ;\n");
		printf("3 - set bits ;\n");
		printf("4 - exit.\n");
		printf("Make your choice :");
		scanf("%d",&choice);
	
		switch (choice){
			case 1 :
				printf("Enter your strings (a-p)?");
				scanf("%s",s);
		
				for (i=0;s[i]!='\0';++i){
 					print_binary(s[i]);putchar(' ');
 				}
 				putchar('\n');
 								
				compress_str1(s);
				
				printf("The result is :");
				
				for (j=0;j<i/2+i%2;++j){
 					print_binary(s[j]);putchar(' ');
 				}	
 				putchar('\n');
				break;	
			case 2 :
				printf("Enter your strings (a-p)?");
				scanf("%s",s);
		
				for (i=0;s[i]!='\0';++i){
 					print_binary(s[i]);putchar(' ');
 				}
 				putchar('\n');
 								
				compress_str2(s);
				
				printf("The result is :");
				
				for (j=0;j<i/2+i%2;++j){
 					print_binary(s[j]);putchar(' ');
 				}	
 				putchar('\n');
				break;
			case 3 :
				printf("Enter the values for x,p,n,y\n");
				scanf("%u %u %u %u",&big_x,&p,&n,&big_y);
				x=big_x;
				y=big_y;
				if (my_setbits(&x,p,n,y)!=OK) {
					printf("Wrong parameters !\n");
				} else {
					printf("The result is :");
					print_binary(x);
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
