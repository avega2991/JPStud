#include "panes\mini-games\kanji_crossword\KanjiCrossword.h"

using namespace MiniGames;
USING_NS_CC;


KanjiCrossword::KanjiCrossword(short wordsNum)
{
	m_currentWordsSet = this->generateWordsSet(wordsNum);

}

KanjiCrossword*	KanjiCrossword::create(short wordsNum)
{
	KanjiCrossword* kanjiCrossword = new KanjiCrossword(wordsNum);

	if (kanjiCrossword->init())
	{
		kanjiCrossword->autorelease();
		return kanjiCrossword;
	}

	CC_SAFE_DELETE(kanjiCrossword);
	return nullptr;
}

std::set<CrosswordWord*>	KanjiCrossword::generateWordsSet(short wordsNum)
{
	std::set<CrosswordWord*> wordsSet;
	/*std::set<ID> existedWordsIDVector;
	std::map<ID, DictionaryWord*> wordsDict = AppDictionary::getInstance()->getWordsDictionary();
	long wordsCount = wordsDict.size();

	// FIRST WORD IS RANDOM
	std::srand(time(0));
	ID wordID = rand() % wordsCount;
	while (!this->isOnlyKanjiWord(wordID))
	{
		wordID = rand() % wordsCount;
	}

	CrosswordWord* kanjiWord = this->wordToCrosswordWord(wordID);
	existedWordsIDVector.insert(wordID);
	
	// TODO : GENERATE KANJI-SET
	for (std::map<ID, DictionaryWord*>::iterator newWord = wordsDict.begin(); newWord != wordsDict.end(); newWord++)
	{
		ID newWordID = newWord->first;

		if (this->isOnlyKanjiWord(newWordID) &&
			existedWordsIDVector.find(newWordID) == existedWordsIDVector.end())
		{
			kanjiWord = this->wordToCrosswordWord(newWordID);

			// TODO : CHECK - ARE THERE ANY EXISTED KANJI ???
			for (std::set<std::vector<Triad<short, short, short>>>::iterator word = wordsSet.begin();
				word != wordsSet.end(); word++)
			{
				for (std::vector<Triad<short, short, short>>::const_iterator sym = word->begin(); sym != word->end(); sym++)
				{
					
				}
			}
		}

		if (wordsSet.size() >= wordsNum)
			break;
	}*/

	return wordsSet;
}

CrosswordWord*	KanjiCrossword::wordToCrosswordWord(ID wordID)
{
	std::string word = m_dictionary->getWordByID(wordID)->getKanjiWriting();
	std::map<ID, Kanji*> kanjiDict = m_dictionary->getKanjiDictionary();
	CrosswordWord* cwWord = new CrosswordWord(word.size());

	for (int i = 0; i < word.size(); i++)
	{
		Triad<KANJI_ID, RELATED_WORD_INDEX, RELATED_KANJI_INDEX> elem;
		Kanji* kanji = m_dictionary->getKanjiBySym(std::to_string(word[i]));
		
		elem.first = kanji->getID();
		elem.second = KANJI_NOT_RELATED;
		elem.third = KANJI_NOT_RELATED;

		cwWord->setDataWithIndex(elem, i);
	}

	return cwWord;
}

bool	KanjiCrossword::isOnlyKanjiWord(ID wordID)
{
	DictionaryWord* word = m_dictionary->getWordByID(wordID);
	std::string kanjiWriting = word->getKanjiWriting();
	std::vector<std::string> kanaSymbols;

	// <INIT_KANA_VECTOR>
	std::map<std::string, Triad<std::string, std::string, std::string>> m_keyboradDict = m_dictionary->getKeyboardDictionary();

	for (std::map<std::string, Triad<std::string, std::string, std::string>>::iterator sym = m_keyboradDict.begin();
		sym != m_keyboradDict.end(); sym++)
	{
		kanaSymbols.push_back(sym->second.first);
		kanaSymbols.push_back(sym->second.second);
	}
	// </INIT_KANA_VECTOR>

	for (int i = 0; i < kanjiWriting.size(); i++)
	{
		for (std::vector<std::string>::iterator sym = kanaSymbols.begin();
			sym != kanaSymbols.end(); sym++)
		{
			if (kanjiWriting.find(*sym) != std::string::npos)
				return false;
		}
	}

	return true;
}