#pragma once

#include "cocos2d.h"

#include "support\AppDictionary.h"
#include "support\AppLib.h"

#define KANJI_NOT_RELATED		-1

typedef int						KANJI_ID;
typedef short					RELATED_WORD_INDEX;
typedef short					RELATED_KANJI_INDEX;


namespace MiniGames
{
	class CrosswordWord
	{
	private:
		std::vector<Triad<KANJI_ID, RELATED_WORD_INDEX, RELATED_KANJI_INDEX>>				m_word;	// EVERY ELEM = KANJI WORD
																									// EVERY WORD'S ELEM : 
																									// 1) KANJI ID
																									// 2) INDEX OF RELATED WORD
																									// 3) INDEX OF RELATED KANJI

	public:
		CrosswordWord(int stringLength);
		CrosswordWord(size_t stringLength);
		// ~CrosswordWord();

		std::vector<Triad<KANJI_ID, RELATED_WORD_INDEX, RELATED_KANJI_INDEX>>				getData();
		Triad<KANJI_ID, RELATED_WORD_INDEX, RELATED_KANJI_INDEX>							getDataByIndex(int index);
		KANJI_ID																			getKanjiIDByStringIndex(int index);
		RELATED_WORD_INDEX																	getRelatedWordIndexByString(int index);
		RELATED_KANJI_INDEX																	getRelatedKanjiIndexStringByStringIndex(int index);

		void																				setData(std::vector<Triad<KANJI_ID, RELATED_WORD_INDEX, RELATED_KANJI_INDEX>> data);
		void																				setDataWithIndex(Triad<KANJI_ID, RELATED_WORD_INDEX, RELATED_KANJI_INDEX> data, int index);
		void																				setKanjiIDByStringIndex(KANJI_ID, int index);
		void																				setRelatedWordIndexByString(RELATED_WORD_INDEX, int index);
		void																				setRelatedKanjiIndexStringByStringIndex(RELATED_KANJI_INDEX, int index);
	};
};