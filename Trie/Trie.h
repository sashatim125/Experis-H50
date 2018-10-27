

#ifndef __TRIE_H__
#define __TRIE_H__

#include "ITrie.h"

#include <stdexcept>
#include <fstream>
#include <vector>
#include <boost/interprocess/managed_external_buffer.hpp>
#include <boost/interprocess/indexes/null_index.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/container/flat_map.hpp>

using namespace boost::interprocess;


class Trie : public ITrie
{
public:

	static const std::size_t BUFFER_SIZE = 32*1024;
	
private:

	static const std::size_t ALIGHMENT = 8;

	typedef int16_t BufferOffsetDiff;
	
	typedef basic_managed_external_buffer
	   <char
	   ,rbtree_best_fit<null_mutex_family>
	   ,null_index>
		SimpleManagedExternalBuffer;

	class OffsetPtr;

	typedef std::pair<char, OffsetPtr> 
			TrieNodePair;

	typedef allocator<TrieNodePair, SimpleManagedExternalBuffer::segment_manager>
			TrieNodePairAllocator;
			
	class TrieNode;
	
	typedef std::vector<TrieNode*> 
			TrieNodePtrVector;
	
public:

	//buffer_ptr = preallocated array of BUFFER_SIZE size of bytes
	static Trie* TrieCreate(char* bufferPtr);

	//no need to free any memory
	//~Trie() {};

	// Try to add the key/val to the trie
	// can fail if there isn't enough room
	// if already exists, will overwrite old 
	// value
	virtual bool TryWrite(const std::string& key, const LongInt& value);

	// Try to find the key in the trie, if found,
	// will put the value in the out param.
	// Can fail if value is not there
	virtual bool TryRead(const std::string& key, LongInt& value) const;

	// Remove the key from the trie, noop
	// if the key isn't there
	virtual void Delete(const std::string& key);

	// Saves the internal array to a file
	virtual void Save(const std::string& filename) const;
	
	// Loads the internal array from a file
	virtual void Load(const std::string& filename);
	
private:
	//non-copyable
	Trie(const Trie&);
	Trie& operator=(const Trie&);
	
	//buffer_ptr = preallocated array of BUFFER_SIZE size of bytes
	explicit Trie(char* bufferPtr);
	
	void DeletePath(const TrieNodePtrVector& tnpVec, const std::string& key, bool withValue);

//inner classes//////////////

	//Is used as (relational = offset) pointer within the buffer
	class OffsetPtr
	{
	public:
	
		//~OffsetPtr() {}
		
		OffsetPtr();
		
		explicit OffsetPtr(void* ptr);
		
		OffsetPtr(const OffsetPtr& other);
			
		OffsetPtr& operator=(const OffsetPtr& other);
		
		OffsetPtr& operator=(void* ptr);
		
		void* get() const;
		
	private:	
		BufferOffsetDiff m_offset;
	};

	//Trie Node - a map with pairs (char, ptr to TrieNode), and optional (VALUE_TAG, ptr to value)
	class TrieNode
	{
	private:	
		static const char VALUE_TAG;
	
		typedef boost::container::flat_map<char, OffsetPtr, std::less<char>, TrieNodePairAllocator>
			TrieNodeChildren;
		
	public:
	
		//~TrieNode()

		TrieNode(const OffsetPtr& triePtr);
			
		std::size_t numOfChildren() const;
		
		//does have a value and/or children
		bool isValid() const;
		
		bool hasValue() const;
		
		void setValue(const LongInt& val); //throws
		
		LongInt getValue() const; //throws
		
		void deleteValue();

		bool hasChild(const char c) const;
		
		TrieNode* getChild(const char c) const; //throws
	
		void insertChild(const char c); //throws
		
		void deleteChild(const char c);

	private:
		//non_copyable
		TrieNode(const TrieNode&);
		TrieNode& operator=(const TrieNode&);
			
		OffsetPtr m_TriePtr;
		
		TrieNodeChildren m_children;
	};
	
//members//////////////////
	
	char*  m_bufferPtr;
	
	SimpleManagedExternalBuffer m_managedBuffer;
	
	TrieNodePairAllocator m_TrieNodePairAlloc;

	OffsetPtr m_trieRootOffsetPtr;
};




#endif //__TRIE_H__


