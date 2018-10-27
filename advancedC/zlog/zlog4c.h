
#ifndef __ZLOG4C_H__
#define __ZLOG4C_H__

#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>		/*strlen()*/


/** 
 * @brief Simple logger for C apps.
 * 
 * @author Alexander Timoshenko sashatim125@gmail.com
 * 
 * @bug Try to find one! 
 */ 

/*
 *Should NOT be called by the user !!!
 */
char GetLogLevelChar(int _logLevel);
void GetLogger(int *_logLevel, FILE **_logFile);

typedef enum
{
	LOG_TRACE = 0,	/**< Trace message usually very detailed			*/
	LOG_DEBUG,		/**< A message useful for debugging					*/
	LOG_INFO,		/**< Informative message							*/
	LOG_WARNING,	/**< Warning										*/
	LOG_ERROR,		/**< An error occurred								*/
	LOG_CRITICAL,	/**< Critical error									*/
	LOG_SEVERE,		/**< Server error requiring immediate intervention	*/
	LOG_FATAL,		/**< Fatal error signaling an emergency				*/
	LOG_NONE		/**< Used only in configuration file				*/
	
} LogLevel;


#ifndef NDEBUG

	#define PRINT_FILE_DETAILS	fprintf(logFile,"%s@%s:%d ",__func__,__FILE__,__LINE__)

#else 

	#define PRINT_FILE_DETAILS
	
#endif /*NDEBUG*/


#define ZLOG(MODULE, LOG_LEVEL, ...) \
do\
{\
	int logLevel;\
	FILE *logFile;\
	char strBuff[128];\
	time_t t;\
	struct tm *tms;\
	struct timeval tv;\
\
	GetLogger(&logLevel,&logFile);\
\
	if(LOG_LEVEL < logLevel || logLevel == LOG_NONE)\
	{\
		continue;\
	}\
\
	time(&t);\
	tms = localtime(&t);\
	\
	strftime(strBuff, 128, "%F %X", tms);\
\
	gettimeofday(&tv,NULL);\
\
	sprintf(strBuff+strlen(strBuff),".%03ld ",tv.tv_usec/1000);\
	\
	fprintf(logFile,"\n%s %u %lu %c %s ", strBuff, getpid(), pthread_self(), GetLogLevelChar(LOG_LEVEL),MODULE);\
	\
	PRINT_FILE_DETAILS;\
\
	fprintf(logFile,__VA_ARGS__);\
	\
	fprintf(logFile,"\n");\
\
} while(0)



int ZlogInit(const char* _confFileName);


#endif/*__ZLOG4C_H__*/


