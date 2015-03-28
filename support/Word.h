#pragma once

#include "cocos2d.h"
#include <vector>

// TODO : SET THE PARSER TIDY
class DictionaryWord
{
private:
	int																m_id;
	std::string														m_romajiWriting;
	std::string														m_kanjiWriting;
	std::string														m_kanaWriting;
	std::vector<std::string>										m_translations;

	static int														s_idCounter;


public:
	DictionaryWord(const std::string& formatString);
	// ~DictionaryWord();

	int																getID();
	std::string														getRomajiWriting();
	std::string														getKanjiWriting();
	std::string														getKanaWriting();
	std::vector<std::string>										getTranslations();

};