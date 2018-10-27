
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

/** 
 *  @file  myString.c
 *  @brief API for various string functions
 *	
 *  @details  See the functions description
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 *  @bug NONE! 
 */
 
#define ASSERT(exp) \
	do\
	{\
		if(!(exp))\
		{\
			fprintf(stderr,"\nI am in file %s, line %d and expression %s.\n",__FILE__,__LINE__,#exp);\
			fprintf(stderr,"My PID is %u.\n\n",getpid());\
			abort();\
		}\
	}\
	while(0)



size_t myStrLen(const char *_str)
{
	size_t len = 0;
	
	if(NULL==_str)
	{
		return 0;
	}

	while(*(_str+len) != '\0')
	{
		++len;
	}

	return len;
}


 
char* StrCpyIt(char *_str1, const char *_str2)
{
/*	if((NULL==_str1)||(NULL==_str2))
	{
		return NULL;
	}
*/
	ASSERT((NULL!=_str1)&&(NULL!=_str2));

	while ('\0' != (*_str1++ = *_str2++))
	{
		;
	}

	return _str1;
}

char* StrCpyRec(char *_str1, const char *_str2)
{/*
	if((NULL==_str1)||(NULL==_str2))
	{
		return NULL;
	}
*/
	*_str1 = *_str2;
	
	if(*_str2 != '\0')
	{
		StrCpyRec(_str1+1,_str2+1);
	}
	
	return _str1;
}


char* StrNCpyIt(char *_str1, size_t _n, const char *_str2)
{
	if((NULL==_str1)||(NULL==_str2))
	{
		return NULL;
	}

	while ((_n-- > 0)&&('\0' != (*_str1++ = *_str2++)))
	{
		;
	}


	return _str1;
}


char* StrNCpyRec(char *_str1, size_t _n, const char *_str2)
{/*
	if((NULL==_str1)||(NULL==_str2))
	{
		return NULL;
	}
*/	
	if(0 == _n)
	{
		return _str1;
	}

	if(_str2 == '\0')
	{
		 *_str1='\0';
		 return _str1;
	}

	StrNCpyRec(_str1+1,_n-1,_str2+1);
	
	*_str1 = *_str2;
	
	return _str1;
}


int StrCmpIt(const char *_str1, const char *_str2)
{

	if((NULL==_str1)||(NULL==_str2))
	{
		return -1;
	}

	while ((*_str1 == *_str2)&&(*_str1!='\0'))
	{
		++_str1;
		++_str2;		
	} ;

	return (*_str1 - *_str2);
}


int StrCmpRec(const char *_str1, const char *_str2)
{/*
	if((NULL==_str1)||(NULL==_str2))
	{
		return -1;
	}
*/
	if((*_str1 == '\0')||(*_str1 != *_str2))
	{
		return (*_str1 - *_str2);
	}
	
	return StrCmpRec(_str1+1,_str2+1);
}


char* StrCat(char *_str1, const char *_str2)
{

	if((NULL==_str1)||(NULL==_str2))
	{
		return NULL;
	}

	
	StrCpyIt(_str1+myStrLen(_str1),_str2);

	return _str1;
}


char* StrStr(const char *_str1, const char *_str2)
{

	size_t len1, len2, i, j;
	
	len1 = myStrLen(_str1);
	len2 = myStrLen(_str2);

	if((NULL==_str1)||(NULL==_str2)||(len2 > len1))
	{
		return NULL;
	}
	
	for(i=0 ; i < len1-len2 ; ++i)
	{

		for (j=0 ; j < len2 ; ++j)
		{
			if(_str1[i+j] != _str2[j])
			{
				break;
			}
		}
		if(j == len2)
		{
			return (char*)((void*)(_str1+i));
		}

	}
	
	return NULL;
}




















