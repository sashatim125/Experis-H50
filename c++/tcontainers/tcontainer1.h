
#ifndef __TCONTAINER1_T_H__
#define __TCONTAINER1_T_H__

#include <cstdlib>
#include <string>
#include <algorithm>
#include <typeinfo>

using namespace std;

template <typename T, template< class S, class Alloc = allocator<T*> >  class Container>
class TContainer_t
{
	public:
	
	TContainer_t() {}
	
	~TContainer_t() {}
	
	bool IsEmpty()const 		{return m_elements.empty();}
	
	size_t NumOfElements()const {return m_elements.size();}
	
	void Insert(T* _elem) 		{m_elements.push_back(_elem);}

	T* GetFirst()const; //throws on empty

	T* GetLast()const; //throws on empty

	T* Find(const T& _val)const; //returns pointer to element or 0 if none

	T* Remove(const T& _val) ; //throws when isn't there
	
	void RemoveAll() ; 
	
	void RemoveAndDelete(const T& _val) ; //throws when isn't there

	void RemoveAndDeleteAll() ;
	
	T* operator[](size_t _index) ; //throws if index out of bounds

	private:
	
	//copy is forbidden
	
	TContainer_t(const TContainer_t& _tc);
	
	TContainer_t& operator=(const TContainer_t& _tc);
	
	///////////////////
	
	typedef Container<T*> MyCollection;
	
	MyCollection m_elements;
	
	
	//predicate class
	
	class EqualTo
	{
		public:
		
		EqualTo(const T& _val) : m_val(_val) {}
		
		bool operator()(const T* _ptr)const {return *_ptr == m_val;}
		
		private:
		T& m_val;
	};
	
	//Delete for for_each
	void DeleteFunc(T* _elem) {delete _elem;}
	
	typedef typename MyCollection::iterator MyIter_t;



};

template <typename T, template< class S, class Alloc = allocator<T*> >  class Container>
T* TContainer_t<T,Container>::GetFirst()const
{
	if(IsEmpty())
	{
		throw (string("Empty container !"));
	}
	
	return m_elements.front();
}

template <typename T, template< class S, class Alloc = allocator<T*> >  class Container>
T* TContainer_t<T,Container>::GetLast()const
{
	if(IsEmpty())
	{
		throw (string("Empty container !"));
	}
	
	return m_elements.back();
}


template <typename T, template< class S, class Alloc = allocator<T*> >  class Container>
T* TContainer_t<T,Container>::Find(const T& _val)const
{
	MyIter_t it = fine_if(m_elements.begin(),m_elements.end(),EqualTo(_val));
	
	return (it == m_elements.end()) ? 0 : *it;
}


template <typename T, template< class S, class Alloc = allocator<T*> >  class Container>
T* TContainer_t<T,Container>::Remove(const T& _val)
{
	MyIter_t it = fine_if(m_elements.begin(),m_elements.end(),EqualTo(_val));
	
	T* res;
	
	if(it == m_elements.end())
	{
		throw (string("No such element !"));
	}
	
	res = *it;
	
	m_elements.erase(it);
	
	return res;
}

template <typename T, template< class S, class Alloc = allocator<T*> >  class Container>
void TContainer_t<T,Container>::RemoveAll()
{	
	m_elements.clear();
}


template <typename T, template< class S, class Alloc = allocator<T*> >  class Container>
void TContainer_t<T,Container>::RemoveAndDelete(const T& _val)
{
	MyIter_t it = fine_if(m_elements.begin(),m_elements.end(),EqualTo(_val));
	
	if(it == m_elements.end())
	{
		throw (string("No such element !"));
	}
	
	delete *it;
	
	m_elements.erase(it);
}

template <typename T, template< class S, class Alloc = allocator<T*> >  class Container>
void TContainer_t<T,Container>::RemoveAndDeleteAll()
{	
	for_each(m_elements.begin(),m_elements.end(),DeleteFunc);
	
	m_elements.clear();
}

template <typename T, template< class S, class Alloc = allocator<T*> >  class Container>
T* TContainer_t<T,Container>::operator[](size_t _index)
{
	if(_index >= NumOfElements())
	{
		throw (string("Index out of bounds !"));
	}

	if(typeid(MyCollection) == typeid(vector<T*>))
	{
		return (*(vector<T*>*)(&m_elements))[_index];
	}
	
	if(typeid(MyCollection) == typeid(list<T*>))
	{	
		MyIter_t it;
		for(it = m_elements.begin() ; _index > 0; --_index, ++it)
		{}
		
		return *it;
	}
}
















#endif//__TCONTAINER1_T_H__


