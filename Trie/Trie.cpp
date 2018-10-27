

#include "Trie.h"

///////////////////////
//Trie/////////////////
///////////////////////


	//buffer_ptr = preallocated array of BUFFER_SIZE size of bytes
	Trie* Trie::TrieCreate(char* bufferPtr)
	{
		return ::new (bufferPtr+Trie::BUFFER_SIZE-sizeof(Trie)) Trie(bufferPtr);
	}


	//buffer_ptr = preallocated array of BUFFER_SIZE size of bytes
	Trie::Trie(char* bufferPtr)
		: m_bufferPtr(bufferPtr)
		, m_managedBuffer(create_only, bufferPtr, BUFFER_SIZE-sizeof(Trie))
		, m_TrieNodePairAlloc(m_managedBuffer.get_segment_manager())
		, m_trieRootOffsetPtr(m_managedBuffer.allocate(sizeof(TrieNode)))
	{
		::new (m_trieRootOffsetPtr.get()) TrieNode(OffsetPtr(this));
	}

	// Try to add the key/val to the trie
	// can fail if there isn't enough room
	// if already exists, will overwrite old 
	// value
	bool Trie::TryWrite(const std::string& key, const LongInt& value)
	{
		std::size_t length = key.length();
		std::size_t i = 0;
		TrieNode* nextNode = static_cast<TrieNode*>(m_trieRootOffsetPtr.get());
		//here we keep the path in the trie 
		//so we can delete the remains of unsuccessful attempt
		TrieNodePtrVector tnpVec;
		tnpVec.reserve(length+1);
		tnpVec.push_back(nextNode);
		
		for(; i < length ; nextNode = nextNode->getChild(key[i]),
			tnpVec.push_back(nextNode), ++i)
		{		
			if(!nextNode->hasChild(key[i]))
			{
				try
				{
					nextNode->insertChild(key[i]);
				}catch (std::exception&)
				{
					//DESTOY the unfinished key
					tnpVec.pop_back();
					DeletePath(tnpVec, key, false);
					return false;
				}
			}
		}

		try
		{
			nextNode->setValue(value);
		}catch (std::exception&)
		{
			//DESTOY the unfinished key
			tnpVec.pop_back();
			DeletePath(tnpVec, key, false);
			return false;
		}
	
		return true;
	}

	// Try to find the key in the trie, if found,
	// will put the value in the out param.
	// Can fail if value is not there
	bool Trie::TryRead(const std::string& key, LongInt& value) const
	{
		std::size_t length = key.length();
		TrieNode* nextNode;
		std::size_t i;
		for(i = 0 , nextNode = static_cast<TrieNode*>(m_trieRootOffsetPtr.get()); i < length ; )
		{		
			if(nextNode->hasChild(key[i]))
			{
				nextNode = nextNode->getChild(key[i++]);
			}else
			{
				return false;
			}
		}
	
		if(nextNode->hasValue())
		{
			value = nextNode->getValue();
			return true;
		}
	
		return false;
	}

	// Remove the key from the trie, noop
	// if the key isn't there
	void Trie::Delete(const std::string& key)
	{
		std::size_t length = key.length();
		std::size_t i = 0;
		TrieNode* nextNode = static_cast<TrieNode*>(m_trieRootOffsetPtr.get());
		//here we keep the path in the trie 
		TrieNodePtrVector tnpVec;
		tnpVec.reserve(length+1);
		tnpVec.push_back(nextNode);
		
		for(; i < length ; nextNode = nextNode->getChild(key[i]),
			tnpVec.push_back(nextNode), ++i)
		{		
			if(!nextNode->hasChild(key[i]))
			{
				return;
			}
		}
		
		if(nextNode->hasValue())
		{
			DeletePath(tnpVec, key, true);
		}
	}

	// Saves the internal array to a file
	void Trie::Save(const std::string& filename) const
	{
		std::ofstream ofs(filename);
		
		ofs.write(m_bufferPtr, BUFFER_SIZE);
	}
	
	// Loads the internal array from a file
	void Trie::Load(const std::string& filename)
	{
		std::ifstream ifs(filename);
	
		char* bufferPtr = m_bufferPtr;
		
		ifs.read(m_bufferPtr, BUFFER_SIZE);
		
		m_bufferPtr = bufferPtr;
	}

	void Trie::DeletePath(const TrieNodePtrVector& tnpVec, const std::string& key, bool withValue)
	{
		long last = tnpVec.size()-1;
		
		if(withValue)
		{
			tnpVec[last--]->deleteValue();
		}
		
		for(; last >= 0; --last)
		{
			if(! tnpVec[last]->getChild(key[last])->isValid())
			{
				tnpVec[last]->deleteChild(key[last]);
			}
		}
	}

