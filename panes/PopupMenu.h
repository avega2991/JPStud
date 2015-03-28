#pragma once

#include "cocos2d.h"

#include "support\ConstValues.h"

// layer objects' order
#define POPUP_BACKGROUND_ORDER						1
#define POPUP_TEXT_ORDER							2
#define POPUP_MENU_ORDER							3

#define POPUP_VERTICAL_PX_OFFSET					20
#define POPUP_BUTTON_PX_OFFSET						25
#define POPUP_APPEARANCE_ANIMATION_DURATION			0.3f

#define ACTION_POPUP_MOVE							100


class PopupMenu : public cocos2d::Layer
{
private:
	cocos2d::Label*									m_popupHeader;
	cocos2d::Label*									m_popupText;
	cocos2d::Menu*									m_popupMenu; // contains only 'OK' button
	
public:
	PopupMenu();
	PopupMenu(float x, float y, float width, float height);
	PopupMenu(const std::string& backgroundFilename, float x, float y);
	~PopupMenu();

	static PopupMenu*								create();
	static PopupMenu*								create(const std::string& text);
	static PopupMenu*								create(float x, float y, float width, float height);
	static PopupMenu*								create(const std::string& backgroundFilename, float x, float y);

	void											closePopup();

	cocos2d::Label*									getHeaderText();
	cocos2d::Label*									getCurrentText();
	cocos2d::Menu*									getCurrentMenu();

	void											setHeaderText(const std::string&);
	void											setCurrentText(const std::string&);
	void											setCurrentMenu(cocos2d::Menu*);
	
	// SUBFUNCTIONS && CALLBACKS
	void											closePopupCallback(Ref* pSender);
	void											onCreate(float dt);
	void											onDestroy(float dt);

	void											_fadeIn(float duration);
};
