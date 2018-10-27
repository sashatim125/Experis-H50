
/** 
 *  @file DLinkListItrFunc.c
 *  @brief API for the functions over iterators 
 *	
 *  @details  See the functions description
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com 
 * 
 *  @bug exterminator at work! 
 */


#include "DLinkList.h"
#include "DLinkListItr.h"
#include "DLinkListItrFunc.h"
 
#ifndef IS_NULL
#define IS_NULL(ptr) (NULL==(ptr))
#endif /*IS_NULL*/

#ifndef TRUE
#define TRUE 1
#endif
 
#ifndef FALSE
#define FALSE 0
#endif
 

ListItr ListItr_FindFirst(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context)
{
	ListItr nextItr;

	if(IS_NULL(_begin)||IS_NULL(_end)||IS_NULL(_predicate))
	{
		return NULL;
	}
	
	nextItr = _begin;
	
	while(!ListItr_Equals(nextItr,_end))
	{
		if(_predicate(ListItr_Get(nextItr),_context))
		{
			break;
		}
			
		nextItr=ListItr_Next(nextItr);	
	}

	return nextItr;
}



size_t ListItr_CountIf(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context)
{
	ListItr nextItr;
	size_t counter;

	if(IS_NULL(_begin)||IS_NULL(_end)||IS_NULL(_predicate))
	{
		return 0;
	}
	
	counter=0;
	nextItr = _begin;
	
	while(!ListItr_Equals(nextItr,_end))
	{
		if(_predicate(ListItr_Get(nextItr),_context))
		{
			++counter;
		}
		nextItr=ListItr_Next(nextItr);	
	}
	
	return counter;
}



ListItr ListItr_ForEach(ListItr _begin, ListItr _end, ListActionFunction _action, void* _context)
{
	ListItr nextItr;

	if(IS_NULL(_begin)||IS_NULL(_end)||IS_NULL(_action))
	{
		return NULL;
	}
	
	nextItr = _begin;
	
	while(!ListItr_Equals(nextItr,_end))
	{
		if(!_action(ListItr_Get(nextItr),_context))
		{
			break;
		}
			
		nextItr=ListItr_Next(nextItr);	
	}

	return nextItr;
}



void ListItr_Sort(ListItr _begin, ListItr _end, LessFunction _less)
{
	ListItr next, beginNext;
	int wereSwaps;

	if(IS_NULL(_begin)||IS_NULL(_end)||IS_NULL(_less)||
		ListItr_Equals(_begin,_end)||ListItr_Equals(ListItr_Next(_begin),_end))
	{
		return ;
	}
	
	beginNext = ListItr_Next(_begin);
	wereSwaps = 1;
	
	while(!ListItr_Equals(beginNext,_end) && wereSwaps)
	{
		next = beginNext;
		wereSwaps = 0;
		
		while(!ListItr_Equals(next,_end))
		{
			if(_less(ListItr_Get(next),ListItr_Get(ListItr_Prev(next))))
			{
				/*swap with one before*/
				ListItr_Set(next,ListItr_Set(ListItr_Prev(next),ListItr_Get(next)));
				
				++wereSwaps;
			}
		
			next=ListItr_Next(next);
		}
	
		_end = ListItr_Prev(_end);	
	}
}



int ListItr_IsSorted(ListItr _begin, ListItr _end, LessFunction _less)
{
	ListItr next;

	if(IS_NULL(_begin)||IS_NULL(_end)||IS_NULL(_less))
	{
		return FALSE;
	}
	
	if(ListItr_Equals(_begin,_end)||ListItr_Equals(ListItr_Next(_begin),_end))
	{
		return TRUE;
	}
	
	next = ListItr_Next(_begin);
	
	while(!ListItr_Equals(next,_end))
	{
		if(_less(ListItr_Get(next),ListItr_Get(ListItr_Prev(next))))
		{
			return FALSE;
		}
	
		next=ListItr_Next(next);
	}
	
	return TRUE;
}


