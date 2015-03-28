#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <queue>


struct TreeNode
{
	std::string						value;
	short							childrenCount;
	std::vector<TreeNode* >			children;
	std::vector<std::string>		answers;
};

class DialogTree
{
private:
	TreeNode*						m_root;
	TreeNode*						m_iterator;

	// sequence of dialog pointers until the current node (for JAP <-> ENG convertation)
	std::queue<short>				m_answerSequence;

private:
	void							parseFile(std::ifstream& inputFile, TreeNode* destination);

public:
	DialogTree();
	// ~DialogTree();

	void							push(const std::string&);
	// 'push' synonim
	void							operator<< (const std::string&);

	std::string						getCurrentNodeText();
	std::vector<std::string>		getAnswers();
	
	std::queue<short>				getNodeSequence();

	void							nextNode(short chosenNode);
};
