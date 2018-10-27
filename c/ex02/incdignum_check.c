/*checking the function inc_dig */

#include <stdio.h>
 #include "incdignum.h"

int main (void) {
	int n;
	
	printf("Please enter integer number :");
	scanf("%d",&n);
	
	printf("The digits of %d are ",n);
	if (!inc_dig(n)) {
		printf("not ");
	}
	printf("in strongly increasing order.\n");

	return 0;
}

