
#include <vector>
#include <string>
#include <pthread.h>
#include <unistd.h>

void* DoNothing(void* _d)
{
	sleep(3600);
	return 0;
}


int main()
{
	pthread_t t;
	
	pthread_create(&t,0,DoNothing,0);

	sleep(5);
	
	pthread_cancel(t);

	pthread_join(t,0);




	return 0;
}
