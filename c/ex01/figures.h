/*Description :
 *This file conteins 6 functions that print
 *geometric figures (triangles)
 *of chars "ch" and of size "size";
 *
 *Input :
 *"ch" should be printable and
 *"size" should be MIN_SIZE..MAX_SIZE
 *
 *Return :
 *They return the status value defined below.
 */

#define INPUT_CHAR_ERROR 1
#define INPUT_SIZE_ERROR 2
#define OK 0

#define MAX_SIZE 40
#define MIN_SIZE 1


/*This function prints the following type of triangle :
 *  +
 *  ++
 *  +++
 */
int print_triangle (char ch, int size);

/*This function prints the following type of triangle :
 *  +++
 *  ++
 *  +
 */
int print_down_triangle (char ch, int size);

/*This function prints the following type of triangle :
 *  +
 *  ++
 *  +++
 *  ++
 *  +
 */
int print_arrow_triangle (char ch, int size);

/*This function prints the following type of triangle :
 *    +
 *   + +
 *  + + +
 */
int print_pyramid_triangle (char ch, int size);

/*This function prints the following type of triangle :
 *  + + +
 *   + +
 *    +
 */
int print_rev_piramid_triangle (char ch, int size);


/*This function prints the following type of (double) triangle :
 *    +
 *   + +
 *  + + +
 *   + +
 *    +
 */
int print_diamond_triangle (char ch, int size);



