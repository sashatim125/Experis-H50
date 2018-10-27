#ifndef __BITSET_H__
#define __BITSET_H__

#include <cstddef>
#include <algorithm>
#include <ostream>
#include <string>

using std::cout;

namespace advcpp
{

const size_t BITS = 8;

template<size_t SIZE, class T = unsigned int>
class BitSet
{
	template<size_t SIZE1, class T1>
	friend std::ostream& operator<< (std::ostream& _os, const BitSet<SIZE1,T1>& _bs);

public:

	class BitRef;

	BitSet();
	
	BitSet(const std::string& _str);
	
	BitSet(const BitSet& _other);
	
	BitSet& operator=(const BitSet& _other);

//doesn't check pos
	bool operator[](size_t _pos) const;
	
	BitRef operator[](size_t _pos);
///////////////////	
	BitSet& operator|=(const BitSet& _other);
	
	BitSet& operator&=(const BitSet& _other);
	
	BitSet& operator^=(const BitSet& _other);
	
	BitSet& Flip();
	
	bool operator==(const BitSet& _other) const;
	
	bool operator!=(const BitSet& _other) const;
	
	bool IsNone() const;
	
	bool IsAll() const;
	
	bool IsAny() const;

	BitSet& operator<<=(size_t _n);
	
	BitSet& operator>>=(size_t _n);
	
	std::string ToString() const;

private:
	static const size_t s_numOfBlocks = SIZE/(sizeof(T)*BITS)+((SIZE%(sizeof(T)*BITS))?1:0);
	
	static const size_t s_numOfBytes = s_numOfBlocks*sizeof(T);

	T m_data[s_numOfBlocks];
	
	BitRef GetBitRef(size_t _pos);
	
	void SetOffUnusedBits();
	void SetOnUnusedBits();
};

//Help class///////////////
template<size_t SIZE, class T>
class BitSet<SIZE,T>::BitRef
{
	friend class BitSet;
public:
	operator bool() const;

	BitRef& operator=(bool _val);
	BitRef& operator=(const BitRef& _br);
private:
	BitRef();

