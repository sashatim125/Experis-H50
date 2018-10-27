
/** 
 *  @file pipeComm.h
 *  @brief Implementation of the file transfer through pipe functions
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */

#define _POSIX_C_SOURCE 199309L

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include "pipeComm.h"

#include "pipeHeader.h"



static ssize_t streamData(int _sourceFD, int _destFD, size_t _dataSize)
{
	ssize_t totReadedSize;
	ssize_t totWrittenSize;
	ssize_t readedSize;
	ssize_t writtenSize;
	ssize_t bytesLeft;
	char buffer[BUFFER_SIZE];
	
	for(totReadedSize = totWrittenSize = 0 , bytesLeft = (ssize_t)_dataSize;
		0 < bytesLeft ; bytesLeft -= readedSize )
	{
		if (0 >= (readedSize = read(_sourceFD, buffer,
			(size_t)bytesLeft < sizeof(buffer) ? (size_t)bytesLeft : sizeof(buffer))))
		{
			return -1;
		}
		
		totReadedSize+=readedSize;
		
		if(readedSize > (writtenSize = write(_destFD,
			buffer, (size_t)readedSize)))
		{
			return -2;
		}
		
		totWrittenSize+=writtenSize;	
	}
	
	if(totReadedSize > totWrittenSize)
	{
		return -3;
	}

	return totWrittenSize;
}


static int prepareToSend(const char* _fileName, const char* _pipeName, int* _sourceFD, int* _pipeFD, size_t* _fileSize)
{

	size_t headerSize;
	struct stat statbuf;
	char buffer[BUFFER_SIZE];
	
	if(-1 == (*_sourceFD = open(_fileName,O_RDONLY)))
    {
    	perror("Source file open error");
    	return -1;
    }
    if(-1 == fstat(*_sourceFD,&statbuf))
    {
    	perror("Status checking error");
    	close(*_sourceFD);
    	return -2;
    }
    
    if(0 != mkfifo(_pipeName,S_IRUSR|S_IWUSR))
    {
    	if(EEXIST != errno)
    	{
    		perror("Pipe creation error");
    		close(*_sourceFD);
    		return -3;
    	}
    }
    *_fileSize = (size_t)statbuf.st_size;
    
	if (0== (headerSize = createHeader(buffer, _fileName, *_fileSize)))
	{
		perror("Header creation error");
		close(*_sourceFD);
    	return -4;
	}
	
	if(-1 == (*_pipeFD = open(_pipeName,O_WRONLY)))
    {
    	perror("Pipe for write open error");
		close(*_sourceFD);
    	return -5;
    }
    
    if(-1 == write(*_pipeFD,&headerSize,sizeof(size_t)))
	{
		perror("Header size writing error");
		close(*_pipeFD);
		close(*_sourceFD);
		return -6;
	}
	
	if(headerSize > write(*_pipeFD,buffer,headerSize))
	{
		perror("Header writing error");
		close(*_pipeFD);
		close(*_sourceFD);
		return -7;
	}

	return 0;
}


int sendFileToPipe(const char* _fileName, const char* _pipeName)
{
	int sourceFD, pipeFD;
	size_t fileSize;
	
	if(0 != prepareToSend(_fileName, _pipeName, &sourceFD, &pipeFD, &fileSize))
	{
		return -1;
	}
	
	if((ssize_t)fileSize > streamData(sourceFD, pipeFD, fileSize))
	{
		perror("File streaming to pipe error");
		close(pipeFD);
		close(sourceFD);
		return -2;
	}
	
	close(pipeFD);
	close(sourceFD);
	
	return 0;
}


static int prepareToReceive(const char* _pipeName, int* _pipeFD, int* _destFD, size_t* _fileSize)
{
	char fileName[BUFFER_SIZE];
	size_t headerSize;
	char buffer[BUFFER_SIZE];
	
	if(-1 == (*_pipeFD = open(_pipeName,O_RDONLY)))
    {
    	perror("Pipe open for read error");
    	return -1;
    }
    
    if(0 >= read(*_pipeFD,&headerSize,sizeof(size_t)))
	{
		perror("Header size reading error");
		close(*_pipeFD);
		return -2;
	}
    
    if(headerSize > read(*_pipeFD,buffer,headerSize))
	{
		perror("Header reading error");
		close(*_pipeFD);
		return -3;
	}
	
	if(0 != readHeader(buffer,fileName,_fileSize))
	{
		perror("Wrong header error");
		close(*_pipeFD);
		return -4;
	}
    
    strcat(fileName,NEW_FILE);
    if(-1 == (*_destFD = open(fileName,O_CREAT|O_WRONLY|O_TRUNC,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)))
    {
    	perror("Destination file create/open error");
    	close(*_pipeFD);
    	return -5;
    }
    
    return 0;
}


int receiveFileFromPipe(const char* _pipeName)
{
	int destFD, pipeFD;
	size_t fileSize;
	
	if(0 !=	prepareToReceive(_pipeName, &pipeFD, &destFD, &fileSize))
	{
		return -1;
	}

	if((ssize_t)fileSize > streamData(pipeFD, destFD, fileSize))
	{
		perror("File streaming from pipe error");
		close(pipeFD);
		close(destFD);
		return -2;
	}
		
	close(pipeFD);
	close(destFD);
	
	return 0;
}




