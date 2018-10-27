
#include <iostream>
#include "singleton.h"

using advcpp::Singleton;


class SingletonExample : public Singleton<SingletonExample>
{
	friend Singleton<SingletonExample>;

public:
	void SayHello() {std::cout<<"Hello, World !!!\n";}
	
protected:
	SingletonExample() {}
	~SingletonExample() {}
private:
	SingletonExample(const SingletonExample& _other);
	SingletonExample& operator=(const SingletonExample& _other);
};





int main()
{
	SingletonExample& se = SingletonExample::Instance();
	
	se.SayHello();

	return 0;
}
