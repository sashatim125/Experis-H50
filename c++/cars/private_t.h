
#ifndef __PRIVATE_T_H__
#define __PRIVATE_T_H__

#include "car_t.h"


class Private_t : public Car_t
{
	public:
	
	~Private_t();
	
	Private_t(unsigned int _capacity);
	
	Private_t(const Private_t& _priv);
	
	Private_t& operator=(const Private_t& _priv);
	
	void Accelerate();
	
	void ReduceSpeed();
	
	unsigned int GetSpeed() const;

	private:
	
	unsigned int m_speed;
	
	static const unsigned int s_initialSpeed;
	
	static const unsigned int s_speedStep;
	
	static const char* s_privateName;
	
	static const char* s_GearType;

};

#endif //__PRIVATE_T_H__



