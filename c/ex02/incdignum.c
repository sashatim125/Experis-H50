/* The function checks if all
 * its digits are in strongly increasing order.
 * like 1234 is OK, while 143 and 133 are NOT.
 */
 
 #include "incdignum.h"
 
 int inc_dig (int n){
 
	 int temp;
	 
	 if (n<0) {
	 	n*=-1;
	 }
 
 	/*n conteins no more then 1 digit*/
 	if (n<9) {
 		return TRUE;
	 }
 
	 do {
	 	temp=n%10;
	 	n/=10;
 		if (temp<=n%10) {
	 		return FALSE;
	 	} 

	 } while (0!=n);
 
	 return TRUE;
 }
