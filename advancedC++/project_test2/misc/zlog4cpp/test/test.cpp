





#include <iostream>
#include <vector>
#include <string>

#include <unistd.h>
#include <pthread.h>
#include <sys/syscall.h>
//#include <sys/types.h>



#define TOSTRING(arg) std::string(#arg)


#define LOGLEVELSLIST \
	X(LOG_TRACE),	/**< Trace message usually very detailed			*/\
	Y(LOG_DEBUG),	/**< A message useful for debugging					*/\
	Y(LOG_INFO),	/**< Informative message							*/\
	Y(LOG_WARNING),	/**< Warning										*/\
	Y(LOG_ERROR),	/**< An error occurred								*/\
	Y(LOG_CRITICAL),/**< Critical error									*/\
	Y(LOG_SEVERE),	/**< Server error requiring immediate intervention	*/\
	Y(LOG_FATAL),	/**< Fatal error signaling an emergency				*/\
	Y(LOG_NONE)		/**< Used only in configuration file				*/

#define X(arg) arg=0
#define Y(arg) arg
enum LogLevels {LOGLEVELSLIST};
#undef X
#undef Y

#define X(arg) #arg
#define Y(arg) #arg
static const char *__LogLevelsNames[] = {LOGLEVELSLIST};
#undef X
#undef Y

static std::vector<std::string> LogLevelsNames(__LogLevelsNames,
	__LogLevelsNames + sizeof(__LogLevelsNames)/sizeof(char*));

void* testFunc(void* _n)
{
	std::cout<<getpid()<<" "<<(syscall(__NR_gettid)-getpid()+1)<<std::endl;

	return 0;
}

int main()
{
	pthread_t t1,t2,t3;

	std::cout<<"The string is "<< TOSTRING(myString) <<std::endl;

	for(size_t i=0; i<LogLevelsNames.size(); ++i)
	{
		std::cout<<LogLevelsNames[i]<<std::endl;
	}

	
	pthread_create(&t1,0,testFunc,0);
	pthread_create(&t2,0,testFunc,0);
	pthread_create(&t3,0,testFunc,0);
	
	pthread_join(t1,0);
	pthread_join(t2,0);
	pthread_join(t3,0);

	std::cout<<getpid()<<" "<<(syscall(__NR_gettid)-getpid()+1)<<std::endl;


	return 0;
}

























