/*This file contains the API for the linked list (Persons) data structure.
 *AUTHOR        : Timoshenko Alexander
 *LAST MODIFIED : 16.12.2017
 */
 
#ifndef __LLIST_H__
#define __LLIST_H__

 
/*Definition of the Linked List type*/ 
typedef struct Person Person;

struct Person
{
    int     m_id; /* Unique Key */
    char    m_name[128];
    int     m_age;
    Person* m_next;
};

 
/*Description :adds the new node that become the new head;
 *Params : _head - old head , _p - the new person;
 *Return: (pointer to) the new head;
 *Error : NULL _p =>do nothing.
 */
Person* ListInsertHead(Person* _head, Person* _p);


/*Description :removes the head node;
 *Params : _head - old head , _item pointer to the node to be returned;
 *Return: (pointer to) the new head;
 *Error : NULL _item =>do nothing,NUll _head = underflow,return NULL.
 */
Person* ListRemoveHead(Person* _head, Person** _item);


/*Description :inserts the new node to ALLREDY SORTED list (interative implementation);
 *Params : _head - old head , _key - comparison key, _p - the new node(person);
 *Return: (pointer to) the new head;
 *Error : NULL _item , key duplication =>do nothing.
 */
Person* ListInsertByKey(Person* _head, int _key, Person* _p);


/*Description :inserts the new node to ALLREDY SORTED list (recursive implementation);
 *Params : _head - old head , _key - comparison key, _p - the new node(person);
 *Return: (pointer to) the new head;
 *Error : NULL _item , key duplication =>do nothing.
 */
Person* ListInsertByKeyRec(Person* _head, int _key, Person* _p);


/*Description :remove the node(with the provided key) from ALLREDY SORTED list (interative implementation);
 *Params : _head - old head , _key - comparison key, _p - (pointer to) the removed node(person);
 *Return: (pointer to) the new head;
 *Error : NULL _item ,empty list(underflow) =>do nothing.
 */
Person* ListRemoveByKey(Person* _head, int _key, Person** _p);


/*Description :remove the node(with the provided key) from ALLREDY SORTED list (recursive implementation);
 *Params : _head - old head , _key - comparison key, _p - (pointer to) the removed node(person);
 *Return: (pointer to) the new head;
 *Error : NULL _item ,empty list(underflow) =>do nothing.
 */
Person* ListRemoveByKeyRec(Person* _head, int _key, Person**_p);


/*Description :prints the list;
 *Params : _head - the head ;
 *Return: nothing
 *Error : empty list =>do nothing.
 */
void    PrintList(Person* _head);

/*Description :prints the person data;
 *Params : _ - the person node ;
 *Return: nothing
 *Error : null pointer =>do nothing.
 */
void PrintPerson(Person* _p);

#endif/*__LLIST_H__*/


