#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
struct Node
{
	int m_data;
	Node* m_next;
};


Node* ListCreate(int* _arr, int _n)
{
	Node* node;
	if (_n == 0)
	{
		return NULL;
	}
	node = malloc(sizeof(Node));
	node->m_data = *_arr;
	node->m_next = ListCreate(_arr+1, _n-1);
	return node;
}

void ListPrint(Node* _lst)
{
	while (_lst != NULL)
	{
		printf("%d  ", _lst->m_data);
		_lst = _lst->m_next;
	}
	putchar('\n');
}

Node* ListFlip(Node* _node)
{
	Node* head;
	
	if(NULL==_node)
	{
		return NULL;
	}
	
	if(NULL==_node->m_next)
	{
		return _node;
	}
	
	head=ListFlip(_node->m_next);
	_node->m_next->m_next=_node;
	_node->m_next=NULL;

	return head;
}

int main()
{
	int data[] = { 2,3,4,5, 6,7,8,9};
	Node* flipped;
	Node* list = ListCreate(data, sizeof(data)/sizeof(int));
	ListPrint(list);
	flipped = ListFlip(list);
	ListPrint(flipped);
	return 0;
}

