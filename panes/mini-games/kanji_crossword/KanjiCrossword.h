#pragma once

#include "cocos2d.h"

#include "support\AppDictionary.h"
#include "panes\mini-games\kanji_crossword\CrosswordWord.h"


namespace MiniGames
{
	class KanjiCrossword : public cocos2d::Layer
	{
	private:
		AppDictionary*																		m_dictionary;
		std::set<CrosswordWord*>															m_currentWordsSet;
		
	private:
		std::set<CrosswordWord*>															generateWordsSet(short wordsNum);

		CrosswordWord*																		wordToCrosswordWord(ID wordID);

		bool																				isOnlyKanjiWord(ID wordID);

	public:
		KanjiCrossword(short wordsNum);
		// ~KanjiCrossword();

		static KanjiCrossword*																create(short wordsNum);
	};
};