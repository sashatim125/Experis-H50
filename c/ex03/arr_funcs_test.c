/*This programs tests the 3 array functions
 *from arr_funcs.h.
 */
 
 #include "arr_funcs.h"
 #include <stdio.h>
 
 /*#define ARRAY_SIZE 5*/
 #define PASS 0
 #define FAIL 1
/*#define MAX_TEST_NUM 3
 
#define RUN_TEST(num) \
{\
	char passed[]="passed !\n" , failed[]="failed !\n";\
 	printf ("Test %d %s",num,(test_#num() == PASS) ? passed : failed);\
}
*/

 /*pring the array values*/
 int print_array(int* , int);
 
 /*receiving array values*/
 int rec_array(int* ,int);
 
 /*compares 2 array of size "size" and returns 0 if they are equal or
  * non-0 if they are not.
  */
 int comp_arrays(int[] , int[] , size_t);
 
 void run_test(int(*test)()){
 
 	printf("Test %s.\n",(test()==PASS)?"passed":"failed");
 }
 
 /*most popular input check*/
 int test_1(void){

	int arr[] = {1,2,3,4,5} , res;
	if ((most_popular(NULL,5,&res) != POINTER_ERROR) || 
	   (most_popular(arr,5,NULL) != POINTER_ERROR) ||
	   (most_popular(arr,0,&res) != SIZE_ERROR)) {
		return FAIL; 
	}
	return PASS;
 }
 /*most_popular 1 most popular check*/
 int test_2(void){
 
 	int arr[] = {1,2,2,3,3,3,4,4,4,4,5,5,5,5,5} , res , i;
 	
 	most_popular(arr,15,&res);
 	if (res != 5) {
 		return FAIL;
 	}
  	return PASS;
 }
 
 /*most_popular many most populars check*/
  int test_3(void){
 
 	int arr[] = {1,2,2,3,3,4} , res , i;
 	
 	most_popular(arr,6,&res);
 	if (res != 2) {
 		return FAIL;
 	}
  	return PASS;
 }
 
/*bubble_sort input check*/ 
 int test_4(void){

	int arr[] = {1,2,3,4,5} , res;
	if ((bubble_sort(NULL,5) != POINTER_ERROR) || 
	   (bubble_sort(arr,0) != SIZE_ERROR)) {
		return FAIL; 
	}
	return PASS;
 }

/*bubble_sort sorted array check*/
int test_5(void){

	int arr_before[] = {1,2,3,4,5} ,arr_after[] = {1,2,3,4,5} ,res;

	bubble_sort(arr_before,5);
	if (comp_arrays(arr_before,arr_after,5)) {
		return FAIL;
	}
	return PASS;
}



 int main(void) {
/*
	int i;
	
	for (i=1 ; i<=MAX_TEST_NUM ; i++) {
		RUN_TEST(i)
	}
*/
	run_test(test_1);
	run_test(test_2);
	run_test(test_3);
	run_test(test_4);
	run_test(test_5);	
	
	
	return 0; 
/* 	int arr[ARRAY_SIZE] , most_pop_num;

	rec_array(arr,ARRAY_SIZE);

	most_popular(arr,ARRAY_SIZE,&most_pop_num);
 	printf("The most popular number is %d.\n",most_pop_num);

	sort(arr,ARRAY_SIZE);
	
	printf("The sorted array is :\n");
	
	print_array(arr,ARRAY_SIZE);
	
	rec_array(arr,ARRAY_SIZE);
 	
 	sort_even_odd(arr,ARRAY_SIZE);
 	
	printf("The even-odd sorted array is :\n");
 	
 	print_array(arr,ARRAY_SIZE);

 	return 0;
 */
 }
 
 int print_array(int arr[], int size){
 
 	int i;
 
 	IN_CHECK(arr,size)
 	
 	printf("Printing the array ...\n");
 	for (i=0 ; i<size ; i++) {
 		printf("%d ",arr[i]);
 	}
 	putchar('\n');
 
 	return OK;
 }
 
int rec_array(int arr[] ,int size){

	int i;
	
	IN_CHECK(arr,size)

	printf("Receiving the numbers ...\n");
 	
 	for (i=0 ; i<size ; i++){
 		printf("Please enter the %d-th number :",i+1);
 		scanf("%d",arr+i);
 	}
	return OK;
}

int comp_arrays(int arr1[] , int arr2[] , size_t size){

	size_t i;
	int res=0;
	
	if ((arr1 == NULL) || (arr2 == NULL)) {
		return POINTER_ERROR;
	}

	for (i=0 ; (i<size) && (res == 0) ; i++){
		res = (arr1[i]-arr2[i]);
	}
	return res;

}
 
 
 
