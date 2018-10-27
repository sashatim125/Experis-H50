

#include <stdio.h>

int main() {

	FILE *my_file;
	int res;
	
	if ((my_file=fopen("file1","r")) != NULL) {
		fprintf(stdout,"File opened.\n");
	}
	
	
	



	if (fclose(my_file) == 0) {
		fprintf(stdout,"File closed.\n");
	}



	return 0;
}

