
#include "my_strings.h"
#include <stdio.h>
#include <string.h>
#include <stddef.h>

 #define PASS 0
 #define FAIL 1
 
void run_test(int(*test)()){
 
 	printf("Test %s.\n",(test()==PASS)?"passed":"failed");
}


/*testing  rev_string input check*/
int test1(void) {

	if (rev_str(NULL)!=NULL_POINTER_ERROR){
		return FAIL;
	}

 return PASS;
}

/*test rev_string on several inputs*/
int test2(void) {

	char s1[] = "abcdefg";
	char s3[] = "gfedcba";

	rev_str(s1);		
	if (strcmp(s1,s3)) {
		return FAIL;
	}
 return PASS;
}

/*testing  is_palyndrome input check*/
int test3(void) {

	if (is_palyndrome(NULL)!=NULL_POINTER_ERROR){
		return FAIL;
	}

 return PASS;
}

/*test is_palyndrome on several inputs*/
int test4(void) {

	char s1[] = "abcdefg";
	char s2[] = "abcdcba";

	if (is_palyndrome(s1)) {
		return FAIL;
	}
	if (!is_palyndrome(s2)) {
		return FAIL;
	}
 return PASS;
}


/*testing  print_binary */
int test5(void) {

	print_binary(5);
	putchar('\n');
	print_binary(13);
	putchar('\n');
	print_binary(10);
	putchar('\n');

 return PASS;
 }
 
 /*testing my_atoi input*/
 int test6(void) {

	if (my_atoi(NULL)!=0){
		return FAIL;
	}

 return PASS;
}

/*testing my_atoi on several inputs*/ 
 int test7(void) {
	char s1[]  ="123";
	char s2[] = "-543";
	char s3[] = "abc";
	char s4[] = " abs-125.5 ";
	int n1 = 123 , n2 = -543 , n3 = 0 , n4 = -125;
	
	if (my_atoi(s1)!=n1) {
		return FAIL;
	}
	if (my_atoi(s2)!=n2) {
		return FAIL;
	}
	if (my_atoi(s3)!=n3) {
		return FAIL;
	}
	if (my_atoi(s4)!=n4) {
		return FAIL;
	}
	return PASS;
}

/*test my_strstr*/
int test8(void){

	char s1[] = "abcd";
	char s2[] = "bc";
	
	if (my_strstr(s1,s2)!=s1+1) {
		return FAIL;
	}
	return PASS;
}

/*test my_itoa */
int test9(void){

	int n=-12345;
	char s[]  ="-12345" , buf[50];
	
	my_itoa(n,buf);
	
	if (strcmp(s,buf)!=0) {
		return FAIL;
	}
	return PASS;
}


int main() {

	run_test(test1);
	run_test(test2);
	run_test(test3);
	run_test(test4);
	run_test(test5);
	run_test(test6);
	run_test(test7);
	run_test(test8);
	run_test(test9);


	return 0;
}
