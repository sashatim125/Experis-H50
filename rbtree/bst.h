
#ifndef __BST_H__
#define __BST_H__


//Binary search tree template



template <typename T>
class BSTNode
{
public:

	BSTNode(const T& _data)
	: m_data(_data)
	{}
	
	BSTNode(const T& _data, BSTNode* _parent, BSTNode* _left, BSTNode* _right)
	: m_data(_data)
	, m_parent(_parent)
	, m_left(_left)
	, m_right(_right)
	{}
	
	~BSTNode()
	{
		delete m_right;
		delete m_left;
	}
	
	const T& data() const
	{
		return m_data;
	}
	
	const BSTNode* parent() const;
	{
		return m_parent;
	}
	BSTNode*& parent()
	{
		return m_parent;
	}
	
	const BSTNode* left() const
	{
		return m_left;
	}
	BSTNode*& left()
	{
		return m_left;
	}
	
	const BSTNode*& right() const
	{
		return m_right;
	}
	BSTNode* right()
	{
		return m_right;
	}
	
	

private:
	//temporary uncopyable
	BSTNode(const BSTNode&);
	BSTNode& operator=(const BSTNode&);

	BSTNode *m_parent;
	BSTNode *m_left;
	BSTNode *m_right;
	
	T m_data;
	
};













































#endif //__BST_H__
