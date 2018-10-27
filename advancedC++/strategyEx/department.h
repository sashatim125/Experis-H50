#ifndef __DEPARTMENT_H__
#define __DEPARTMENT_H__

#include <vector>

#include "worker.h"


namespace advcpp
{
class DepartmentReporter;

class Department
{

friend class DepartmentAccessor;

public:

	inline
	Department(const std::string& _name, const std::string& _description, DepartmentReporter* _reporter);
	
//	~Department();

	inline
	void AddWorker(const Worker& _w);
	
	void Report() const;
	
	inline
	void SetReporter(DepartmentReporter* _reporter);

private:
	Department(const Department& _d);
	Department& operator=(const Department& _d);

	std::string m_name;
	std::string m_description;
	std::vector<Worker> m_workers;
	
	DepartmentReporter *m_reporter;
};

class DepartmentAccessor
{
public:

	inline
	DepartmentAccessor(const Department& _dep);
	
//	~DepartmentAccessor();

	inline
	const std::string& GetName() const;

	inline
	const std::string& GetDescription() const;
	
	inline
	const std::vector<Worker>& GetWorkers() const;	
	
private:
	const Department& m_dep;
};


}

using namespace advcpp;

Department::Department(const std::string& _name, const std::string& _description, DepartmentReporter* _reporter) :
	m_name(_name), m_description(_description), m_reporter(_reporter)
{}


inline
void Department::AddWorker(const Worker& _w)
{
	m_workers.push_back(_w);
}	


inline
void Department::SetReporter(DepartmentReporter* _reporter)
{
	m_reporter = _reporter;
}


inline
DepartmentAccessor::DepartmentAccessor(const Department& _dep) :
	m_dep(_dep)
{}

inline
const std::string& DepartmentAccessor::GetName() const
{
	return m_dep.m_name;
}

inline
const std::string& DepartmentAccessor::GetDescription() const
{
	return m_dep.m_description;
}
	
inline
const std::vector<Worker>& DepartmentAccessor::GetWorkers() const
{
	return m_dep.m_workers;
}






#endif //__DEPARTMENT_H__

