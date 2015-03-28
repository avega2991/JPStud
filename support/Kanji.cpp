#include "support\Kanji.h"

USING_NS_CC;

int Kanji::s_idCounter = 1;


Kanji::Kanji(const std::string& formatString)
{
	this->m_id = s_idCounter;
	s_idCounter++;

	std::string line = formatString;
	
	int startSymPos = line.find("\"");
	line = line.substr(startSymPos + 1, line.length() - startSymPos - 1);
	int endSymPos = line.find("\"");
	std::string kanjiSym = line.substr(0, endSymPos);
	line = line.substr(endSymPos + 1, line.length() - endSymPos);

	this->m_symbol = kanjiSym;

	startSymPos = line.find("\"");
	line = line.substr(startSymPos + 1, line.length() - startSymPos - 1);
	endSymPos = line.find("\"");
	std::string filename = line.substr(0, endSymPos);
	line = line.substr(endSymPos + 1, line.length() - endSymPos);
	Sprite* image = Sprite::create(filename);

	this->m_image = image;

	startSymPos = line.find("\"");
	while (startSymPos != std::string::npos)
	{
		startSymPos = line.find("\"");
		line = line.substr(startSymPos + 1, line.length() - startSymPos - 1);
		endSymPos = line.find("\"");
		std::string reading = line.substr(0, endSymPos);
		line = line.substr(endSymPos + 1, line.length() - endSymPos);

		std::string exampleLine = line.substr(0, line.find(";"));
		int exampleLength = exampleLine.length();
		int exampleEndSymPos = exampleLine.find(":");
		while (exampleEndSymPos != std::string::npos && exampleLine.length() > 0)
		{
			startSymPos = exampleLine.find("\"");
			exampleLine = exampleLine.substr(startSymPos + 1, exampleLine.length() - startSymPos - 1);
			endSymPos = exampleLine.find("\"");
			std::string example = exampleLine.substr(0, endSymPos);
			exampleLine = exampleLine.substr(endSymPos + 1, exampleLine.length() - endSymPos);

			this->m_description[reading].push_back(example);

			exampleEndSymPos = line.find(":");
		}
		line = line.substr(exampleLength, line.length() - exampleLength);

		startSymPos = line.find("\"");
	}
}

int	Kanji::getID()
{
	return this->m_id;
}

std::string	Kanji::getSymbol()
{
	return this->m_symbol;
}

Sprite*	Kanji::getSprite()
{
	return this->m_image;
}

std::map<std::string, std::vector<std::string>>	Kanji::getDescription()
{
	return this->m_description;
}