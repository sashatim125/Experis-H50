#ifndef __SPECIALSTRING_H__
#define __SPECIALSTRING_H__


namespace advcpp
{

//interface
class SpecialString
{
public:
//interface
class StringIterator
{
public:
	virtual
	~StringIterator()
	{}

	virtual
	void FirstChar() =0;
	virtual
	void Next() =0;
	virtual
	bool HasNext()  =0;
	virtual
	char GetChar()  =0;
};

	virtual
	~SpecialString()
	{}
	
	virtual
	SpecialString::StringIterator* GetIter() =0;
	virtual
	void Print() =0;
};

}//namespace advcpp

#endif//__SPECIALSTRING_H__

