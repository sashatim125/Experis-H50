
/** 
 * @brief Simple logger for C apps implementation.
 * 
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 *  @bug Bugs ??? Here ??? We KILLED plenty of them on Klendathu ...
 */ 
 
#include "zlog4c.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STRING_BUFFER_SIZE 512

#define CONF_FILE_BEGIN "[#]"


static const char *logLevelNames[] =
{
	"LOG_TRACE",	/**< Trace message usually very detailed			*/
	"LOG_DEBUG",	/**< A message useful for debugging					*/
	"LOG_INFO",		/**< Informative message							*/
	"LOG_WARNING",	/**< Warning										*/
	"LOG_ERROR",	/**< An error occurred								*/
	"LOG_CRITICAL",	/**< Critical error									*/
	"LOG_SEVERE",	/**< Server error requiring immediate intervention	*/
	"LOG_FATAL",	/**< Fatal error signaling an emergency				*/
	"LOG_NONE"		/**< Used only in configuration file				*/
	
} ;

typedef struct 
{
	LogLevel m_logLevel;
	
	FILE *m_logFile;

} Logger;


static Logger theLogger;


static void CloseEverything(void);

char GetLogLevelChar(int _logLevel)
{
	return logLevelNames[_logLevel][4];
}

void GetLogger(int *_logLevel, FILE **_logFile)
{
	*_logLevel = theLogger.m_logLevel;
	
	*_logFile  = theLogger.m_logFile;
}


int ZlogInit(const char* _confFileName)
{
	FILE *confFile;	
	char strBuff[STRING_BUFFER_SIZE];
	char strBuff2[STRING_BUFFER_SIZE];
	int i;

	
	if (NULL==(confFile = fopen(_confFileName,"r")))
	{
		fprintf(stderr,"\n%s is not a valid configuration file name !\n\n",_confFileName);
		return 1;
	}
	
	fgets(strBuff,STRING_BUFFER_SIZE-1,confFile);
	if(0 != strcmp(strBuff,CONF_FILE_BEGIN "\n"))
	{
		fprintf(stderr,"\nWrong format of the configuration file - no start signature !\n");
		fclose(confFile);
		return 2;		
	}
	
	fgets(strBuff,STRING_BUFFER_SIZE-1,confFile);
	if(1 != sscanf(strBuff,"Level = %s",strBuff2))
	{
		fprintf(stderr,"\nWrong format of the configuration file - wrong level !\n");
		fclose(confFile);
		return 3;		
	}

	for(i=0 ; i <= LOG_NONE ; ++i)
	{
		if(0 == strcmp(strBuff2, logLevelNames[i]))
		{
			theLogger.m_logLevel = i;
			break;
		}
	}
	if(i > LOG_NONE)
	{
		fprintf(stderr,"\nWrong format of the configuration file - wrong level !\n");
		fclose(confFile);
		return 4;		
	}
	
	fgets(strBuff,STRING_BUFFER_SIZE-1,confFile);
	if(1 != sscanf(strBuff,"Path = %s",strBuff2))
	{
		fprintf(stderr,"\nWrong format of the configuration file  - wrong path !\n");
		fclose(confFile);
		return 5;		
	}

	strcat(strBuff2,"/");
	
	fgets(strBuff,STRING_BUFFER_SIZE-1,confFile);
	if(1 != sscanf(strBuff,"File = %s",strBuff2+strlen(strBuff2)))
	{
		fprintf(stderr,"\nWrong format of the configuration file - wrong file!\n");
		fclose(confFile);
		return 6;		
	}
	
	if(NULL==(theLogger.m_logFile = fopen(strBuff2,"a")))
	{
		fprintf(stderr,"\nWrong name or path of the log file !\n");
		fclose(confFile);
		return 7;		
	}
	
	ZLOG("Log",LOG_FATAL,"Log start");
	
	atexit(CloseEverything);
	
	fclose(confFile);
	return 0;
}


static void CloseEverything(void)
{
	ZLOG("Log",LOG_FATAL,"Log end");
	fclose(theLogger.m_logFile);
}









