#pragma once

#include "cocos2d.h"

#include "support\DialogTree.h"
#include "support\ConstValues.h"

// layer objects' order
#define DIALOG_BACKGROUND_ORDER				1
#define DIALOG_TEXT_ORDER					2
#define DIALOG_MENU_ORDER					3

class PlayerDialog : public cocos2d::Layer
{
private:
	DialogTree*										m_dialogTree;
	TreeNode*										m_currentNode;

	cocos2d::Label*									m_dialogHeader;
	cocos2d::Label*									m_dialogText;
	cocos2d::Menu*									m_dialogMenu;

	std::string										m_currentLang;

public:
	PlayerDialog();
	~PlayerDialog();

	static PlayerDialog*							create();
	static PlayerDialog*							create(const std::string&);
	void											closeDialog();

	cocos2d::Label*									getHeaderText();
	cocos2d::Label*									getCurrentText();
	cocos2d::Menu*									getCurrentMenu();
	DialogTree*										getDialogTree();
	std::string										getCurrentLang();

	void											setHeaderText(const std::string&);
	void											setCurrentText(const std::string&);
	void											setCurrentMenu(cocos2d::Menu*);
	void											setCurrentLang(const std::string&);

	bool											loadDialogFromFile(const std::string&);
		
	// SUBFUNCTIONS && CALLBACKS
	void											dialogBeginCallback(cocos2d::Ref*);
	void											switchDialogCallback(cocos2d::Ref*);
};
