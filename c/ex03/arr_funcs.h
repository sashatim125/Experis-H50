/*This file contains the declaration of 3 functions
 *that works on array of integer.
 */
 
 #define OK 0
 #define POINTER_ERROR 1
 #define SIZE_ERROR 2
 
/*Input checking macro using inp_check*/
#define IN_CHECK(arr,size) \
{\
	int res;\
	\
	if ((res=inp_check(arr,size))!=OK) {\
		return res;\
	}\
} 

/*Input checking function*/
int inp_check(int* ptr, int size);
 
/*The following function will find the most popular member 
 *of the array "arr" of size "size".
 */
int most_popular(int arr[] , int size, int* most_pop_ptr);
 
/*The following function will sort
 *(bubble sort) the array of integers "arr" in place
 *of size "size".
 */
  
int bubble_sort(int arr[] , int size);
 
/*The following function will send the even members
 *of the array of integers "arr" of size "size"
 *to the left size of the array and the odd to the
 *right size in their corresponding order.
 */
  
int sort_even_odd(int arr[] , int size);


 
 
