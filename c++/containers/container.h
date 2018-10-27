
#ifndef __CONTAINER_H__
#define __CONTAINER_H__

#include <cstdlib>

template <class T>
class Container
{
	public:

	Container(): m_numOfElem(0) {};
	
	Container(const Container& _cont): m_numOfElem(_cont.m_numOfElem) {};
	
	virtual ~Container() =0;
	
	Container& operator=(const Container& _cont);
	
	virtual
	void Append(const T* _elem, size_t _index) =0; //throws on index out of bounds
	
	virtual
	void Prepend(const T* _elem, size_t _index) =0;//throws on index out of bounds
	

	bool Contains (const T& _val) const ;
	
	size_t Count() const ;
	
	virtual
	const T* Find(const T& _val) const =0; //return 0 if not found
	
	virtual
	size_t Index(const T& _val) const =0; //throws when isn't there
	
	virtual
	void Insert(const T* _elem) =0;
	
	bool IsEmpty();
	
	virtual
	T* Remove(const T& _val) =0; //throws when isn't there
	
	virtual
	void RemoveAll() =0; 
	
	virtual
	void RemoveAndDelete(const T& _val) =0; //throws when isn't there
	
	virtual
	void RemoveAndDeleteAll() =0;
	
	
	protected:

	void SetNumOfElem(size_t n);



	private :

	size_t m_numOfElem;


};

template <class T>
Container<T>::~Container() 
{}

template <class T>
Container<T>& Container<T>::operator=(const Container& _cont)
{
	if(&_cont != this)
	{
		m_numOfElem = _cont.m_numOfElem;
	}
	
	return *this;
}

template <class T>
bool Container<T>::Contains (const T& _val) const 
{
	return (Find(_val) != 0);
}


template <class T>
size_t Container<T>::Count() const
{
	return m_numOfElem;
}

template <class T>
void Container<T>::SetNumOfElem(size_t n)
{
	m_numOfElem = n;
}

template <class T>
bool Container<T>::IsEmpty()
{
	return (m_numOfElem == 0);
}











#endif//__CONTAINER_H__


