
#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <cstring>
#include <string>

#include "container.h"

using namespace std;

template <class T>
class Array : public Container<T> 
{
	public:

	Array();

	Array(const Array& _arr);

	virtual ~Array();

	virtual
	Array& operator=(const Array& _arr);
	
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

	protected:

	void ShiftElemsRight(size_t _start, size_t _end);
	
	void ShiftElemsLeft(size_t _start, size_t _end);
	
	void Realloc(); //capacity*=2 , throws if error
	
	private:
	
	T** m_elements;
	
	size_t m_capacity;
	
	static const size_t initCapacity = 16;


};


template <class T>
	Array<T>::Array() : Container<T>(), m_elements(0), m_capacity(0) {}
	

template <class T>
	Array<T>::Array(const Array& _arr) : Container<T>(_arr)
{
	m_capacity = _arr.m_capacity;
	
	m_elements = new T*[m_capacity];
	
	memcpy(m_elements, _arr.m_elements, Container<T>::Count()*sizeof(T*));
}

template <class T>
	Array<T>::~Array()
{
	delete[] m_elements;
}

template <class T>
Array<T>& Array<T>::operator=(const Array& _arr)
{
	if(&_arr != this)
	{
		delete[] m_elements;
	
		Container<T>::operator=(_arr);
		
		m_capacity = _arr.m_capacity;
	
		m_elements = new T*[m_capacity];
	
		memcpy(m_elements, _arr.m_elements, Container<T>::Count()*sizeof(T*));
	}
	return *this;
}

template <class T>
void Array<T>::Append(const T* _elem, size_t _index)
{
	size_t count = Container<T>::Count();

	if(_index >= count)
	{
		throw (string("Index out of bounds!"));
	}
	
	if(m_capacity == count)
	{
		try
		{
			Realloc();
		}
		catch(string&)
		{
			throw;
		}
	}
	
	if(_index < count -1)
	{
		ShiftElemsRight(_index+1, count-1);
	}
	
	m_elements[_index+1] = (T*)_elem;
	
	Container<T>::SetNumOfElem(count+1);
}


template <class T>
void Array<T>::Prepend(const T* _elem, size_t _index)
{
	size_t count = Container<T>::Count();

	if(_index > count)
	{
		throw (string("Index out of bounds!"));
	}
	
	if(m_capacity == count)
	{
		try
		{
			Realloc();
		}
		catch(string&)
		{
			throw;
		}
	}
	
	if(_index < count)
	{
		ShiftElemsRight(_index, count-1);
	}
	
	m_elements[_index] = (T*)_elem;
	
	Container<T>::SetNumOfElem(count+1);
}

template <class T>
const T* Array<T>::Find(const T& _val) const
{
	size_t count = Container<T>::Count();
	T* res = 0;
	
	for(size_t i=0 ; i < count ; ++i)
	{
		if(*m_elements[i] == _val)
		{
			res = m_elements[i];
			
			break;
		}	
	}
	
	return res;
}

template <class T>
size_t Array<T>::Index(const T& _val) const
{
	size_t count = Container<T>::Count();
	size_t i;
	
	if(0 == count)
	{
		throw (string("Empty container !"));
	}
	
	for(i=0 ; i < count ; ++i)
	{
		if(*m_elements[i] == _val)
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
void Array<T>::Insert(const T* _elem)
{
	try
	{
		Prepend(_elem, Container<T>::Count());
	}
	catch(string&)
	{
		throw;
	}
}


template <class T>
T* Array<T>::Remove(const T& _val)
{
	size_t i;
		
	try
	{
		i = Index(_val);
	}
	catch (string&)
	{
		throw;
	}
	
	T* res = m_elements[i];
	size_t count = Container<T>::Count();
	
	if(i< count-1)
	{
		ShiftElemsLeft(i+1,count);
	}

	Container<T>::SetNumOfElem(count-1);	

	return res;
}


template <class T>
void Array<T>::RemoveAll()
{	
	Container<T>::SetNumOfElem(0);
}

template <class T>
void Array<T>::RemoveAndDelete(const T& _val)
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
void Array<T>::RemoveAndDeleteAll()
{
	size_t count = Container<T>::Count();	
	
	for(size_t i = 0 ; i< count ; ++i)
	{
		delete m_elements[i];
	}
	
	Container<T>::SetNumOfElem(0);
}

template <class T>
void Array<T>::ShiftElemsRight(size_t _start, size_t _end)
{
	while(_end >= _start)
	{
		m_elements[_end+1] = m_elements[_end];
		--_end;
	}
}


template <class T>
void Array<T>::ShiftElemsLeft(size_t _start, size_t _end)
{
	while(_start <= _end)
	{
		m_elements[_start-1] = m_elements[_start];
		++_start;
	}
}


template <class T>
void Array<T>::Realloc()
{
	if(0 == m_capacity)
	{
		m_elements = new T*[initCapacity];
		
		if(!m_elements)
		{
			throw (string("Memory alloc error!"));
		}else
		{
			m_capacity = initCapacity;
		}
	}else
	{
		T** tmpElements = new T*[m_capacity*2];
	
		if(!m_elements)
		{
			throw (string("Memory alloc error!"));
		}else
		{
			m_capacity *=2;
			
			memcpy(tmpElements, m_elements, Container<T>::Count()*sizeof(T*));
			
			delete[] m_elements;
			
			m_elements = tmpElements;
		}
	}
}




















#endif//__ARRAY_H__



