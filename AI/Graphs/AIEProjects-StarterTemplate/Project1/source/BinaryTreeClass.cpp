#include "BinaryTreeClass.h"


BinaryTreeClass::BinaryTreeClass()
{
	m_rootNode = nullptr;
}


BinaryTreeClass::~BinaryTreeClass()
{

}


bool BinaryTreeClass::IsEmpty()
{
	if (m_rootNode == nullptr)
		return true;
	else return false;
}


void BinaryTreeClass::Insert(int value)
{
	if (m_rootNode == nullptr)
		m_rootNode = new TreeNode(value);
	else
		m_rootNode->AddValue(value);
}


bool BinaryTreeClass::Find(int value)
{
	if (m_rootNode == nullptr)
		return false;
	else
		return m_rootNode->FindValue(value);
}


void BinaryTreeClass::Remove(int value)
{
	if (m_rootNode != nullptr)
	{
		if (value < m_rootNode->m_value && m_rootNode->m_left != nullptr)
		{
			m_rootNode->m_left->Remove(value, m_rootNode);
		}
		else if (m_rootNode->m_value == value)
		{
			//FIND RIGHT LOWEST LEAF
		}
		else if (m_rootNode->m_value > value && m_rootNode->m_right != nullptr)
		{
			m_rootNode->m_right->Remove(value, m_rootNode);
		}
	}
}