	T *m_byte;
	T  m_mask;
};



template<size_t SIZE, class T>
BitSet<SIZE,T> operator|(const BitSet<SIZE,T>& _lh,const BitSet<SIZE,T>& _rh);

template<size_t SIZE, class T>
BitSet<SIZE,T> operator&(const BitSet<SIZE,T>& _lh,const BitSet<SIZE,T>& _rh);

template<size_t SIZE, class T>
BitSet<SIZE,T> operator^(const BitSet<SIZE,T>& _lh,const BitSet<SIZE,T>& _rh);

template<size_t SIZE, class T>
BitSet<SIZE,T> operator~(const BitSet<SIZE,T>& _bs);

template<size_t SIZE, class T>
BitSet<SIZE,T> operator<<(const BitSet<SIZE,T>& _bs, size_t _n);

template<size_t SIZE, class T>
BitSet<SIZE,T> operator>>(const BitSet<SIZE,T>& _bs, size_t _n);


//////////biwise FUNCTORS ////////////////
template<class T>
struct BitwiseOr
{
	T operator()(const T& _lho, const T& _rho) {return _lho | _rho;}
};

template<class T>
struct BitwiseXor
{
	T operator()(const T& _lho, const T& _rho) {return _lho ^ _rho;}
};

template<class T>
struct BitwiseAnd
{
	T operator()(const T& _lho, const T& _rho) {return _lho & _rho;}
};

template<class T>
struct BitwiseNot
{
	T operator()(const T& _o) {return static_cast<T>(~_o);}
};

///////////////////////////////////////////////////////
///Implementations/////////////////////////////////////
///////////////////////////////////////////////////////

//BitRef//////////////

template<size_t SIZE, class T>
BitSet<SIZE,T>::BitRef::BitRef()
{}

template<size_t SIZE, class T>
BitSet<SIZE,T>::BitRef::operator bool() const
{
	return 0 != (m_mask & (*m_byte));
}

template<size_t SIZE, class T>
typename BitSet<SIZE,T>::BitRef& BitSet<SIZE,T>::BitRef::operator=(bool _val)
{
	if(_val)
	{
		(*m_byte) |= m_mask;
	}else
	{
		(*m_byte) &= static_cast<T>(~m_mask);
	}
	return *this;
}

template<size_t SIZE, class T>
typename BitSet<SIZE,T>::BitRef& BitSet<SIZE,T>::BitRef::operator=(const BitRef& _other)
{
	m_byte = _other.m_byte;
	m_mask = _other.m_mask;
}


//BitSet/////////////////

template<size_t SIZE, class T>
BitSet<SIZE,T>::BitSet()
{
	std::fill(m_data, m_data+s_numOfBlocks, 0);
}


template<size_t SIZE, class T>
BitSet<SIZE,T>::BitSet(const BitSet& _other)
{
	std::copy(_other.m_data, _other.m_data+s_numOfBlocks, this->m_data);
}


template<size_t SIZE, class T>
BitSet<SIZE,T>::BitSet(const std::string& _str)
{
	for(size_t i=0; i < SIZE; ++i)
	{
		(*this)[i] = _str[i] =='0' ? false : true;
	}
}
	
template<size_t SIZE, class T>
BitSet<SIZE,T>& BitSet<SIZE,T>::operator=(const BitSet& _other)
{
	if(this != &_other)
	{
		std::copy(_other.m_data, _other.m_data+s_numOfBlocks, this->m_data);
	}
	return *this;
}
template<size_t SIZE, class T>
void BitSet<SIZE,T>::SetOffUnusedBits()
{
	if(SIZE%(sizeof(T)*BITS))
	{
		T t =0;
		t = static_cast<T>(static_cast<T>(~t) << (sizeof(T)*BITS - SIZE%(sizeof(T)*BITS)));
		m_data[s_numOfBlocks-1] &= t;		
	}
}

template<size_t SIZE, class T>
void BitSet<SIZE,T>::SetOnUnusedBits()
{
	if(SIZE%(sizeof(T)*BITS))
	{
		T t =0;
		t = static_cast<T>(~(static_cast<T>(~t) << (sizeof(T)*BITS - SIZE%(sizeof(T)*BITS))));	
		m_data[s_numOfBlocks-1] |= t;		
	}
}

template<size_t SIZE, class T>
typename BitSet<SIZE,T>::BitRef BitSet<SIZE,T>::GetBitRef(size_t _pos)
{
	BitRef br;
	
	br.m_byte = m_data + _pos/(sizeof(T)*BITS);
	
	br.m_mask = static_cast<T>((static_cast<T>(1) << (sizeof(T)*BITS-1)) >> _pos%(sizeof(T)*BITS));
	
	return br;
}	

template<size_t SIZE, class T>
bool BitSet<SIZE,T>::operator[](size_t _pos) const
{//std::cout<<"using const[]\n";
	return (const_cast<BitSet<SIZE,T>* >(this))->GetBitRef(_pos);
}

template<size_t SIZE, class T>
typename BitSet<SIZE,T>::BitRef BitSet<SIZE,T>::operator[](size_t _pos)
{//std::cout<<"using nonconst[]\n";
	return GetBitRef(_pos);
}


template<size_t SIZE, class T>
BitSet<SIZE,T>& BitSet<SIZE,T>::operator|=(const BitSet& _other)
{
	std::transform(m_data, m_data+s_numOfBlocks, _other.m_data, m_data, BitwiseOr<T>());

	return *this;
}

template<size_t SIZE, class T>
BitSet<SIZE,T> operator|(const BitSet<SIZE,T>& _lh, const BitSet<SIZE,T>& _rh)
{
	return BitSet<SIZE,T>(_lh) |= _rh;
}


template<size_t SIZE, class T>
BitSet<SIZE,T>& BitSet<SIZE,T>::operator&=(const BitSet& _other)
{
	std::transform(m_data, m_data+s_numOfBlocks, _other.m_data, m_data, BitwiseAnd<T>());
	
	return *this;
}

template<size_t SIZE, class T>
BitSet<SIZE,T> operator&(const BitSet<SIZE,T>& _lh,const BitSet<SIZE,T>& _rh)
{
	return BitSet<SIZE,T>(_lh) &= _rh;
}

template<size_t SIZE, class T>
BitSet<SIZE,T>& BitSet<SIZE,T>::operator^=(const BitSet& _other)
{
	std::transform(m_data, m_data+s_numOfBlocks, _other.m_data, m_data, BitwiseXor<T>());
	
	return *this;
}

template<size_t SIZE, class T>
BitSet<SIZE,T> operator^(const BitSet<SIZE,T>& _lh,const BitSet<SIZE,T>& _rh)
{
	return BitSet<SIZE,T>(_lh) ^= _rh;
}


template<size_t SIZE, class T>
BitSet<SIZE,T>& BitSet<SIZE,T>::Flip()
{
	std::transform(m_data, m_data+s_numOfBlocks, m_data, BitwiseNot<T>());
	
	return *this;
}

template<size_t SIZE, class T>
BitSet<SIZE,T> operator~(const BitSet<SIZE,T>& _bs)
{
	return BitSet<SIZE,T>(_bs).Flip();
}

template<size_t SIZE, class T>
bool BitSet<SIZE,T>::operator==(const BitSet& _other) const
{
	(const_cast<BitSet<SIZE,T>* >(this))->SetOffUnusedBits();
	(const_cast<BitSet<SIZE,T>* >(&_other))->SetOffUnusedBits();
	return	std::equal(m_data, m_data+s_numOfBlocks, _other.m_data);

}

template<size_t SIZE, class T>
bool BitSet<SIZE,T>::operator!=(const BitSet& _other) const
{
	return !(this->operator==(_other));
}


template<size_t SIZE, class T>
bool BitSet<SIZE,T>::IsNone() const
{
	(const_cast<BitSet<SIZE,T>* >(this))->SetOffUnusedBits();

	T t=0;	
	return (std::count(m_data, m_data+s_numOfBlocks,t) == s_numOfBlocks);
}
	
template<size_t SIZE, class T>
bool BitSet<SIZE,T>::IsAll() const
{
	(const_cast<BitSet<SIZE,T>* >(this))->SetOnUnusedBits();

	T t=0;
	t = static_cast<T>(~t);	
	bool res = (std::count(m_data, m_data+s_numOfBlocks,t) == s_numOfBlocks);
	
	(const_cast<BitSet<SIZE,T>* >(this))->SetOffUnusedBits();
	
	return res;
}
	
	
template<size_t SIZE, class T>	
bool BitSet<SIZE,T>::IsAny() const
{
	return !IsNone();
}

template<class T>
struct ShiftRight
{
	ShiftRight(size_t _shift): m_shift(_shift) {}

