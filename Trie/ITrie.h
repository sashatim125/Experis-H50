

#ifndef __ITRIE_H__
#define __ITRIE_H__

#ifndef interface
#define interface struct
#endif //interface


#include <string>
#include <cstdint>


interface ITrie
{
	typedef int64_t LongInt;//value type
	
	virtual ~ITrie() {};

	// Try to add the key/val to the trie
	// can fail if there isn't enough room
	// if already exists, will overwrite old 
	// value
	virtual bool TryWrite(const std::string& key, const LongInt& value) =0;

	// Try to find the key in the trie, if found,
	// will put the value in the out param.
	// Can fail if value is not there
	virtual bool TryRead(const std::string& key, LongInt& value) const =0;

	// Remove the key from the trie, noop
	// if the key isn't there
	virtual void Delete(const std::string& key) =0;

	// Saves the internal array to a file
	virtual void Save(const std::string& filename) const =0;
	
	// Loads the internal array from a file
	virtual void Load(const std::string& filename) =0;
};

#endif //__ITRIE_H__


