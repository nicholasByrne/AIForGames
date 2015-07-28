#pragma once
#include "TreeNode.h"

class BinaryTreeClass
{
public:
	BinaryTreeClass();
	~BinaryTreeClass();

	TreeNode* m_rootNode;

	bool IsEmpty();
	void Insert(int value);
	bool Find(int value);
	
	//TODO
	void Remove(int value);
	//http://aieportal.aie.edu.au/pluginfile.php/37788/mod_resource/content/0/Trees%20-%20Exercise.pdf
	//http://www.algolist.net/Data_structures/Binary_search_tree/Removal
};

