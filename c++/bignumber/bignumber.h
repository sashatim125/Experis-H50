
#ifndef __BIGNUMBER_H__
#define __BIGNUMBER_H__

#include <iostream>
#include <string>

using namespace std;

class BigNumber
{
	public:
	
	//overloaded IO operators
	friend
	ostream& operator<<(ostream& os, const BigNumber& _num);
		
	friend
	istream& operator>>(istream& is, BigNumber& _num);
	
	BigNumber();
	
	BigNumber(const char * _str);//doesn't check input validity
	
	BigNumber(int _num);
	
	BigNumber(const BigNumber& _num);
	
	~BigNumber() {}
	
	
	BigNumber& operator=(const BigNumber& _num);
	
	BigNumber& operator=(int _num);
	
	bool operator==(const BigNumber& _num) const;
	
	bool operator<(const BigNumber& _num) const;
	
	bool operator>(const BigNumber& _num) const;
	
	//work on positive numbers only !
	BigNumber operator+(const BigNumber& _num) const;
	
	BigNumber operator-(const BigNumber& _num) const;
	
	private:
	
	string m_str;
	
	bool m_isNeg;
	
	size_t PadWithZeros(const string& _str1, const string& _str2, string& _padStr1, string& _pasStr2)const;

};












#endif //__BIGNUMBER_H__


