
#ifndef __SORT_H__
#define __SORT_H__

#include "../ADTErr.h"
#include <stddef.h> /*size_t*/

/** 
 *  @file sort.h
 *  @brief API for various sort algorithms
 *	
 *  @details  See the functions description
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 *  @bug NONE! 
 */


/** 
 * @brief Insertion sort
 * time : worst and average - O(n^2), best O(n)),
 * memory : O(1) ,
 * stable.
 * @param[in] _arr - unsorted array of ints,
 * @param[in] _size - size of the array
 * @return status
 * @retval ERR_OK on success
 * @retval ERR_NOT_INITIALIZED 
 */
ADTErr InsertionSort(int _arr[], size_t _size);



/** 
 * @brief Shell sort
 * time : worst - O(n^2), average - depends on the gap, best O(nlog n)),
 * memory : O(1) ,
 * unstable.
 * @param[in] _arr - unsorted array of ints,
 * @param[in] _size - size of the array
 * @return status
 * @retval ERR_OK on success
 * @retval ERR_NOT_INITIALIZED 
 */
ADTErr ShellSort(int _arr[], size_t _size);


/** 
 * @brief Quick sort (recursive implementation);
 * time : worst - O(n^2), average and best O(nlog n)),
 * memory : O(log n) up to O(n),
 * unstable.
 * @param[in] _arr - unsorted array of ints,
 * @param[in] _size - size of the array
 * @return status
 * @retval ERR_OK on success
 * @retval ERR_NOT_INITIALIZED 
 */
ADTErr QuickSortRec(int _arr[], size_t _size);


/** 
 * @brief Quick sort (itarative implementation);
 * time : worst - O(n^2), average and best O(nlog n)),
 * memory : O(log n) up to O(n),
 * unstable.
 * @param[in] _arr - unsorted array of ints,
 * @param[in] _size - size of the array
 * @return status
 * @retval ERR_OK on success
 * @retval ERR_NOT_INITIALIZED
 * @retval ERR_ALLOCATION_FAILED 
 */
ADTErr QuickSortIt(int _arr[], size_t _size);


/** 
 * @brief Selection sort
 * time : worst and best and average - O(n^2),
 * memory : O(1) ,
 * unstable.
 * @param[in] _arr - unsorted array of ints,
 * @param[in] _size - size of the array
 * @return status
 * @retval ERR_OK on success
 * @retval ERR_NOT_INITIALIZED 
 */
ADTErr SelectionSort(int _arr[], size_t _size);


/** 
 * @brief Merge sort
 * time : worst and best and average - O(nlog n),
 * memory : O(1) ,
 * stable.
 * @param[in] _arr - unsorted array of ints,
 * @param[in] _size - size of the array
 * @return status
 * @retval ERR_OK on success
 * @retval ERR_NOT_INITIALIZED 
 */
ADTErr MergeSort(int _arr[], size_t _size);

/** 
 * @brief Count sort (0 <= numbers <= r)
 * time : worst and best and average - O(n),
 * memory : O(r) +O(n),
 * stable.
 * @param[in] _arr - unsorted array of ints,
 * @param[in] _size - size of the array
 * @return status
 * @retval ERR_OK on success
 * @retval ERR_NOT_INITIALIZED 
 */
ADTErr CountSort(int _arr[], size_t _size);









#endif/*__SORT_H__*/

