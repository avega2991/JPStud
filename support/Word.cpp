#include "support\Word.h"

USING_NS_CC;

int DictionaryWord::s_idCounter = 1;


DictionaryWord::DictionaryWord(const std::string& formatString)
{
	this->m_id = s_idCounter;
	s_idCounter++;

	std::string line = formatString;

	int startSymPos = line.find("\"");
	line = line.substr(startSymPos + 1, line.length() - startSymPos - 1);
	int endSymPos = line.find("\"");
	std::string romajiWriting = line.substr(0, endSymPos);
	line = line.substr(endSymPos + 1, line.length() - endSymPos);

	this->m_romajiWriting = romajiWriting;

	startSymPos = line.find("\"");
	line = line.substr(startSymPos + 1, line.length() - startSymPos);
	endSymPos = line.find("\"");
	std::string kanjiWriting = line.substr(0, endSymPos);
	line = line.substr(endSymPos + 1, line.length() - endSymPos);
	
	this->m_kanjiWriting = kanjiWriting;

	startSymPos = line.find("\"");
	line = line.substr(startSymPos + 1, line.length() - startSymPos);
	endSymPos = line.find("\"");
	std::string kanaWriting = line.substr(0, endSymPos);
	line = line.substr(endSymPos + 3, line.length() - endSymPos);
	
	this->m_kanaWriting = kanaWriting;

	startSymPos = line.find("\"");
	while (startSymPos != std::string::npos)
	{
		std::string translation = line.substr(0, line.find("\""));
		int translationLength = translation.length();
		int translationEndSymPos = line.find(":");
		
		if (translationEndSymPos == std::string::npos)
			line.clear();
		else
			line = line.substr(translationLength + 3, line.length() - translationLength);

		startSymPos = line.find("\"");

		this->m_translations.push_back(translation);
	}
}

int	DictionaryWord::getID()
{
	return m_id;
}

std::string	DictionaryWord::getRomajiWriting()
{
	return m_romajiWriting;
}

std::string	DictionaryWord::getKanaWriting()
{
	return m_kanaWriting;
}

std::string	DictionaryWord::getKanjiWriting()
{
	return m_kanjiWriting;
}

std::vector<std::string>	DictionaryWord::getTranslations()
{
	return m_translations;
}
