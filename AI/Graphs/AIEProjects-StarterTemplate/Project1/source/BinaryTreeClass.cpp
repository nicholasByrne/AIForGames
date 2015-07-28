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

}