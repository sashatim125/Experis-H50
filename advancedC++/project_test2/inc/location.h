#ifndef __LOCATION_H__
#define __LOCATION_H__

// 
//  @file location.h
//  @brief Location
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//

#include <string>
#include <iostream>

namespace advcpp
{

struct Location
{
	inline
	friend std::ostream& operator<<(std::ostream& _os, const Location& _loc);

	inline
	Location(const std::string& _floor, const std::string& _room);
	
	virtual
	~Location() {}

	virtual inline
	const std::string& GetFloor() const;

	virtual inline
	const std::string& GetRoom() const;


private:

	std::string m_floor;	
	std::string m_room;
};

inline
std::ostream& operator<<(std::ostream& _os, const Location& _loc)
{
	_os<<"floor: "<<_loc.m_floor<<", room: "<<_loc.m_room<<" ";
	return _os;
}

}

using namespace advcpp;

inline
Location::Location(const std::string& _floor, const std::string& _room)
:	m_floor(_floor)
,	m_room(_room)
{}

inline
const std::string& Location::GetFloor() const
{
	return m_floor;
}

inline
const std::string& Location::GetRoom() const
{
	return m_room;
}








#endif //__LOCATION_H__
