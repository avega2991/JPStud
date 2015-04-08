#include "panes\mini-games\kanji_crossword\CrosswordWord.h"

using namespace MiniGames;
USING_NS_CC;


CrosswordWord::CrosswordWord(int stringLength)
{
	m_word.resize(stringLength);
}

CrosswordWord::CrosswordWord(size_t stringLength)
{
	m_word.resize(stringLength);
}

// <GET>
std::vector<Triad<KANJI_ID, RELATED_WORD_INDEX, RELATED_KANJI_INDEX>>	CrosswordWord::getData()
{
	return m_word;
}

Triad<KANJI_ID, RELATED_WORD_INDEX, RELATED_KANJI_INDEX>	CrosswordWord::getDataByIndex(int index)
{
	return m_word[index];
}

KANJI_ID	CrosswordWord::getKanjiIDByStringIndex(int index)
{
	return m_word[index].first;
}

RELATED_WORD_INDEX	CrosswordWord::getRelatedWordIndexByString(int index)
{
	return m_word[index].second;
}

RELATED_KANJI_INDEX	CrosswordWord::getRelatedKanjiIndexStringByStringIndex(int index)
{
	return m_word[index].third;
}
// </GET>

// <SET>
void	CrosswordWord::setData(std::vector<Triad<KANJI_ID, RELATED_WORD_INDEX, RELATED_KANJI_INDEX>> data)
{
	m_word = data;
}

void	CrosswordWord::setDataWithIndex(Triad<KANJI_ID, RELATED_WORD_INDEX, RELATED_KANJI_INDEX> data, int index)
{
	m_word[index] = data;
}

void	CrosswordWord::setKanjiIDByStringIndex(KANJI_ID id, int index)
{
	m_word[index].first = id;
}

void	CrosswordWord::setRelatedWordIndexByString(RELATED_WORD_INDEX wordIndex, int index)
{
	m_word[index].second = wordIndex;
}

void	CrosswordWord::setRelatedKanjiIndexStringByStringIndex(RELATED_KANJI_INDEX kanjiIndex, int index)
{
	m_word[index].third = kanjiIndex;
}
// </SET>