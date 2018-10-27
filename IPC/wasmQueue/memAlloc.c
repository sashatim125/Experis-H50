

#include "memAlloc.h"

/** 
 *  @file memAlloc.c
 *  @brief Implementation of simple memory management unit
 * (allocation and releasing)
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 *  @bug exterminator at work!  
 */

#define BITS 8

#define MSB_ON (((Block)1) << (sizeof(Block)*BITS-1) )

#define BLOCK_SIZE_BITS ((Block)(sizeof(Block)-1))

#define MIN_BUFF_SIZE (sizeof(Block)*5)

#define MIN_ALLOC_SIZE (2*sizeof(Block))

#define ZERO_HEADER (0)

#define ALIGN_FORWARD(blockPtr) \
do\
{\
	if (*((Block*)&(blockPtr)) & BLOCK_SIZE_BITS)\
	{\
		*((Block*)&(blockPtr)) |= BLOCK_SIZE_BITS ;\
		*((Block*)&(blockPtr)) += 1;\
	}\
}while(0)

#define ALIGN_BACKWARD(blockPtr) \
do\
{\
	*((Block*)&(blockPtr)) &= ~BLOCK_SIZE_BITS ;\
\
}while(0)

#define GET_BLOCK(blockPtr) (*((Block*)(blockPtr)))

#define IS_FREE(blockPtr) (!(GET_BLOCK(blockPtr) & MSB_ON))

#define SET_FREE(blockPtr)  do {*((Block*)(blockPtr)) &= ~MSB_ON;} while(0)

#define SET_ALLOC(blockPtr) do {*((Block*)(blockPtr)) |= MSB_ON;} while(0)

#define GET_BLOCK_SIZE(blockPtr)  (*((Block*)(blockPtr)) & ~MSB_ON)

#define NEXT_BLOCK(blockPtr) ((Block*)((Byte*)(blockPtr) + GET_BLOCK_SIZE(blockPtr)))



void* initMem(void* _buff, size_t _size)
{
	Byte *start, *end;

	if(NULL==_buff || _size < MIN_BUFF_SIZE)
	{
		return NULL;
	}
	
	start = (Byte*)_buff;
	end = ((Byte*)_buff)+_size;
	
	ALIGN_FORWARD(start);
	ALIGN_BACKWARD(end);
	
	end = (Byte*)((Block*)end - 1);
	
	*((Block*)end) = ZERO_HEADER;
	
	*((Block*)start) = (Block)(end-start);
	
	return start;
}


static void mergeForward(void *_blockStart)
{
	Block *start = (Block*)_blockStart;
	Block *next;
	
	SET_FREE(start);
	
	for(next = NEXT_BLOCK(start) ; GET_BLOCK(next) != ZERO_HEADER && IS_FREE(next); next = NEXT_BLOCK(next))
	{
		*start += GET_BLOCK_SIZE(next);	
	}
}


void releaseMem(void *_blockPtr)
{
	_blockPtr = (Block*)_blockPtr - 1;
	
	SET_FREE(_blockPtr);
	
	mergeForward(_blockPtr);
}


void* allocMem(void* _buffer, size_t _size)
{
	Block reqSize ;
	Block restSize;
	Block *header, *blkPtr;
	void* res;
	
	if(NULL==_buffer || 1 > _size)
	{
		return NULL;
	}
	
	reqSize = (_size % sizeof(Block)) ? 
		(Block)(_size - _size % sizeof(Block) + sizeof(Block)) : (Block)_size;
	header = _buffer;
	ALIGN_FORWARD(header);
	res = NULL;
	
	while(GET_BLOCK(header) != ZERO_HEADER && NULL==res)
	{	
		if(IS_FREE(header))
		{	
			mergeForward(header);

			/*have enough space*/
			if(GET_BLOCK_SIZE(header) >= sizeof(Block) + reqSize)			
			{
				restSize = GET_BLOCK_SIZE(header)-(Block)sizeof(Block) - reqSize;
				/*can split*/
				if(restSize >= MIN_ALLOC_SIZE)
				{
					blkPtr = (Block*)((Byte*)header + reqSize + (Block)sizeof(Block));
					GET_BLOCK(blkPtr) = restSize;
					SET_FREE(blkPtr);
				}
				GET_BLOCK(header) = (Block)sizeof(Block) + reqSize;
				SET_ALLOC(header);
				res = header+1;
			}
		}		
		header = NEXT_BLOCK(header);
	}

	return res;
}















