
#include <sstream>
#include <algorithm>

#include "bignumber.h"

//public:
	
BigNumber::BigNumber() :
	m_str("0"), m_isNeg(false)
{}
	
BigNumber::BigNumber(const char * _str)
{
	if(_str[0] == '-')
	{
		m_isNeg = true;
		++_str;
	}else
	{
		m_isNeg = false;
	}
	
	m_str = _str;	
}
	
BigNumber::BigNumber(int _num)
{
	ostringstream oss;
	
	if(_num < 0)
	{
		m_isNeg = true;
		_num*= -1;
	}else
	{
		m_isNeg = false;
	}
	
	oss<<_num;
	
	m_str = oss.str();	
}
	
BigNumber::BigNumber(const BigNumber& _num) :
	m_str(_num.m_str), m_isNeg(_num.m_isNeg)
{}
		
BigNumber& BigNumber::operator=(const BigNumber& _num)
{
	if(&_num != this)
	{
		m_str = _num.m_str;
		m_isNeg = _num.m_isNeg;
	}
	
	return *this;
}
	
BigNumber& BigNumber::operator=(int _num)
{
	ostringstream oss;
	
	if(_num < 0)
	{
		m_isNeg = true;
		_num*= -1;
	}
	
	oss<<_num;
	
	m_str = oss.str();
	
	return *this;
}


size_t BigNumber::PadWithZeros(const string& _str1, const string& _str2, string& _padStr1, string& _pasStr2)const
{
	size_t len1 = _str1.length();
	size_t len2 = _str2.length();
	
	size_t maxlen = (len1 > len2) ? len1 : len2;
	
	_padStr1 = string(maxlen - len1,'0')+_str1;
	_pasStr2 = string(maxlen - len2,'0')+_str2;
	
	return maxlen;

}
	
bool BigNumber::operator==(const BigNumber& _num) const
{	
	string _padStr1;
	string _padStr2;

	if(m_isNeg != _num.m_isNeg)
	{
		return false;
	}
	
	PadWithZeros(m_str,_num.m_str,_padStr1,_padStr2);
	return (_padStr1 == _padStr2);
}

	
bool BigNumber::operator<(const BigNumber& _num) const
{
	string _padStr1;
	string _padStr2;

	if(m_isNeg && !_num.m_isNeg)
	{
		return true;
	}
	
	if(!m_isNeg && _num.m_isNeg)
	{
		return false;
	}
	
	PadWithZeros(m_str,_num.m_str,_padStr1,_padStr2);
	return (_padStr1 < _padStr2);
}
	
bool BigNumber::operator>(const BigNumber& _num) const
{	
	string _padStr1;
	string _padStr2;

	if(m_isNeg && !_num.m_isNeg)
	{
		return false;
	}
	
	if(!m_isNeg && _num.m_isNeg)
	{
		return true;
	}
	
	PadWithZeros(m_str,_num.m_str,_padStr1,_padStr2);
	return (_padStr1 > _padStr2);
}


	
BigNumber BigNumber::operator+(const BigNumber& _num) const
{	
	string _padStr1;
	string _padStr2;
	int carry;
	long len, i;
	int res;
	
	if(_num == 0)
	{
		return *this;
	}
	if(*this == 0)
	{
		return _num;
	}
	
	len = (long)PadWithZeros(m_str,_num.m_str,_padStr1,_padStr2);
	string resStr(len+1,0);
	
	for(carry = 0, i=len-1; i >= 0 ; --i)
	{
		res = _padStr1[i] + _padStr2[i] + carry - 2*'0';
		resStr[i+1] =(char)(res%10 + '0');
		carry = res/10;
	}
	resStr[0] =(char)(carry + '0');
	
	return (carry == 0) ? resStr.c_str()+1 : resStr.c_str();
}



BigNumber BigNumber::operator-(const BigNumber& _num) const
{	
	string _padStr1;
	string _padStr2;
	int carry;
	long len, i;
	int res;
	bool isResNeg;
	
	if(_num == 0)
	{
		return *this;
	}
	if(*this == 0)
	{
		BigNumber n(_num);
		n.m_isNeg = true;
		return n;
	}
	if(*this == _num)
	{
		return "0";
	}
	
	const BigNumber *n1,*n2;
	if(*this > _num)
	{
		n1 = this;
		n2 = &_num;
		isResNeg = false;
	}else
	{
		n1 = &_num;
		n2 = this;
		isResNeg = true;
	}
	
	len = (long)PadWithZeros(n1->m_str,n2->m_str,_padStr1,_padStr2);
	string resStr(len,0);
	
	for(carry = 0, i=len-1; i >= 0 ; --i)
	{
		res = _padStr1[i] - _padStr2[i] - carry ;
		if(res < 0)
		{
			carry = 1;
			res += 10;
		}else
		{
			carry = 0;
		}
		resStr[i] =(char)(res + '0');
	}
	
	int padZeros;
	for(padZeros = 0; resStr[padZeros] == '0' ; ++padZeros)
	{}
	BigNumber n(resStr.c_str()+padZeros);
	n.m_isNeg = isResNeg;
	return n;
}


//overloaded IO operators

ostream& operator<<(ostream& os, const BigNumber& _num)
{
	if(_num.m_isNeg)
	{
		os<<"-";
	}
	os << _num.m_str;
		
	return os;
}
	
istream& operator>>(istream& is, BigNumber& _num)
{
	string s;
		
	is >> s;
	
	_num = s.c_str();	

	return is;
}




