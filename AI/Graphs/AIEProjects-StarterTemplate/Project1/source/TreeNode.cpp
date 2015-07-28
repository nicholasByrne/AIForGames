#include "TreeNode.h"


TreeNode::TreeNode()
{
	m_left = nullptr;
	m_right = nullptr;
}


TreeNode::TreeNode(TreeNode* parent)
{
	m_left = nullptr;
	m_right = nullptr;
}


TreeNode::TreeNode(int value)
{
	m_left = nullptr;
	m_right = nullptr;
	m_value = value;
}


TreeNode::~TreeNode()
{

}


void TreeNode::AddValue(int value)
{
	if (value < m_value)
	{
		if (m_left != nullptr)
			m_left->AddValue(value);
		else
			m_left = new TreeNode(value);
	}
	else if (value > m_value)
	{
		if (m_right != nullptr)
			m_right->AddValue(value);
		else
			m_right = new TreeNode(value);
	}
	else //duplicate value
		return;
}


bool TreeNode::FindValue(int value)
{
	if (m_value == value)
	{
		return true;
	}
	else if (m_left == nullptr && value < m_value)
	{
		return false;
	}
	else if (value < m_value)
	{
		return m_left->FindValue(value);
	}
	else if (m_right == nullptr && value > m_value)
	{
		return false;
	}
	else if (value > m_value)
	{
		return m_right->FindValue(value);
	}
	else
		return false;
}


void TreeNode::Remove(int value, TreeNode* parentNode)
{

}

