#ifndef __STREE_T__
#define __STREE_T__

#include <vector>

#include "building_t.h"

using namespace std;

template<class T1,class T2>
class Street_t
{
	public:
	
				Street_t();

				Street_t(const Street_t<T1, T2>& _s);
	
	Street_t<T1, T2>& operator=(const Street_t<T1, T2>& _s);
	
	const T1&	GetStreetID() const;
	
	void 		SetStreetID(const T1& _id);
	
	void 		AddBuilding2Street(const Building_t<T2>& _b);
	
	const Building_t<T2>& GetBuilding(const T2& _bID) const;
	
	
	
	

	private:
	
	T1 m_ID;
	
	vector<Building_t<T2> > m_buildings;

};


template<class T1,class T2>
	Street_t<T1, T2>::Street_t() {}
	
template<class T1,class T2>	
	Street_t<T1, T2>::Street_t(const Street_t<T1, T2>& _s) :
		m_ID(_s.m_ID),m_buildings(_s.m_buildings)  {}

template<class T1,class T2>	
	Street_t<T1, T2>& Street_t<T1, T2>::operator=(const Street_t<T1, T2>& _s)
	{
		if(&_s != this)
		{
			m_ID = _s.m_ID;
			m_buildings = _s.m_buildings;
		}
		
		return *this;
	}

template<class T1,class T2>	
	const T1& Street_t<T1, T2>::GetStreetID() const
	{
		return m_ID;
	}

template<class T1,class T2>
	void Street_t<T1, T2>::SetStreetID(const T1& _id)
	{
		m_ID = _id;
	}
	
template<class T1,class T2>
	void Street_t<T1, T2>::AddBuilding2Street(const Building_t<T2>& _b)
	{
		m_buildings.push_back(_b);
	}
	
template<class T1,class T2>
	const Building_t<T2>& Street_t<T1, T2>::GetBuilding(const T2& _bID) const
	{
		size_t i;
		size_t size = m_buildings.size();
		
		for(i=0 ; i< size ; ++i)
		{
			if (_bID == m_buildings[i].GetBuildingID())
			{
				break;
			}
		}
		
		if(i == size)
		{
			throw "No such building";
		}
		
		return m_buildings[i];
	}




















#endif //__STREE_T__

