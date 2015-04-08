#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "panes\Canvas.h"
#include "panes\PopupMenu.h"
#include "support\AppDictionary.h"
#include "support\Kanji.h"
#include "support\GLAddition.h"

// ORDERS
#define DICTIONARY_MENU_ORDER									1
#define DICTIONARY_PAGE_ORDER									2
#define DICTIONARY_TAB_LAYER_ORDER								3
#define DICTIONARY_LABEL_ORDER									4
#define DICTIONARY_HINT_ORDER									4
#define DICTIONARY_KANA_PAGE_UNDERLAYER_ORDER					5
#define DICTIONARY_KANA_PAGE_LAYER_ORDER						6
#define DICTIONARY_KANA_PAGE_HINT_ORDER							7

#define KANA_PAGE_BACKGROUND_ORDER								1
#define KANA_PAGE_SPRITE_ORDER									2
#define KANA_PAGE_HINT_ORDER									3
#define KANA_PAGE_MENU_LABEL_ORDER								4

#define KANJI_TAB_RESULT_LAYER_ORDER							1
#define KANJI_TAB_SPRITE_BORDER_ORDER							2
#define KANJI_TAB_SPRITE_ORDER									3
#define KANJI_TAB_HINT_ORDER									4

// LAYER
#define DICTIONARY_TAB_LAYER									10
#define DICTIONARY_HINT											11
#define DICTIONARY_KANA_PAGE_UNDERLAYER							12
#define DICTIONARY_KANA_PAGE_LAYER								13
#define DICTIONARY_KANA_PAGE_HINT								14

#define KANJI_TAB_SEARCH_RESULT_LAYER							20

#define KANA_PAGE_BACKGROUND									30
#define KANA_PAGE_SPRITE										31
#define KANA_PAGE_HINT											32
// #define KANA_PAGE_MENU_LABEL									33
#define KANA_PAGE_OUTLINE										34
#define KANA_PAGE_BRUSH_SCALEDOWN								35
#define KANA_PAGE_BRUSH_SCALEUP									36
#define KANA_PAGE_BRUSH_DEPTH_HINT								37
#define KANA_PAGE_EXAMPLE										38


// DICTIONARY TABMENU BUTTONS
#define DB_KANJI												101
#define DB_WORDS												102
#define DB_GRAMMAR												103
#define DB_KANA													104

// DICTIONARY LABELS
#define DL_KANJI												201
#define DL_WORDS												202
#define DL_GRAMMAR												203
#define DL_KANA													204

// INPUT TYPES
#define	DICTIONARY_KANA_TYPE_HIRAGANA							301
#define DICTIONARY_KANA_TYPE_KATAKANA							302
#define DICTIONARY_KANJI_INPUT_TYPE_IMAGE						311
#define DICTIONARY_KANJI_INPUT_TYPE_TEXT						312

// OTHER TAGS
#define DICTIONARY_PAGE_ONE										401
#define DICTIONARY_PAGE_TWO										402
#define DICTIONARY_TEXTFIELD									411
#define DICTIONARY_TABMENU										421
#define DICTIONARY_SEARCH_RESULT								431
#define DICIONARY_KANJI_HELPER									441
#define DICIONARY_WORDS_HELPER									442

// CONSTANTS
#define KANA_ANIMATION_MAX_FRAMES								48
#define	KANA_PAGE_BUTTON_VERTICAL_OFFSET						7


class DictionaryInterface : public cocos2d::Layer
{
private:
	const int													c_alignOffset = 12;
	const int													c_stringMaxLength = 20;
	const int													c_promptStringLength = 22;
	const cocos2d::Vec2											c_splitLinePosition = cocos2d::Vec2(200, 112);

	cocos2d::Layer*												m_tabLayer;
	Canvas*														m_canvas;
	short														m_currentTab;

	short														m_currentKanaType;
	short														m_currentKanjiInputType;

	// WORDS TAB
	std::vector<std::string>									m_kanaString;

	// KANA TAB
	std::string													m_currentKanaSpriteInitFilename;
	std::string													m_currentKanaPage;
	short														m_kanaPageBrushDepth;

private:
	void														switchCurrentTab(BYTE tabTag);

	// <CALLBACKS>
	void														tabmenuCallback(Ref*);
	void														kanaTypeMenuCallback(Ref*);
	// KANJI TAB CALLBACKS
	void														switchKanjiInputTypeCallback(Ref*);
	void														kanjiEnterButtonCallback(Ref*);
	void														searchResultButtonCallback(Ref*);
	// WORDS TAB CALLBACKS
	void														wordEnterButtonCallback(Ref*);
	// KANA TAB CALLBACKS
	void														kanaRowsCallback(Ref*);
	void														closeButtonCallback(Ref*);
	void														clearCanvasButtonCallback(Ref*);
	void														setOutlineButtonCallback(Ref*);
	void														brushScaleButtonCallback(Ref*);

	void														onEachFrameExampleView(float);
	// OTHER CALLBACKS
	void														helpButtonCallback(Ref*);
	// </CALLBACKS>

	void														onEachFrameWordTab(float);
	
	// <SUBFUNCTIONS>
	void														_createKanjiTab();
	void														_createKanjiResults();
	void														_createWordsTab();
	void														_createGrammarTab();
	void														_createKanaTab();

	void														_underlayerAfterFadeOut();
	// </SUBFUNCTIONS>

	// <ONLY_FOR_DEVELOPMENT>
	void														teachKanjiSystemSinceID(int startID);
	// </ONLY_FOR_DEVELOPMENT>

public:
	DictionaryInterface();
	~DictionaryInterface();

	static DictionaryInterface*									create();

};
