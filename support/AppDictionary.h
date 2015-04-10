#pragma once

#include "cocos2d.h"
#include <map>
#include <vector>
#include <fstream>

#include "support\Kanji.h"
#include "support\Word.h"
#include "sprites\items\Item.h"
#include "support\AppLib.h"
#include "support\GLAddition.h"

#define KANJI_SEARCH_COLLISION_MAX_ERROR									6
#define KANJI_SEARCH_MAX_RESULT												9

typedef int ID;


class AppDictionary
{
private:
	std::vector<std::vector<std::string>>									m_kanaRowsDictionary;	// kana rows by it's order (romaji)
	std::map<ID, Kanji*>													m_kanjiDictionary;
	std::map<ID, DictionaryWord*>											m_wordsDictionary;
	std::map<ID, InventoryItem*>											m_itemsDictionary;
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
	std::map<ID, Kanji*>													getKanjiDictionary();
	std::map<ID, DictionaryWord*>											getWordsDictionary();
	std::map<ID, InventoryItem*>											getItemsDictionary();
	std::map<std::string, Triad<std::string, std::string, std::string>> 	getKeyboardDictionary();
	
	Kanji*																	getKanjiByID(ID);
	DictionaryWord*															getWordByID(ID);
	InventoryItem*															getItemByID(ID);

	std::vector<Kanji*>														getKanjiByRomaji(const std::string&);
	Kanji*																	getKanjiBySym(const std::string& kanjiSym);
	std::vector<Kanji*>														getKanjiByImage(const cocos2d::Rect& area);

	std::vector<DictionaryWord*>											getWordsByRomaji(const std::string&);
	std::vector<DictionaryWord*>											getWordsByKana(const std::string&);

	InventoryItem*															getItemByName(const std::string&);

	std::string											 					getHiraganaByLatin(const std::string&);
	std::string											 					getKatakanaByLatin(const std::string&);

	std::string																getKeyButtonByRomaji(const std::string&);

};
