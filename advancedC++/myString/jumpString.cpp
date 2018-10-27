

#include "jumpString.h"


void JumpString::StringIterator::Jump()
{
	for (unsigned i = 0; i < m_jump; ++i)
	{
		GetMyIter()->Next();
	}
}


void JumpString::StringIterator::FirstChar()
{
	GetMyIter()->FirstChar();
}
	

void JumpString::StringIterator::Next()
{
	Jump();
}
	

bool JumpString::StringIterator::HasNext()
{/*
	JumpString::StringIterator it = *GetMyIter();
	if(1 <= m_jump)
	{
		for (unsigned i = 0,jump = m_jump-1; i < jump; ++i)
		{
			it->Next();
		}
		return it->HasNext();
	}
*/	
	return GetMyIter()->HasNext();

}
	









