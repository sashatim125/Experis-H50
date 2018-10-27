
#include <cctype>

#include "toUpperString.h"


char ToUpperString::StringIterator::GetChar() 
{
	return (char)toupper(GetMyIter()->GetChar());
}






