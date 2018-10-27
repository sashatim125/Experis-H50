


/** 
 *  @file pipeHeader.c
 *  @brief Implementation of the pipe connection protocol functions
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */


#include "pipeHeader.h"

#include <string.h>

#ifndef MAGIC_NUMBER
#define MAGIC_NUMBER 0xabcdef
#endif /*MAGIC_NUMBER*/


typedef struct Header
{
	int m_magicNum;
	
	size_t m_headerSize;
	
	size_t m_fileSize;
	
	char m_fileName[1];

} Header;


size_t createHeader(void* _buffer, const char* _fileName,size_t _fileSize)
{
	Header *headerPtr;
	
	if(NULL==_buffer || NULL==_fileName)
	{
		return 0;
	}
	
	headerPtr = (Header*)_buffer;
	
	strcpy(headerPtr->m_fileName,_fileName);
	
	headerPtr->m_fileSize = _fileSize;
	
	headerPtr->m_headerSize = sizeof(Header)+strlen(headerPtr->m_fileName);
	
	headerPtr->m_magicNum = MAGIC_NUMBER;

	return headerPtr->m_headerSize;
}





int readHeader(const void* _buffer, char* _fileName, size_t* _fileSize)
{
	const Header *headerPtr;
	
	if(NULL==_buffer || NULL==_fileName)
	{
		return -1;
	}
	
	headerPtr = (Header*)_buffer;
	
	if(MAGIC_NUMBER != headerPtr->m_magicNum)
	{
		return -2;
	}
	
	if(headerPtr->m_headerSize != sizeof(Header)+strlen(headerPtr->m_fileName))
	{
		return -3;
	}
	
	*_fileSize = headerPtr->m_fileSize;
	
	strcpy(_fileName,headerPtr->m_fileName);
	
	
	return 0;
}
















