
#include "my_strings.h"
#include <stdio.h>
#include <string.h>
#include <stddef.h>

 #define PASS 0
 #define FAIL 1
 
void run_test(int(*test)()){
 
 	printf("Test %s.\n",(test()==PASS)?"passed":"failed");
}


/*testing  print_binary */
int test1(void) {

	print_binary(0);
	putchar('\n');
	print_binary(5);
	putchar('\n');
	print_binary(13);
	putchar('\n');
	print_binary(10);
	putchar('\n');
	print_binary(-1);
	putchar('\n');


 return PASS;
 }
 
 /*testing my_atoi input*/
 int test2(void) {

	if (my_atoi(NULL)!=0){
		return FAIL;
	}

 return PASS;
}

/*testing my_atoi on several inputs*/ 
 int test3(void) {
	char s1[]  ="100";
	char s2[] = "55.444";
	char s3[] = "	1234 15";
	char s4[] = " -1234";
	char s5[] = " +1234";
	char s6[] = "123four";
	char s7[] = "invalid123";
	
	int n1 = 100 , n2 = 55 , n3 = 1234 , n4 = -1234 ,\
	    n5 = 1234, n6 = 123, n7 = 0;
	
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
	if (my_atoi(s5)!=n5) {
		return FAIL;
	}
	if (my_atoi(s6)!=n6) {
		return FAIL;
	}
	if (my_atoi(s7)!=n7) {
		return FAIL;
	}

	return PASS;
}
/*testing  rev_string input check*/
int test4(void) {

	if (rev_str(NULL)!=NULL_POINTER_ERROR){
		return FAIL;
	}

 return PASS;
}

/*test rev_string on several inputs*/
int test5(void) {

	char s1[] = "abcdefg";
	char s2[] = "gfedcba";
	char s3[] = "";
	char s4[] = "abba";

	rev_str(s3);		
	if (strcmp(s3,s3)) {
		return FAIL;
	}	
	rev_str(s1);		
	if (strcmp(s1,s2)) {
		return FAIL;
	}
	rev_str(s4);		
	if (strcmp(s4,s4)) {
		return FAIL;
	}
 return PASS;
}

/*testing  is_palyndrome input check*/
int test6(void) {

	if (is_palyndrome(NULL)!=NULL_POINTER_ERROR){
		return FAIL;
	}

 return PASS;
}

/*test is_palyndrome on several inputs*/
int test7(void) {

	char s1[] = "abcdefg";
	char s2[] = "abcdcba";
	char s3[] = "";

	if (is_palyndrome(s1)) {
		return FAIL;
	}
	if (!is_palyndrome(s2)) {
		return FAIL;
	}
	if (!is_palyndrome(s3)) {
		return FAIL;
	}
 return PASS;
}

/*testing  strstr input check*/
int test8(void) {

	char s1[] = "12345";
	char s2[] = "12";
	char s3[] = "";

	if (my_strstr(NULL,s1)!=NULL || my_strstr(s1,NULL)!=NULL || my_strstr(s2,s1)!=NULL || 
	    my_strstr(s1,s3)!=NULL){
		return FAIL;
	}

 return PASS;
}
 
 
/*test my_strstr*/
int test9(void){

	char s1[] = "abcd";
	char s2[] = "bc";
	char s3[] = "abd";
	char s4[] = "bcbc";
	
	if (my_strstr(s1,s2)!=s1+1) {
		return FAIL;
	}
	if (my_strstr(s2,s1)!=NULL) {
		return FAIL;
	}
	if (my_strstr(s1,s3)!=NULL) {
		return FAIL;
	}
	if (my_strstr(s4,s2)!=s4) {
		return FAIL;
	}
	
	return PASS;
}
/*testing my_itoa input*/
 int test10(void) {

	if (my_itoa(0, NULL)!=NULL){
		return FAIL;
	}

 return PASS;
}

/*test my_itoa */
int test11(void){

	int n1=0 , n2=-5 , n3=125;
	char buf[50];
	char s1[]  = "0", s2[] = "-5", s3[] = "125";
	
	my_itoa(n1,buf);
	if (strcmp(s1,buf)!=0) {
		return FAIL;
	}
	my_itoa(n2,buf);
	if (strcmp(s2,buf)!=0) {
		return FAIL;
	}
	my_itoa(n3,buf);
	if (strcmp(s3,buf)!=0) {
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
	run_test(test10);
	run_test(test11);

	return 0;
}
