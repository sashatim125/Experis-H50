#ifndef __DEPARTMENTREPORTER_H__
#define __DEPARTMENTREPORTER_H__

#include "department.h"

namespace advcpp
{

class DepartmentReporter
{
public:
	inline
	DepartmentReporter(const Department& _dep);
	
	virtual
	~DepartmentReporter() {}
	
	virtual
	void Report() =0;

protected:
	inline
	const Department& GetDep() const;
	
	inline
	const DepartmentAccessor& GetDepAccess() const;

private:
	const Department& m_dep;
	const DepartmentAccessor m_da;
};


class DepartmentReporterFull : public DepartmentReporter
{
public:

	inline
	DepartmentReporterFull(const Department& _dep);

	virtual
	void Report();
};


class DepartmentReporterShort : public DepartmentReporter
{
public:

	inline
	DepartmentReporterShort(const Department& _dep);

	virtual
	void Report();
};


class DepartmentReporterSummary : public DepartmentReporter
{
public:

	inline
	DepartmentReporterSummary(const Department& _dep);

	virtual
	void Report();
};


}


inline
DepartmentReporter::DepartmentReporter(const Department& _dep) :
	m_dep(_dep), m_da(_dep)
{}

inline
DepartmentReporterFull::DepartmentReporterFull(const Department& _dep) :
	DepartmentReporter(_dep)
{}

inline
DepartmentReporterShort::DepartmentReporterShort(const Department& _dep) :
	DepartmentReporter(_dep)
{}

inline
DepartmentReporterSummary::DepartmentReporterSummary(const Department& _dep) :
	DepartmentReporter(_dep)
{}

inline
const Department& DepartmentReporter::GetDep() const
{
	return m_dep;
}
	
inline
const DepartmentAccessor& DepartmentReporter::GetDepAccess() const
{
	return m_da;
}






#endif//__DEPARTMENTREPORTER_H__