/////////////////////////
//Trie::OffsetPtr///////
////////////////////////

		Trie::OffsetPtr::OffsetPtr() 
			: m_offset(0)
		{}
		
		Trie::OffsetPtr::OffsetPtr(void* ptr)
			: m_offset(static_cast<BufferOffsetDiff>(static_cast<char*>(ptr) - reinterpret_cast<char*>(this)))
		{}
		
		Trie::OffsetPtr::OffsetPtr(const OffsetPtr& other)
			: m_offset(static_cast<BufferOffsetDiff>(static_cast<char*>(other.get()) - reinterpret_cast<char*>(this)))
		{}
			
		Trie::OffsetPtr& Trie::OffsetPtr::operator=(const Trie::OffsetPtr& other)
		{
			if(&other != this)
			{
				m_offset = static_cast<BufferOffsetDiff>(static_cast<char*>(other.get()) - reinterpret_cast<char*>(this));
			}
			return *this;
		}
		
		Trie::OffsetPtr& Trie::OffsetPtr::operator=(void* ptr)
		{
			m_offset = static_cast<BufferOffsetDiff>(static_cast<char*>(ptr) - reinterpret_cast<char*>(this));
			return *this;
		}
		
		void* Trie::OffsetPtr::get() const
		{
			return reinterpret_cast<char*>(const_cast<OffsetPtr*>(this))+m_offset;
		}


/////////////////////////
//Trie::TrieNode/////////
/////////////////////////


		Trie::TrieNode::TrieNode(const OffsetPtr& triePtr)
			: m_TriePtr(triePtr)
			, m_children(static_cast<Trie*>(m_TriePtr.get())->m_TrieNodePairAlloc)
			{}
		
		std::size_t Trie::TrieNode::numOfChildren() const
		{
			return m_children.size() - (this->hasValue() ? 1 : 0);
		}
		
		//does have a value and/or children
		bool Trie::TrieNode::isValid() const
		{
			return (!m_children.empty());
		}
		
		bool Trie::TrieNode::hasValue() const
		{
			return m_children.find(VALUE_TAG) != m_children.end();	
		}
		
		void Trie::TrieNode::setValue(const LongInt& val) //throws
		{
			TrieNodeChildren::iterator iter = m_children.find(VALUE_TAG);
			if(iter != m_children.end())
			{
				*(static_cast<LongInt*>(iter->second.get())) = val;
			}else
			{
				void* ptr = static_cast<Trie*>(m_TriePtr.get())->m_managedBuffer.allocate_aligned(sizeof(LongInt), ALIGHMENT);
				*(static_cast<LongInt*>(ptr)) = val;
				m_children.insert({VALUE_TAG,ptr});				
			}		
		}
		
		ITrie::LongInt Trie::TrieNode::getValue() const //throws
		{
			return *(static_cast<LongInt*>(m_children.at(VALUE_TAG).get()));
		}
		
		void Trie::TrieNode::deleteValue() 
		{
			TrieNodeChildren::const_iterator iter = m_children.find(VALUE_TAG);
			if(iter != m_children.end())
			{
				(static_cast<Trie*>(m_TriePtr.get()))->m_managedBuffer.deallocate(iter->second.get());
				m_children.erase(iter);	
			}
		}

		bool Trie::TrieNode::hasChild(const char c) const
		{
			return m_children.find(c) != m_children.end();	
		}
		
		Trie::TrieNode* Trie::TrieNode::getChild(const char c) const //throws
		{
			return static_cast<TrieNode*>(m_children.at(c).get());		
		}
	
		void Trie::TrieNode::insertChild(const char c) //throws
		{
			TrieNodeChildren::iterator iter = m_children.find(c);
			if(iter != m_children.end())
			{
				throw std::runtime_error("already exist");	
			}else
			{
				void* ptr = static_cast<Trie*>(m_TriePtr.get())->m_managedBuffer.allocate(sizeof(TrieNode));
				::new (ptr) TrieNode(m_TriePtr);			
				m_children.insert({c,ptr});
			}		
		}
		
		void Trie::TrieNode::deleteChild(const char c) 
		{
			TrieNodeChildren::const_iterator iter = m_children.find(c);
			if(iter != m_children.end())
			{
				(static_cast<TrieNode*>(iter->second.get()))->~TrieNode();
				(static_cast<Trie*>(m_TriePtr.get()))->m_managedBuffer.deallocate(iter->second.get());
				m_children.erase(iter);	
			}		
		}


	const char Trie::TrieNode::VALUE_TAG = '\0';





























