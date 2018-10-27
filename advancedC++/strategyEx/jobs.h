#ifndef __JOBS_H__
#define __JOBS_H__


#include <map>
#include <string>
#include <stdexcept>

namespace advcpp
{

typedef int JobId_t;

//static class
class Jobs
{
public:
	//returns empty string on failure
	inline static
	const std::string& FindJob(const JobId_t& _j);
	
	inline static
	void AddSetJob(const JobId_t& _j, const std::string& _desc);

private:
	Jobs();
	
	static std::map<JobId_t,std::string> s_jobs;
	static const std::string s_emptyString;
};

}

using namespace advcpp;

inline
const std::string& Jobs::FindJob(const JobId_t& _j)
{
	std::map<JobId_t,std::string>::iterator it = s_jobs.find(_j);
	
	return (it == s_jobs.end()) ? s_emptyString : it->second;
}
	
inline
void Jobs::AddSetJob(const JobId_t& _j, const std::string& _desc)
{
	s_jobs[_j] = _desc;
}

#endif //__JOBS_H__

