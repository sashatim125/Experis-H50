/*This file contains the API for the Vector data structure.
 *AUTHOR        : Timoshenko Alexander
 *LAST MODIFIED : 12.12.2017
 */
 
#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "../ADTErr.h"
#include <stddef.h>

 
/*Definition of the Queue type*/ 
typedef struct Queue Queue;
 
/*Description :new queue creation with _size;
 *Params : _size - maximal size;
 *Return: pointer to the created queue;
 *Error : ERR_OK,ERR_GENERAL,ERR_NOT_INITIALIZED,ERR_ALLOCATION_FAILED(NOT reported).
 */
Queue* QueueCreate(size_t _size);


/*Description :destruction of the queue;
 *Params : queue - to be destroyed.
 *Return: none;
 *Error : ERR_NOT_INITIALIZED - does nothing , DO NOT use this function more then ONE time.
 */
void   QueueDestroy(Queue *_queue);


/*Description :addition of new element to the tail;
 *Params : existing _queue, new _item;
 *Return: status (see Errors)
 *Error : ERR_OK,ERR_GENERAL,ERR_NOT_INITIALIZED,ERR_OVERFLOW.
 */
ADTErr QueueInsert(Queue *_queue, int  _item);


/*Description :removes the first item from the queue;
 *Params : the _queue, pointer to the _item returned;
 *Return: status;
 *Error : ERR_OK,ERR_GENERAL,ERR_NOT_INITIALIZED,ERR_UNDERFLOW.
 */
ADTErr QueueRemove(Queue *_queue, int *_item);


/*Description :checks if the queue is empty;
 *Params : the _queue;
 *Return: true(1) or false(0) [ true for ERR_NOT_INITIALIZED];
 *Error : ---.
 */
int    QueueIsEmpty(Queue *_queue);


/*Description :prints the queue;
 */
void   QueuePrint(Queue *_queue);

#endif/*__QUEUE_H__*/
