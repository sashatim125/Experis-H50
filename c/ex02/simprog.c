

#include <stdio.h>

#define ARR_SIZE 10

int main(void) {

	int arr[ARR_SIZE] , i , sum=0;
	
	for (i=0 ; i<ARR_SIZE ; i++){
		printf("Enter integer number :");
		scanf("%d",arr+i);
		sum+=arr[i];
	}
	printf("The sum of all numbers is :%d\n",sum);

return 0;
}

