#ifndef __SHARED_PTR_H__
#define __SHARED_PTR_H__


#include <cstddef>
#include <algorithm>

namespace advcpp
{

class SafeRefCounter
{
	friend void swap(SafeRefCounter& _a, SafeRefCounter& _b);

public:
	SafeRefCounter();
	
	SafeRefCounter(const SafeRefCounter& _other);
	
	SafeRefCounter& operator=(const SafeRefCounter& _other);
	
	~SafeRefCounter();
	
	SafeRefCounter& operator++();
	
	SafeRefCounter& operator--();
	
	size_t Value() const;

private:
	size_t* m_countPtr;
};

//template <class T1, class R1>
//class SharedPtr;

template <class T, class R = SafeRefCounter>
class SharedPtr
{
	template <class T1, class R1>
	friend class SharedPtr;

public:

	explicit SharedPtr(T * const _ptr =NULL);
	
	SharedPtr(const SharedPtr<T,R>& _other);

	template <class U>	
	SharedPtr(const SharedPtr<U,R>& _other);

	SharedPtr<T,R>& operator=(const SharedPtr<T,R>& _other);

	template <class U>	
	SharedPtr<T,R>& operator=(const SharedPtr<U,R>& _other);
	
	~SharedPtr();

	typedef void(*PF)();
	operator PF () const;
	
	T& operator*() const;
	
	T* operator->() const;
	
	T* GetRawPtr();
	
	std::size_t GetRefCount() const;
	
	bool operator==(const SharedPtr& _other) const;
	bool operator!=(const SharedPtr& _other) const;

private:

	T* m_ptr;
	
	R mutable m_refCounter;	
};

inline
SafeRefCounter::SafeRefCounter()
:	m_countPtr(new size_t(1))
{}

inline	
SafeRefCounter::SafeRefCounter(const SafeRefCounter& _other)
:	m_countPtr(_other.m_countPtr)
{}

inline
void swap(SafeRefCounter& _a, SafeRefCounter& _b)
{
	using std::swap;
	swap(_a.m_countPtr, _b.m_countPtr);
}

inline	
SafeRefCounter& SafeRefCounter::operator=(const SafeRefCounter& _other)
{
	SafeRefCounter r(_other);
	swap(*this,r);
	
	return *this;
}

inline	
SafeRefCounter::~SafeRefCounter()
{
	if(0 == *m_countPtr)
	{
		delete m_countPtr;
	}
}

inline	
SafeRefCounter& SafeRefCounter::operator++()
{
	__sync_add_and_fetch (m_countPtr,1);
	
	return *this;
}

inline	
SafeRefCounter& SafeRefCounter::operator--()
{
	__sync_sub_and_fetch (m_countPtr,1);
	
	return *this;
}

inline	
size_t SafeRefCounter::Value() const
{
	return *m_countPtr;
}









template <class T, class R> inline
SharedPtr<T,R>::SharedPtr(T * const _ptr)
:	m_ptr(_ptr)
{}

	

template <class T, class R> inline
SharedPtr<T,R>::SharedPtr(const SharedPtr<T,R>& _other)
:	m_ptr(_other.m_ptr)
,	m_refCounter(++_other.m_refCounter)
{}


template <class T, class R>
template <class U>	inline
SharedPtr<T,R>::SharedPtr(const SharedPtr<U,R>& _other)
:	m_ptr(_other.m_ptr)
,	m_refCounter(++_other.m_refCounter)
{}


template <class T, class R> inline
SharedPtr<T,R>& SharedPtr<T,R>::operator=(const SharedPtr<T,R>& _other)
{
	if(this != &_other)
	{
		if(0 == (--m_refCounter).Value())
		{
			delete m_ptr;
		}
		m_ptr = _other.m_ptr;
		m_refCounter = ++_other.m_refCounter;
	}
	return *this;
}

template <class T, class R>
template <class U> inline
SharedPtr<T,R>& SharedPtr<T,R>::operator=(const SharedPtr<U,R>& _other)
{
	if(this != reinterpret_cast<const SharedPtr<T>*>(&_other))
	{
		if(0 == (--m_refCounter).Value())
		{
			delete m_ptr;
		}
		m_ptr = _other.m_ptr;
		m_refCounter = ++_other.m_refCounter;
	}
	return *this;
}



/*
template <class T>
template <class U>	inline
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<U>& _other)
{	
	if(this != reinterpret_cast<const SharedPtr<T>*>(&_other))
	{
		Clean();
		
		m_ptr = (const_cast<SharedPtr<U>& >(_other).GetRawPtr());
		m_refCounter = const_cast<std::size_t*>(&_other.GetRefCount());	
		++ (*m_refCounter);
	}
	return *this;
}
*/

/////////////////
/*
template<class T>
void swap(SharedPtr<T>& _a, SharedPtr<T>& _b)
{
	using std:swap;
	swap(a.m_ptr, b.m_ptr);
	swap(a.m_refCounter, b.m_refCounter);
}


template <class T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& _other)
{
	SharedPtr<T> t(_other);
	swap(*this,t);
	
	return *this;
}
*/
//////////////////////

template <class T, class R> inline
SharedPtr<T,R>::~SharedPtr()
{
	if(0 == (--m_refCounter).Value())
	{
		delete m_ptr;
	}
}


void doNothing()
{}

template <class T, class R> inline
SharedPtr<T,R>::operator PF() const
{
	return m_ptr ? doNothing : 0;
}


template <class T, class R> inline
T& SharedPtr<T,R>::operator*() const
{
	return *m_ptr;
}


template <class T, class R> inline
T* SharedPtr<T,R>::operator->() const
{
	return m_ptr;
}



template <class T, class R> inline
T* SharedPtr<T,R>::GetRawPtr()
{
	return m_ptr;
}

template <class T, class R> inline
std::size_t SharedPtr<T,R>::GetRefCount() const
{
	return m_refCounter.Value();
}

template <class T, class R> inline
bool SharedPtr<T,R>::operator==(const SharedPtr& _other) const
{
	return m_ptr == _other.m_ptr;
}


template <class T, class R> inline
bool SharedPtr<T,R>::operator!=(const SharedPtr& _other) const
{
	return !(*this == _other);
}















}//namespace advcpp
#endif //__SHARED_PTR_H__