	T operator()(const T& _rho, const T& _lho)
	{
		T mask = 0;
		mask = static_cast<T>(~(static_cast<T>(~mask) << (sizeof(T)*BITS - m_shift)));
		
		return static_cast<T>(((_rho >> m_shift) & mask) | (_lho << (sizeof(T)*BITS - m_shift)));
	}
private:	
	size_t m_shift;
};

template< class T>
struct ReverseIterator
{
	ReverseIterator(T *ptr): m_it(ptr){}
	
	T& operator*() const {return *m_it;}
	
	ReverseIterator& operator++() {--m_it; return *this;}
	
	bool operator!=(const ReverseIterator& _it)const {return m_it != _it.m_it;}

private:
	T* m_it;
};

template<size_t SIZE, class T>	
BitSet<SIZE,T>& BitSet<SIZE,T>::operator>>=(size_t _n)
{
	_n %= SIZE;
	
	size_t shift= _n/(sizeof(T)*BITS);
	
	if(shift)
	{
		std::copy_backward(m_data, m_data+s_numOfBlocks-shift, m_data+s_numOfBlocks);
		std::fill(m_data, m_data+shift, 0);
	}
	
	_n -= shift*sizeof(T)*BITS;

	ReverseIterator<T>	it1 = m_data + s_numOfBlocks -1,
						it2 = m_data + shift,
						it3 = m_data + s_numOfBlocks -2;

	std::transform(it1, it2, it3, it1, ShiftRight<T>(_n));

	*it2 = ShiftRight<T>(_n).operator()(*it2,0);
	
	SetOffUnusedBits();
	
	return *this;	
}

template<size_t SIZE, class T>	
BitSet<SIZE,T> operator>>(const BitSet<SIZE,T>& _bs, size_t _n)
{

	return BitSet<SIZE,T>(_bs) >>= _n;
}


template<class T>
struct ShiftLeft
{
	ShiftLeft(size_t _shift): m_shift(_shift) {}

	T operator()(const T& _lho, const T& _rho)
	{		
		return static_cast<T>((_lho << m_shift) | (_rho >> (sizeof(T)*BITS - m_shift)));
	}
private:	
	size_t m_shift;
};


template<size_t SIZE, class T>	
BitSet<SIZE,T>& BitSet<SIZE,T>::operator<<=(size_t _n)
{
	//TODO if (_n >= SIZE) ...

	_n %= SIZE;
	
	size_t shift= _n/(sizeof(T)*BITS);
	
	if(shift)
	{
		std::copy(m_data+shift, m_data+s_numOfBlocks, m_data);
		std::fill(m_data+s_numOfBlocks-shift, m_data+s_numOfBlocks, 0);
	}
	
	_n -= shift*sizeof(T)*BITS;

	T	*it1 = m_data,
		*it2 = m_data + s_numOfBlocks - shift -1,
		*it3 = m_data + 1;

	std::transform(it1, it2, it3, it1, ShiftLeft<T>(_n));

	*it2 = ShiftLeft<T>(_n).operator()(*it2,0);
	
	SetOffUnusedBits();
	
	return *this;	
}


template<size_t SIZE, class T>	
BitSet<SIZE,T> operator<<(const BitSet<SIZE,T>& _bs, size_t _n)
{

	return BitSet<SIZE,T>(_bs) <<= _n;
}



template<size_t SIZE, class T>	
std::string BitSet<SIZE,T>::ToString() const
{
	std::string s;
	
	for(size_t i=0; i<SIZE; ++i)
	{
		s.push_back((*this)[i]?'1':'0');
	}
	
	return s;
}



template<size_t SIZE, class T>	
std::ostream& operator<< (std::ostream& _os, const BitSet<SIZE,T>& _bs)
{
	for(size_t i=0; i<SIZE; ++i)
	{
		std::cout<<(_bs[i]?1:0);
	}
	std::cout<<std::endl;
	
	return _os;
}


















}//namespace


#endif//__BITSET_H__

