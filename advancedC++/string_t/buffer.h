
#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <cstddef>
#include <cstring>
#include <stdexcept> 

namespace advcpp
{

template <typename T>
class Buffer
{
	static const std::size_t s_initCapacity = 0;
public:

	Buffer(std::size_t _capacity = s_initCapacity);
	
	Buffer(const Buffer& _other);
	
	~Buffer();
	
	Buffer& operator=(const Buffer& _other);
	
	const T* Array() const;
	
	T* Array();
	
	void PushBack(const T& _item);
	
	void CopyRange(const Buffer& _other, std::size_t _left, std::size_t _right);
	
	void Size() const;

	void Capacity() const;

	void Resize(std::size_t _newCapacity);

//doesn't check index
	T& operator[](std::size_t _index);
	
	const T& operator[](std::size_t _index) const;
	
//checks index and throws std::out_of_range
	T& operator()(std::size_t _index);
	
	const T& operator()(std::size_t _index) const;

private:
	
	std::size_t m_size;
	
	std::size_t m_capacity;
	
	T* m_data;
};


template <typename T>
Buffer<T>::Buffer(std::size_t _capacity)
:	m_size(0)
,	m_capacity(_capacity)
,	m_data(new T[m_capacity])
{}

template <typename T>	
Buffer<T>::Buffer(const Buffer& _other)
try
:	m_size(_other.m_size)
,	m_capacity(s_initCapacity > _other.m_size ? s_initCapacity : _other.m_size)
,	m_data(new T[m_capacity])
{	
	for(std::size_t i=0; i < m_size; ++i)
	{
		new (m_data+i) T((_other.m_data)[i]);
	}
}
catch(std::exception)
{
	delete[] m_data;
}

template <typename T>	
Buffer<T>::~Buffer()
{
	delete[] m_data;
}

template <typename T>
Buffer<T>& Buffer<T>::operator=(const Buffer& _other)
{
	if(this != &_other)//??? should use it ???
	{
		m_size = _other.m_size;
		m_capacity = (s_initCapacity > _other.m_size ? s_initCapacity : _other.m_size);

		delete[] m_data;
		m_data = new T[m_capacity];
		
		for(std::size_t i=0; i < m_size; ++i)
		{
			new (m_data+i) T((_other.m_data)[i]);
		}	
	}
}

template <typename T>
const T* Buffer<T>Array() const
{
	return m_data;
}
	

template <typename T>
T* Buffer<T>Array()
{
	return m_data;
}


template <typename T>
void Buffer<T>::PushBack(const T& _item)
{
	if(m_size == m_capacity)
	{
		Resize(m_capacity*2);	
	}
	operator[](m_size++) = _item;
}
	
template <typename T>
void Buffer<T>::CopyRange(const Buffer& _other, std::size_t _left, std::size_t _right)
{
	if(_left >= _right || _right > _other.m_size())
	{
		throw std::out_of_range();
	}
	
	std::size_t len = _right - _left + 1;
	
	if(this == &_other)
	{
		memmove(m_data, m_data+_left, len*sizeof(T));
		m_size = len;
		return;
	}
	
	if(len > m_capacity)
	{
		delete[] m_data;
		m_capacity = len;
		m_data = new T[m_capacity];			
	}
	
//	memcpy(m_data, m_data+_left, len*sizeof(T));
	m_size = len;	
}
	
template <typename T>
void Buffer<T>::Size() const
{
	return m_size;
}
	
template <typename T>
void Buffer<T>::Capacity() const
{
	return m_capacity;
}
	
template <typename T>
void Buffer<T>::Resize(std::size_t _newCapacity)
{
	m_capacity = _newCapacity;
	T* temp = new T[m_capacity];
	try
		{	
		for(std::size_t i=0; i < m_size; ++i)
		{
			new (temp+i) T(m_data[i]);
		}
	}catch(std::exception)
	{
		delete[]
	}
	delete[] m_data;
	m_data = temp;			
}

//doesn't check index
template <typename T>
T& Buffer<T>::operator[](std::size_t _index)
{
	return m_data[_index];
}
	
template <typename T>	
const T& Buffer<T>::operator[](std::size_t _index) const
{
	return m_data[_index];
}

	
//checks index and throws std::out_of_range
template <typename T>
T& Buffer<T>::operator()(std::size_t _index)
{
	if(_index >= m_size)
	{
		throw std::out_of_range();
	}
	return m_data[_index];
}

template <typename T>
const T& Buffer<T>::operator()(std::size_t _index) const
{
	if(_index >= m_size)
	{
		throw std::out_of_range();
	}
	return m_data[_index];
}



}//namepace advcpp

#endif //__BUFFER_H__


