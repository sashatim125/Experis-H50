
/*This file contains main for functions from "lotto.h".
 *
 *AUTHOR        : Timoshenko Alexander
 *LAST MODIFIED : 04.12.2017
 */
#include "lotto.h"
#include <stdio.h>

int main(int argc,char *argv[]){

	if (argc!=2) {
		fprintf(stderr,"Paramers error!\n");
		return 1;
	}
	
	if (lotto(argv[1])!=OK) {
		fprintf(stderr,"Paramers error!\n");
		return 1;
	}
	
	return 0;
}

