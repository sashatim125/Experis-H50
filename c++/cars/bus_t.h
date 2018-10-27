
#ifndef __BUS_T_H__
#define __BUS_T_H__

#include "car_t.h"


class Bus_t : public Car_t
{
	public:
	
	~Bus_t();
	
	Bus_t(unsigned int _capacity);
	
	Bus_t(const Bus_t& _bus);
	
	Bus_t& operator=(const Bus_t& _bus);
	
	void SetNumOfSeats(unsigned int _numOfSeats);
	
	unsigned int GetNumOfSeats() const;
	
	void SetLineNum(unsigned int _lineNum);
	
	unsigned int GetLineNum() const;

	private:
	
	unsigned int m_numOfSeats;
	
	unsigned int m_lineNum;
	
	static const unsigned int s_defaultNumOfSeats;
	
	static const unsigned int s_defaultLineNum;
	
	static const char* s_busName;
	
	static const char* s_GearType;

};

#endif //__BUS_T_H__



