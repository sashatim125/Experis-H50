
/*This file contains tests for file functions from "file_funcs.h".
 *
 *AUTHOR        : Timoshenko Alexander
 *LAST MODIFIED : 04.12.2017
 */

#include "file_funcs.h"
#include <stdlib.h>
#include <stdio.h>


#define PASS 0
#define FAIL 1

void run_test(int i,int(*test)()){
 
 	printf("Test #%02d %s.\n",i,(test()==PASS)?"passed":"failed");
}

/*testing diff_strings*/
int test1(void) {

	return (diff_strings("test1.txt","test2.txt")==OK)?PASS:FAIL;
}

/*testing diff_strings*/
int test2(void) {

	return (file_word_count("test3.txt")==OK)?PASS:FAIL;
}

/*testing char_count*/
int test3(void) {

	if((char_count("test0.txt")==OK)&&
	   (char_count("test1.txt")==OK)&&
	   (char_count("test2.txt")==OK)&&
	   (char_count("test3.txt")==OK)){
		return PASS;
	}else return FAIL;
}

/*testing char_count*/
int test4(void) {

	if((word_count("test0.txt")==OK)&&
	   (word_count("test1.txt")==OK)&&
	   (word_count("test2.txt")==OK)&&
	   (word_count("test3.txt")==OK)){
		return PASS;
	}else return FAIL;
}


int main() {

	run_test(1,test1);
	run_test(2,test2);
	run_test(3,test3);
	run_test(4,test4);
/*	run_test(5,test5);
	run_test(6,test6);
	run_test(7,test7);
	run_test(8,test8);
	run_test(9,test9);
	run_test(10,test10);
*/
	return 0;
}

