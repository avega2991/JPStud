#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "ui\CocosGUI.h"

#include "panes\interface\DictionaryInterface.h"
#include "panes\interface\StatusInterface.h"
#include "sprites\Player.h"

#define BIAS																	4

#define LBACKPACK																101
#define LBOOK																	102
#define LSTATUS																	103
#define LEXIT																	104
#define BCONFIRM																151
#define BCLOSE																	152


class PlayerInterface : public cocos2d::Layer
{
private:
	cocos2d::EventListenerTouchOneByOne*										m_listener;
	cocos2d::Sprite*															m_placeholder;
	cocos2d::ui::LoadingBar*													m_progressBar;
	cocos2d::Menu*																m_interfaceMenu;
	cocos2d::Label*																m_levelLabel;
	cocos2d::Label*																m_percentageLabel;

	cocos2d::Layer*																m_exitMenuLayer;
	cocos2d::Menu*																m_exitMenu;
	cocos2d::Sprite*															m_exitMenuPlaceholder;
	cocos2d::Sprite*															m_buttonPlaceholder;

	cocos2d::Layer*																m_currentSubmenuLayer;
	int																			m_currentSubmenuTag;

	CocosDenshion::SimpleAudioEngine*											m_soundEngine;

	// PERSONAL OPTIONS
	// static Inventory*														m_inventory;
	// 

private:
	// CALLBACKS
	void																		submenuCustomCallback(Ref*);
	void																		menuExitCallback(Ref*);

	// SUBFUNCTIONS
	Layer*																		_createSelectedSubmenu(int);
	Layer*																		_createInventory();
	Layer*																		_createDictionary();
	Layer*																		_createStatusMenu();
	Layer*																		_createExitMenu();

	void																		_closeProgram();
	void																		_toExitScene();


public:
	PlayerInterface();
	// ~PlayerInterface();
	
	static PlayerInterface*														create();

	cocos2d::Menu*																getExitMenu();
	cocos2d::Sprite*															getExitMenuPlaceholder();
	cocos2d::Layer*																getExitMenuLayer();
	cocos2d::Sprite*															getButtonPlaceholder();

	cocos2d::Layer*																getOpenedSubmenuLayer();

	void																		updatePercentage();

	//DEPRECATED
	bool																		onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
};
