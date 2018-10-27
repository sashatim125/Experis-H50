/*This file contains 3 functions
 *that works on array of integer.
 */
 
#include "arr_funcs.h"
#include <stdio.h>
 
/*swapping 2 integer values*/
int swap (int* , int*); 
  
/*The following function will find the most popular member 
 *of the array "arr" of size "size".
 */
int most_popular(int arr[] , int size, int* most_pop_ptr){

	int i,j,most_pop_num,max_freq,temp_freq;

	IN_CHECK(arr,size)
	if (most_pop_ptr == NULL) {
		return POINTER_ERROR;
	} 	
	 
	max_freq = 0;
	most_pop_num = arr[0];
	
	for (i=0 ; i<size-max_freq ; i++) {
	
		temp_freq=1;
		for (j=i+1 ; j<size ; j++) {
		
			temp_freq+=(arr[j]==arr[i])?1:0;
		
		}
		if (temp_freq > max_freq) {
			max_freq = temp_freq;
			most_pop_num = arr[i];
		}
	}
	*most_pop_ptr = most_pop_num;
	
	return OK;
}

 
/*The following function will sort
 *(bubble sort) the array of integers "arr" in place
 *of size "size".
 */
  
int bubble_sort(int arr[] , int size){

	int i,j,swap_count;
	
	IN_CHECK(arr,size);	
	
	for (i=size-1 ; i>0 ; i--){
		swap_count = 0;
		for (j=0 ; j<i ; j++){	
			if (arr[j] > arr[j+1]){
				swap(arr+j,arr+j+1);
				swap_count++;				
			}
		}
		if (swap_count == 0) {
			break;
		}	
	}
	return OK;
}
 
 /*The following function will send the even members
  *of the array of integers "arr" of size "size"
  *to the left size of the array and the odd to the
  *right size in their corresponding order.
  */
  
int sort_even_odd(int arr[] , int size){

	int i,j,swap_count;
	
	IN_CHECK(arr,size);	
	
	for (i=size-1 ; i>0 ; i--){
		swap_count = 0;
		for (j=0 ; j<i ; j++){

			if ((arr[j]%2!=0) && (arr[j+1]%2==0)){
				swap(arr+j,arr+j+1);
				swap_count++;				
			}
		}
		if (swap_count == 0) {
			break;
		}	
	}
	return OK;
}

/*Input checking function*/
int inp_check(int* ptr, int size) {

	if (ptr==NULL) {
 		return POINTER_ERROR;
 	}
 	if (size<=0) {
 		return SIZE_ERROR;
 	}
 	
	return OK; 
}

/*swapping 2 integer values*/
int swap (int* a, int* b){
	int temp;
	
	if ((a==NULL) || (b==NULL)) {
		return POINTER_ERROR;	
	}
	
	temp=*a;
	*a=*b;
	*b=temp;
	
	return OK;
}


/*int sort_even_odd(int arr[] , int size){

	int i,j,even_count;
	
	IN_CHECK(arr,size);
	
	even_count=0;
	for (i=0 ; i<size ; i++) {
		even_count+=1-arr[i]%2;
	}
	for (i=even_count , j=even_count-1 ; (i<size) && (j>=0) ; i++ , j--){
		while (((arr[i]%2)==1)&&(i<size)) {
			i++;
		}
		if (i==size) {
			break;
		}
		while (((arr[j]%2)==0)&&(j>=0)) {
			j--;
		}
		if (j<0) {
			break;
		}
		swap(arr+i,arr+j);	
	}
	return OK;
}
*/
