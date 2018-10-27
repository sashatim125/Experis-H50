

#include <stdio.h>


void print_binary(unsigned int num){
	
	unsigned int rev_num=0;
	int is_even=0;

	if (num%2==0) {
		is_even++;
	}
	while (num>0){
		rev_num=rev_num*2+num%2;
		num/=2;
	}
	while (rev_num>0){
		putchar(rev_num%2+'0');
		rev_num/=2;
	}
	if (is_even) {
		putchar('0');
	}
}

int main(void) {

	unsigned int i;

	for (i=0 ; i<15 ; i++){
		printf("%d in binary is ",i);
		print_binary(i);
		putchar('\n');
	}
	return 0;
}



