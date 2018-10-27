/*This file contains the linked list (Persons) data structure functions.
 *AUTHOR        : Timoshenko Alexander
 *LAST MODIFIED : 16.12.2017
 */

#include "llist.h"
#include <stdio.h>

#ifndef FOUND 
#define FOUND 1
#endif /*FOUND*/

#ifndef NOT_FOUND 
#define NOT_FOUND 0
#endif /*NOT_FOUND*/

/*Description :finds the node(with the provided key) from ALLREDY SORTED list ;
 *Params : _head - list head(can be NULL if empty list) , _key - comparison key, _p - (pointer to) the removed node(person);
 *         (_p should not be NULL).
 *Return: pointed to the the previous to founded or previous to greater key;
          FOUND and _p!=NULL - founded,
          FOUND and _p==NULL - founded in the head,
          NOT_FOUND and _p!=NULL - previous to greater key,
          NOT_FOUNDED and _p==NULL - should be befor the head.
 *Error : ---.
 */
static int FindByKey(Person* _head, int _key, Person** _p);


Person* ListInsertHead(Person* _head, Person* _p)
{
	/*no node to insert*/
	if(_p == NULL)
	{
		return _head;
	}
	_p->m_next = _head;
	return _p;
}

Person* ListRemoveHead(Person* _head, Person** _item)
{
	Person *nextP;
	
	/*nowere to remove*/
	if(_item==NULL)
	{
		return _head;
	}
	/*empty list*/
	if(_head==NULL)
	{
		*_item=NULL;
		return NULL;/*underflow*/
	}
	
	nextP=_head->m_next;
	_head->m_next=NULL;
	*_item=_head;
	return nextP;
}


Person* ListInsertByKey(Person* _head, int _key, Person* _p)
{
	Person *placeToInsert;
	int stat;
	
	/*no node to insert*/
	if(_p==NULL)
	{
		return _head;
	}
	
	/*allredy exists*/
	if ((stat=FindByKey(_head,_key,&placeToInsert))==FOUND)
	{
		return _head;
	}
	
	else
	{
	
		if (NULL==placeToInsert)
		{
			return ListInsertHead(_head,_p);
		}
		
		else
		{
			placeToInsert->m_next=ListInsertHead(placeToInsert->m_next,_p);
			return _head;
		}
	}

}



Person* ListInsertByKeyRec(Person* _head, int _key, Person* _p)
{
	/*no node to insert*/
	if(_p==NULL)
	{
		return _head;
	}
	
	if ((_head==NULL) || (_key < _head->m_id))
	{
		return ListInsertHead(_head,_p);
	}
	/*key duplication error*/
	if (_key == _head->m_id)
	{
		return _head;
	}

	_head->m_next = ListInsertByKeyRec(_head->m_next,_key,_p);
	return _head;
}



Person* ListRemoveByKey(Person* _head, int _key, Person** _p)
{
	Person *placeToRemove;
	int stat;
	
	/*nowere to remove*/
	if(_p==NULL)
	{
		return _head;
	}
	
	if ((stat=FindByKey(_head,_key,&placeToRemove))==NOT_FOUND)
	{
		*_p=NULL;
		return _head;
	}
	else
	{
		if (NULL==placeToRemove)
		{
			return ListRemoveHead(_head,_p);
		}
		else
		{
			placeToRemove->m_next=ListRemoveHead(placeToRemove->m_next,_p);
			return _head;
		}
	}

}


Person* ListRemoveByKeyRec(Person* _head, int _key, Person**_p)
{	
	/*nowere to remove*/
	if(_p==NULL)
	{
		return _head;
	}
	/*empty list - underflow or nothing found*/
	if (_head==NULL) 
	{
		*_p=NULL;
		return _head;
	}
	/*its not on the list*/
	if (_key < _head->m_id)
	{
		return _head;
	}
	/*found!*/
	if (_key == _head->m_id)
	{
		return ListRemoveHead(_head,_p);
	}
	
	_head->m_next = ListRemoveByKeyRec(_head->m_next,_key,_p);
	return _head;
}

void PrintList(Person* _head)
{
	/*empty list*/
	if (_head==NULL)
	{
		printf("\nThe list is empty.\n");
		return;
	}
	printf("The list :\n\n");
	while(_head!=NULL)
	{
		PrintPerson(_head);
		_head=_head->m_next;
	}
	printf("The end of list.\n");
}


void PrintPerson(Person* _p)
{
	if (_p==NULL)
	{
		return;
	}
	printf("The ID   is :%d;\n",_p->m_id);
	printf("The name is :%s;\n",_p->m_name);
	printf("The age  is :%d;\n\n",_p->m_age);
}


int FindByKey(Person* _head, int _key, Person** _p)
{
	Person* nextP;

	/*should be before the head*/	
	if ((_head==NULL) || (_key < _head->m_id))
	{
		*_p=NULL;
		return NOT_FOUND;
	}

	/*head is the requested person*/
	if (_key == _head->m_id)
	{
		*_p=NULL;
		return FOUND;
	}
	
	for(nextP=_head ; (nextP->m_next!=NULL) ; nextP=nextP->m_next)
	{
		/*found! in next node*/
		if (_key == nextP->m_next->m_id)
		{
			*_p=nextP;
			return FOUND;
		}
		else if (_key < nextP->m_next->m_id)
		{
			*_p=nextP;
			return NOT_FOUND;
		}
	}
	
	*_p=nextP;
	return NOT_FOUND;
}




















