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
	else //discard duplicate value
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
	if (value < m_value && m_left != nullptr)
	{
		m_left->Remove(value, this);
	}
	else if (m_value == value)
	{
		//NodeToDelete has no children
		if (m_left == nullptr && m_right == nullptr)
		{
			if (parentNode->m_left->m_value == value)
				delete parentNode->m_left;
			else if (parentNode->m_right->m_right->m_value == value)
				delete parentNode->m_right;
		}
		//NodeToDelete has one child
		else if ((m_left == nullptr && m_right != nullptr) || (m_left != nullptr && m_right == nullptr))
		{
			if (m_left != nullptr)
			{
				//make parentNode (left||right) = m_left, delete this?
			}
			else
			{

			}
		}
		//NodeToDelete has two children
		else
		{

		}
	}
	else if (m_value > value && m_right != nullptr)
	{
		m_right->Remove(value, this);
	}
	else if (value < m_value)
	{

	}
	else if (m_value > value)
	{

	}
}


int TreeNode::FindSmallestGreaterVal(TreeNode* startingNode) //TODO
{
	return 0;
}

