
#ifndef __VIRTIO_T_H__
#define __VIRTIO_T_H__

#include <cstdio>
#include <string>
#include <utility>
#include <stdexcept>


using namespace std; 

class VirtIO_t
{
	public:
	
	//ends with "cant_open_file_e" status
	VirtIO_t();
	
	//ends with "cant_open_file_e" status
	VirtIO_t(const string & _name, const string& _mode);

	virtual ~VirtIO_t() =0;

	//throws if have open file
	void SetNameAndMode(const string & _name, const string& _mode);

	pair<string,string> GetNameAndMode()const;

	const string& GetStatus()const;
	
	bool IsOpen()const;
	
	//throws if file isn't open
	size_t GetLength()const;
	
	//throw if open error or there is allready open file
	void OpenFile();

	//throw if no open file
	//ends with "cant_open_file_e" status
	void CloseFile();
	
	virtual
	VirtIO_t& operator<<(const char& _val) =0;

	virtual
	VirtIO_t& operator<<(const unsigned char& _val) =0;

	virtual
	VirtIO_t& operator<<(const short& _val) =0;
	
	virtual
	VirtIO_t& operator<<(const unsigned short& _val) =0;
	
	virtual
	VirtIO_t& operator<<(const int& _val) =0;
	
	virtual
	VirtIO_t& operator<<(const unsigned int& _val) =0;
	
	virtual
	VirtIO_t& operator<<(const long& _val) =0;
	
	virtual
	VirtIO_t& operator<<(const unsigned long& _val) =0;

	virtual
	VirtIO_t& operator<<(const float& _val) =0;
	
	virtual
	VirtIO_t& operator<<(const double& _val) =0;
	
	virtual
	VirtIO_t& operator>>(char& _val) =0;

	virtual
	VirtIO_t& operator>>(unsigned char& _val) =0;

	virtual
	VirtIO_t& operator>>(short& _val) =0;
	
	virtual
	VirtIO_t& operator>>(unsigned short& _val) =0;
	
	virtual
	VirtIO_t& operator>>(int& _val) =0;
	
	virtual
	VirtIO_t& operator>>(unsigned int& _val) =0;
	
	virtual
	VirtIO_t& operator>>(long& _val) =0;
	
	virtual
	VirtIO_t& operator>>(unsigned long& _val) =0;

	virtual
	VirtIO_t& operator>>(float& _val) =0;
	
	virtual
	VirtIO_t& operator>>(double& _val) =0;
	
	protected:

	enum Status
	{
		ok_e,
		cant_open_file_e,
		bad_access_e,
		writeErr_e,
		readErr_e
	};
	
	void SetStatus(Status _st);

	FILE*& GetFile();
	
	static
	const string s_StatusStrs[];

	private:
	//uncopyable objects
	VirtIO_t(const VirtIO_t& _vio);
	
	VirtIO_t& operator=(const VirtIO_t& _vio);
	
	
	FILE* m_file;
	
	string m_pathname;
	
	string m_mode;
	
	Status m_status;
	
	bool m_isOpen;
};


	












#endif //__VIRTIO_T_H__

