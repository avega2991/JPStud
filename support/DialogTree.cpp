#include "DialogTree.h"


DialogTree::DialogTree()
{
	m_root = new TreeNode();
	m_root->childrenCount = 0;
	m_iterator = m_root;
}

void	DialogTree::push(const std::string& formatFilename)
{
	(*this) << formatFilename;
}

void	DialogTree::operator<< (const std::string& formatFilename)
{
	std::ifstream inputFile(formatFilename);
	this->parseFile(inputFile, m_root);
	inputFile.close();
}

void	DialogTree::parseFile(std::ifstream& inputFile, TreeNode* destination)
{
	static std::string dialogTreeLine;

	std::getline(inputFile, dialogTreeLine);

	int startSymPos = dialogTreeLine.find("\"");
	dialogTreeLine = dialogTreeLine.substr(startSymPos + 1, dialogTreeLine.length() - startSymPos - 1);

	int endSymPos = dialogTreeLine.find("\"");
	std::string dialogText = dialogTreeLine.substr(0, endSymPos);
	std::string lineEnd = dialogTreeLine.substr(endSymPos + 1, dialogTreeLine.length() - endSymPos);

	int nChildren = 0;
	int childSymPos = lineEnd.find(";");
	while (childSymPos != std::string::npos)
	{
		nChildren++;
		lineEnd = lineEnd.substr(childSymPos + 2, lineEnd.length() - childSymPos - 1);

		endSymPos = lineEnd.find("\"");
		std::string answerText = lineEnd.substr(0, endSymPos);

		destination->answers.push_back(answerText);
		childSymPos = lineEnd.find(";");
	}

	std::vector<TreeNode* > childrenVector(nChildren);

	destination->value = dialogText;
	destination->childrenCount = nChildren;
	destination->children = childrenVector;

	for (std::vector<TreeNode* >::iterator it = destination->children.begin(); it != destination->children.end(); it++)
	{
		*it = new TreeNode();
		this->parseFile(inputFile, *it);
	}
}

std::string	DialogTree::getCurrentNodeText()
{
	return m_iterator->value;
}

std::vector<std::string>	DialogTree::getAnswers()
{
	return m_iterator->answers;
}

std::queue<short>	DialogTree::getNodeSequence()
{
	return m_answerSequence;
}

void	DialogTree::nextNode(short chosenCase)
{
	m_iterator = m_iterator->children[chosenCase];
	m_answerSequence.push(chosenCase);
}
