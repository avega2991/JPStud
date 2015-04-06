#include "panes\PopupMenu.h"

USING_NS_CC;


PopupMenu::PopupMenu()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Sprite* popupBackground = Sprite::create("textures/interface/popup/popupmenu_background.png");
	popupBackground->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - POPUP_VERTICAL_PX_OFFSET));
	popupBackground->setTag(POPUP_BACKGROUND);

	m_popupHeader = Label::createWithTTF("<HEADER>", "fonts/Xerox Serif Wide.ttf", 18);
	m_popupHeader->setAnchorPoint(Vec2(0.5f, 0));
	m_popupHeader->setPosition(Vec2(popupBackground->getPosition().x,
		popupBackground->getPosition().y + popupBackground->getContentSize().height / 2));

	m_popupText = Label::createWithTTF("\n", "fonts/Xerox Sans Serif Wide Oblique.ttf", 18);
	m_popupText->setAnchorPoint(Vec2(0, 1));
	m_popupText->setPosition(Vec2(popupBackground->getPosition().x - popupBackground->getContentSize().width / 2 + POPUP_BUTTON_PX_OFFSET,
		popupBackground->getPosition().y + popupBackground->getContentSize().height / 2 - POPUP_VERTICAL_PX_OFFSET));

	MenuItemFont::setFontSize(18);
	auto ok = MenuItemFont::create("OK!", CC_CALLBACK_1(PopupMenu::closePopupCallback, this));
	m_popupMenu = Menu::create(ok, nullptr);
	m_popupMenu->setAnchorPoint(Vec2(0, 0));
	m_popupMenu->setPosition(Vec2(popupBackground->getPosition().x + popupBackground->getContentSize().width / 2 - POPUP_BUTTON_PX_OFFSET,
		popupBackground->getPosition().y - popupBackground->getContentSize().height / 2 + POPUP_BUTTON_PX_OFFSET));
	
	this->addChild(popupBackground, POPUP_BACKGROUND_ORDER);
	this->addChild(m_popupHeader, POPUP_TEXT_ORDER);
	this->addChild(m_popupText, POPUP_TEXT_ORDER);
	this->addChild(m_popupMenu, POPUP_MENU_ORDER);

	this->schedule(schedule_selector(PopupMenu::onCreate));
}

PopupMenu::PopupMenu(float x, float y, float width, float height)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Sprite* popupBackground = Sprite::create("textures/interface/popup/popupmenu_background.png",
		Rect(0, 0, width, height));
	popupBackground->setPosition(Vec2(x, y - POPUP_VERTICAL_PX_OFFSET));
	popupBackground->setTag(POPUP_BACKGROUND);

	m_popupHeader = Label::createWithTTF("<HEADER>", "fonts/Xerox Serif Wide.ttf", 18);
	m_popupHeader->setAnchorPoint(Vec2(0.5f, 0));
	m_popupHeader->setPosition(Vec2(popupBackground->getPosition().x,
		popupBackground->getPosition().y + popupBackground->getContentSize().height / 2));

	m_popupText = Label::createWithTTF("\n", "fonts/Xerox Sans Serif Wide Oblique.ttf", 16);
	m_popupText->setAnchorPoint(Vec2(0, 1));
	m_popupText->setPosition(Vec2(popupBackground->getPosition().x - popupBackground->getContentSize().width / 2 + POPUP_BUTTON_PX_OFFSET,
		popupBackground->getPosition().y + popupBackground->getContentSize().height / 2 
		- POPUP_VERTICAL_PX_OFFSET * (height / popupBackground->getTexture()->getContentSize().height)));

	MenuItemFont::setFontSize(18);
	auto ok = MenuItemFont::create("OK!", CC_CALLBACK_1(PopupMenu::closePopupCallback, this));
	m_popupMenu = Menu::create(ok, nullptr);
	m_popupMenu->setAnchorPoint(Vec2(0, 0));
	m_popupMenu->setPosition(Vec2(popupBackground->getPosition().x + popupBackground->getContentSize().width / 2 - POPUP_BUTTON_PX_OFFSET,
		popupBackground->getPosition().y - popupBackground->getContentSize().height / 2 + POPUP_BUTTON_PX_OFFSET));

	this->addChild(popupBackground, POPUP_BACKGROUND_ORDER);
	this->addChild(m_popupHeader, POPUP_TEXT_ORDER);
	this->addChild(m_popupText, POPUP_TEXT_ORDER);
	this->addChild(m_popupMenu, POPUP_MENU_ORDER);

	this->schedule(schedule_selector(PopupMenu::onCreate));
}

