#pragma once

#include "cocos2d.h"
#include <map>
#include <vector>
#include <fstream>

#include "support\Kanji.h"
#include "support\Word.h"
#include "sprites\Item.h"
#include "support\AppLib.h"


class AppDictionary
{
private:
	std::vector<std::vector<std::string>>									m_kanaRowsDictionary;
	std::map<int, Kanji*>													m_kanjiDictionary;
	std::map<int, DictionaryWord*>											m_wordsDictionary;
	std::map<int, InventoryItem*>											m_itemsDictionary;
	std::map<std::string, Triad<std::string, std::string, std::string>> 	m_keyboardDictionary;	// 'key' -> <hira, kata, romaji>

	// singleton object
	static AppDictionary*													s_dictionary;
	static std::string														s_extention;
	
private:
	void																	loadAll(const std::string& path);

	void																	loadKanaRows(const std::string& filename);
	void																	loadKanji(const std::string& filename);
	void																	loadWords(const std::string& filename);
	void																	loadItems(const std::string& filename);
	void																	loadKanaKeyboardTable(const std::string& filename);

public:
	AppDictionary();
	// ~AppDictionary();

	void																	init();

	static AppDictionary*													getInstance();

	std::vector<std::vector<std::string>>									getKanaRowsDictionary();
	std::map<int, Kanji*>													getKanjiDictionary();
	std::map<int, DictionaryWord*>											getWordsDictionary();
	std::map<int, InventoryItem*>											getItemsDictionary();
	std::map<std::string, Triad<std::string, std::string, std::string>> 	getKeyboardDictionary();
	
	Kanji*																	getKanjiByID(int);
	DictionaryWord*															getWordByID(int);
	InventoryItem*															getItemByID(int);

	std::vector<Kanji*>														getKanjiByRomaji(const std::string&);

	std::vector<DictionaryWord*>											getWordsByRomaji(const std::string&);
	std::vector<DictionaryWord*>											getWordsByKana(const std::string&);

	InventoryItem*															getItemByName(const std::string&);

	std::string											 					getHiraganaByLatin(const std::string&);
	std::string											 					getKatakanaByLatin(const std::string&);

	std::string																getKeyButtonByRomaji(const std::string&);

};
