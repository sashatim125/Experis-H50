
#ifndef __DLIST_H__
#define __DLIST_H__

#include <cstring>
#include <string>

#include "container.h"

using namespace std;

template <class T>
class DLink : public Container<T> 
{
	public:

	DLink();

	DLink(const DLink& _arr);

	virtual ~DLink();

	virtual
	DLink& operator=(const DLink& _arr);
	
	virtual
	void Append(const T* _elem, size_t _index); //throws on index out of bounds
	
	virtual
	void Prepend(const T* _elem, size_t _index); //throws on index out of bounds
	
	virtual
	const T* Find(const T& _val) const ; //return 0 if not found
	
	virtual
	size_t Index(const T& _val) const; //throws when isn't there
	
	virtual
	void Insert(const T* _elem);
	
	virtual
	T* Remove(const T& _val) ; //throws when isn't there
	
	virtual
	void RemoveAll() ; 
	
	virtual
	void RemoveAndDelete(const T& _val) ; //throws when isn't there
	
	virtual
	void RemoveAndDeleteAll() ;
	
	private:
	
	struct Node_t
	{
		Node_t() {} //: m_val(0), m_prev(0), m_next(0) {}
		
		void InsertBefore(T* _val);
		
		void Delete(bool _withElement);
	
		T* m_val;
		
		Node_t* m_prev;
		
		Node_t* m_next;
	};
	
	Node_t m_head;
	
	Node_t m_tail;
	
	
	void DeleteList(bool _withElements);
	
	void CopyFromList(const DLink& _dl);
	
	Node_t* GoToIndex(size_t _index) const;

	Node_t* FindNode(const T& _val) const;

};




template <class T>
	DLink<T>::DLink() : Container<T>()
	{
		m_head.m_prev = &m_head;
		m_head.m_next = &m_tail;
		m_tail.m_prev = &m_head;
		m_tail.m_next = &m_tail;
	}
	

template <class T>
	DLink<T>::DLink(const DLink& _dl) : Container<T>(_dl)
{
	CopyFromList(_dl);
}

template <class T>
	DLink<T>::~DLink()
{
	DeleteList(false);
}

template <class T>
DLink<T>& DLink<T>::operator=(const DLink& _dl)
{
	if(&_dl != this)
	{
		DeleteList(false);
	
		Container<T>::operator=(_dl);
		
		CopyFromList(_dl);
	}
	return *this;
}

template <class T>
void DLink<T>::Append(const T* _elem, size_t _index)
{
	size_t count = Container<T>::Count();

	if(_index >= count)
	{
		throw (string("Index out of bounds!"));
	}
	
	GoToIndex(_index)->m_next->InsertBefore((T*)_elem);
	
	Container<T>::SetNumOfElem(count+1);
}


template <class T>
void DLink<T>::Prepend(const T* _elem, size_t _index)
{
	size_t count = Container<T>::Count();

	if(_index > count)
	{
		throw (string("Index out of bounds!"));
	}
	
	GoToIndex(_index)->InsertBefore((T*)_elem);
	
	Container<T>::SetNumOfElem(count+1);
}

template <class T>
const T* DLink<T>::Find(const T& _val) const
{
	Node_t *res = FindNode(_val);
	
	return (res == &m_tail) ? 0 : res->m_val;
}

template <class T>
size_t DLink<T>::Index(const T& _val) const
{
	size_t count = Container<T>::Count();
	Node_t *next = m_head.m_next;
	size_t i;
	
	if(0 == count)
	{
		throw (string("Empty container !"));
	}
	
	for(i=0 ; i < count ; ++i, next = next->m_next)
	{
		if(*(next->m_val) == _val)
		{			
			break;
		}	
	}
	
	if(i == count)
	{
		throw (string("No such element !"));
		return 0;
	}else
	{
		return i;
	}
}


template <class T>
void DLink<T>::Insert(const T* _elem)
{
	m_tail.InsertBefore((T*)_elem);
	
	Container<T>::SetNumOfElem(Container<T>::Count()+1);
}


template <class T>
T* DLink<T>::Remove(const T& _val)
{
	Node_t *res = FindNode(_val);
	T* valPtr = 0;
	
	if(res == &m_tail)
	{
		throw (string("No such element !"));
	}
	
	valPtr = res->m_val;
	
	res->Delete(false);

	Container<T>::SetNumOfElem(Container<T>::Count()-1);	

	return valPtr;
}


template <class T>
void DLink<T>::RemoveAll()
{
	DeleteList(false);
}


template <class T>
void DLink<T>::RemoveAndDelete(const T& _val)
{
	T* elem;
	
	try
	{
		elem = Remove(_val);
	}
	catch (string&)
	{
		throw;
	}

	delete elem;
}


template <class T>
void DLink<T>::RemoveAndDeleteAll()
{
	DeleteList(true);
	
	Container<T>::SetNumOfElem(0);
}



template <class T>
void DLink<T>::Node_t::InsertBefore(T* _val)
{
	Node_t* newNode = new Node_t;
	
	newNode->m_val = _val;
	
	newNode->m_next = this;
	newNode->m_prev = this->m_prev;
	this->m_prev = newNode;
	newNode->m_prev->m_next = newNode;
}

template <class T>
void DLink<T>::Node_t::Delete(bool _withElement)
{
	this->m_prev->m_next = this->m_next;
	this->m_next->m_prev = this->m_prev;
	
	if(_withElement)
	{
		delete this->m_val;
	}
	
	delete this;	
}

template <class T>
void DLink<T>::DeleteList(bool _withElements)
{
	Node_t *tmp, *next = m_head.m_next;
	
	//code duplication to do 1 if and not n ifs
	if(_withElements)
	{
		while(next != &m_tail)
		{
			tmp = next->m_next;
			delete next->m_val;
			delete next;
			next = tmp;
		}
	}else
	{
		while(next != &m_tail)
		{
			tmp = next->m_next;
			delete next;
			next = tmp;
		}
	}
}

template <class T>
void DLink<T>::CopyFromList(const DLink& _dl)
{
	Node_t *next = _dl.m_head.m_next;

	while(next != &_dl.m_tail)
	{
		m_tail.InsertBefore(next->m_val);
		next = next->m_next;
	}
}

template <class T>
typename DLink<T>::Node_t* DLink<T>::GoToIndex(size_t _index) const
{
	Node_t *res = m_head.m_next;
	
	for(;_index; --_index)
	{
		res = res->m_next;
	}
	
	return res;
}

template <class T>
typename DLink<T>::Node_t* DLink<T>::FindNode(const T& _val) const
{
	Node_t *next = m_head.m_next;

	while(next != &m_tail)
	{
		if(_val == *(next->m_val))
		{
			break;
		}
		next = next->m_next;
	}
	return next;
}









#endif//__DLIST_H__