static ListItr ListItr_SpliceOneBefore(ListItr _dest, ListItr _iter)
{
	void *item;

	item = ListItr_Remove(ListItr_Prev(_iter));
	 
	return ListItr_InsertBefore(_dest,item);
}


	 
ListItr ListItr_Splice(ListItr _dest, ListItr _begin, ListItr _end)
{
	ListItr curr, newBegin;

	if(IS_NULL(_dest)||IS_NULL(_begin)||IS_NULL(_end))
	{
		return NULL;
	}
	
	/*dummy iterator to keep the begining*/
	newBegin = ListItr_InsertBefore(_dest,(void*)&newBegin);

	curr = _begin;
	
	while(!ListItr_Equals(curr,_end))
	{
		curr = ListItr_Next(curr);
	
		ListItr_SpliceOneBefore(_dest,curr);	
	}
	
	newBegin = ListItr_Next(newBegin);
	
	ListItr_Remove(ListItr_Prev(newBegin));
	
	return newBegin;
}



ListItr ListItr_Merge(ListItr _destEnd, ListItr _firstBegin, ListItr _firstEnd,
			ListItr _secondBegin, ListItr _secondEnd, LessFunction _less)
{
	ListItr firstCurr,secondCurr, newBegin;

	if(IS_NULL(_destEnd)||IS_NULL(_firstBegin)||IS_NULL(_firstEnd)||
		IS_NULL(_secondBegin)||IS_NULL(_secondEnd))
	{
		return NULL;
	}

	/*dummy iterator to keep the begining*/
	newBegin = ListItr_InsertBefore(_destEnd,(void*)&newBegin);
	
	firstCurr  = _firstBegin;
	secondCurr = _secondBegin;
	
	if(!IS_NULL(_less))
	{
		while(!ListItr_Equals(firstCurr,_firstEnd) && !ListItr_Equals(secondCurr,_secondEnd))
		{
			if(_less(ListItr_Get(secondCurr),ListItr_Get(firstCurr)))
			{
				secondCurr = ListItr_Next(secondCurr);
				ListItr_SpliceOneBefore(_destEnd,secondCurr);
				
			}else
			{
				firstCurr = ListItr_Next(firstCurr);
				ListItr_SpliceOneBefore(_destEnd,firstCurr);
			}
		}
	}
	
	if(!ListItr_Equals(firstCurr,_firstEnd))
	{
		ListItr_Splice(_destEnd,firstCurr,_firstEnd);
	}
	if(!ListItr_Equals(secondCurr,_secondEnd))
	{
		ListItr_Splice(_destEnd,secondCurr,_secondEnd);
	}
	
	newBegin = ListItr_Next(newBegin);
	
	ListItr_Remove(ListItr_Prev(newBegin));
	
	return newBegin;
}




List* ListItr_Cut(ListItr _begin, ListItr _end)
{
	List *newList;

	if(IS_NULL(_begin)||IS_NULL(_end))
	{
		return NULL;
	}
	
	if(IS_NULL(newList=ListCreate()))
	{
		return NULL;
	}
	
	ListItr_Splice(ListItr_End(newList),_begin,_end);
	
	return newList;
}




List* ListItr_Unique(ListItr _begin, ListItr _end, EqualsFunction _equals)
{
	List *newList;
	ListItr curr, dest;

	if(IS_NULL(_begin)||IS_NULL(_end)||IS_NULL(_equals))
	{
		return NULL;
	}
	
	if(ListItr_Equals(_begin,_end) || ListItr_Equals(ListItr_Next(_begin),_end))
	{
		return NULL;
	}
	
	if(IS_NULL(newList=ListCreate()))
	{
		return NULL;
	}
	
	dest = ListItr_End(newList);

	curr = ListItr_Next(_begin);
	
	while(!ListItr_Equals(curr,_end))
	{
		if(_equals(ListItr_Get(curr),ListItr_Get(ListItr_Prev(curr))))
		{
			ListItr_SpliceOneBefore(dest,curr);
		}
		curr = ListItr_Next(curr);
	}
		
	return newList;
}














