#pragma once
class TreeNode
{
public:
	TreeNode();
	TreeNode(TreeNode* parent);
	TreeNode(int value);
	~TreeNode();

	int m_value;

	//Children
	TreeNode* m_left;
	TreeNode* m_right;

	void AddValue(int value);
	bool FindValue(int value);
	void Remove(int value, TreeNode* parentNode);
};