PopupMenu::PopupMenu(const std::string& backgroundFilename, float x, float y)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Sprite* popupBackground = Sprite::create(backgroundFilename);
	popupBackground->setPosition(Vec2(x, y - POPUP_VERTICAL_PX_OFFSET));
	popupBackground->setTag(POPUP_BACKGROUND);

	m_popupHeader = Label::createWithTTF("\n", "fonts/Xerox Serif Wide.ttf", 18);
	m_popupHeader->setAnchorPoint(Vec2(0.5f, 0));
	m_popupHeader->setPosition(Vec2(popupBackground->getPosition().x,
		popupBackground->getPosition().y + popupBackground->getContentSize().height / 2));

	m_popupText = Label::createWithTTF("\n", "fonts/Xerox Sans Serif Wide Oblique.ttf", 16);
	m_popupText->setAnchorPoint(Vec2(0, 1));
	m_popupText->setPosition(Vec2(popupBackground->getPosition().x - popupBackground->getContentSize().width / 2 + POPUP_BUTTON_PX_OFFSET,
		popupBackground->getPosition().y + popupBackground->getContentSize().height / 2 - POPUP_VERTICAL_PX_OFFSET));

	MenuItemFont::setFontSize(18);
	auto ok = MenuItemFont::create("OK!", CC_CALLBACK_1(PopupMenu::closePopupCallback, this));
	m_popupMenu = Menu::create(ok, nullptr);
	m_popupMenu->setAnchorPoint(Vec2(0, 0));
	m_popupMenu->setPosition(Vec2(popupBackground->getPosition().x + popupBackground->getContentSize().width / 2 - POPUP_BUTTON_PX_OFFSET,
		popupBackground->getPosition().y - popupBackground->getContentSize().height / 2 - POPUP_BUTTON_PX_OFFSET / 2));

	this->addChild(popupBackground, POPUP_BACKGROUND_ORDER);
	this->addChild(m_popupHeader, POPUP_TEXT_ORDER);
	this->addChild(m_popupText, POPUP_TEXT_ORDER);
	this->addChild(m_popupMenu, POPUP_MENU_ORDER);

	this->setContentSize(popupBackground->getContentSize());

	this->schedule(schedule_selector(PopupMenu::onCreate));
}

PopupMenu::~PopupMenu()
{
	this->removeAllChildrenWithCleanup(true);
	this->removeFromParentAndCleanup(true);
}

PopupMenu*	PopupMenu::create()
{
	PopupMenu* pPopup = new PopupMenu();

	if (pPopup->init())
	{
		pPopup->autorelease();
		return pPopup;
	}

	CC_SAFE_DELETE(pPopup);
	return nullptr;
}

PopupMenu*	PopupMenu::create(float x, float y, float width, float height)
{
	PopupMenu* pPopup = new PopupMenu(x, y, width, height);

	if (pPopup->init())
	{
		pPopup->autorelease();
		return pPopup;
	}

	CC_SAFE_DELETE(pPopup);
	return nullptr;
}

PopupMenu*	PopupMenu::create(const std::string& text)
{
	PopupMenu* pPopup = new PopupMenu();

	if (pPopup->init())
	{
		pPopup->autorelease();
		pPopup->setCurrentText(text);
		return pPopup;
	}

	CC_SAFE_DELETE(pPopup);
	return nullptr;
}

PopupMenu*	PopupMenu::create(const std::string& backgroundFilename, float x, float y)
{
	PopupMenu* pPopup = new PopupMenu(backgroundFilename, x, y);

	if (pPopup->init())
	{
		pPopup->autorelease();
		return pPopup;
	}

	CC_SAFE_DELETE(pPopup);
	return nullptr;
}

void	PopupMenu::closePopup()
{
	this->closePopupCallback(nullptr);
}

// <GET>
Label*	PopupMenu::getHeaderText()
{
	return m_popupHeader;
}

Label*	PopupMenu::getCurrentText()
{
	return m_popupText;
}

Menu*	PopupMenu::getCurrentMenu()
{
	return m_popupMenu;
}
// </GET>

// <SET>
void	PopupMenu::setHeaderText(const std::string& text)
{
	m_popupHeader->setString(text);
}

void	PopupMenu::setCurrentText(const std::string& text)
{
	m_popupText->setString(text);
}
// </SET>

void	PopupMenu::enableAutoClose(bool bEnable)
{
	if (bEnable)
		m_popupMenu->removeFromParent();
	else
		this->addChild(m_popupMenu, POPUP_MENU_ORDER);
}

// SUBFUNCTIONS && CALLBACKS
void	PopupMenu::closePopupCallback(Ref* pSender)
{
	auto move = EaseOut::create(MoveBy::create(POPUP_APPEARANCE_ANIMATION_DURATION, Vec2(0, POPUP_VERTICAL_PX_OFFSET)), 3);
	move->setTag(ACTION_POPUP_MOVE);
	this->setCascadeOpacityEnabled(true);

	this->runAction(FadeOut::create(POPUP_APPEARANCE_ANIMATION_DURATION));
	this->runAction(move);

	this->schedule(schedule_selector(PopupMenu::onDestroy));
}

void	PopupMenu::onCreate(float dt)
{
	if (this->getParent())
	{
		//play sound effect
		
		//
		auto move = MoveBy::create(POPUP_APPEARANCE_ANIMATION_DURATION, Vec2(0, POPUP_VERTICAL_PX_OFFSET));
		this->setCascadeOpacityEnabled(true);
		this->setOpacity(0);

		//this->runAction(FadeIn::create(POPUP_APPEARANCE_ANIMATION_DURATION)); // NOT WORKING!!!
		this->schedule(schedule_selector(PopupMenu::_fadeIn), 0.01f);
		this->runAction(EaseOut::create(move, 3));

		this->unschedule(schedule_selector(PopupMenu::onCreate));
	}
}

void	PopupMenu::onDestroy(float dt)
{
	if (this->getActionByTag(ACTION_POPUP_MOVE) == nullptr)
	{
		this->unschedule(schedule_selector(PopupMenu::onDestroy));

		this->removeAllChildrenWithCleanup(true);
		this->removeFromParentAndCleanup(true);
	}
}

void	PopupMenu::_fadeIn(float dt)
{
	static short frame = 0;
	if (frame < POPUP_APPEARANCE_ANIMATION_DURATION * 100)
	{
		this->setOpacity(frame * 8.5f);
		frame++;
	}
	else
	{
		this->unschedule(schedule_selector(PopupMenu::_fadeIn));
		frame = 0;
	}
}