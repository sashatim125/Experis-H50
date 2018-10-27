#ifndef __WORKER_H__
#define __WORKER_H__

#include <string>
#include <utility> 

#include "jobs.h"

namespace advcpp
{


class Worker
{

friend class WorkerAccessor;

public:

	inline
	Worker(const std::string& _firstName, const std::string& _lastName);
	
	inline
	Worker(const std::string& _firstName, const std::string& _lastName,
		const JobId_t& _jobId, double _salary);

//	~Worker();

	inline
	const JobId_t& GetJobId() const;
	
	inline
	void SetJobId(const JobId_t& _jobId);
	
	inline
	double GetSalary() const;
	
	inline
	void GetSalary(double _salary);

private:

	std::string m_firstName;
	std::string m_lastName;
	JobId_t m_jobId;
	double m_salary;
};

class WorkerAccessor
{
public:

	inline
	WorkerAccessor(const Worker& _worker);
	
//	~WorkerAccessor();

	inline
	std::pair<std::string, std::string> GetName() const;
	
private:
	const Worker& m_worker;
};

}


using namespace advcpp;

inline
Worker::Worker(const std::string& _firstName, const std::string& _lastName) :
	m_firstName(_firstName), m_lastName(_lastName), m_jobId(0), m_salary(0)
{}

inline
Worker::Worker(const std::string& _firstName, const std::string& _lastName,
	const JobId_t& _jobId, double _salary) :
	m_firstName(_firstName), m_lastName(_lastName), m_jobId(_jobId), m_salary(_salary)
{}

inline
const JobId_t& Worker::GetJobId() const
{
	return m_jobId;
}
	
inline
void Worker::SetJobId(const JobId_t& _jobId)
{
	m_jobId = _jobId;
}
	
inline
double Worker::GetSalary() const
{
	return m_salary;
}
	
inline
void Worker::GetSalary(double _salary)
{
	m_salary = _salary;
}

inline
WorkerAccessor::WorkerAccessor(const Worker& _worker) :
	m_worker(_worker)
{}

inline
std::pair<std::string, std::string> WorkerAccessor::GetName() const
{
	return std::pair<std::string, std::string>(m_worker.m_firstName,m_worker.m_lastName);
}



#endif //__WORKER_H__

