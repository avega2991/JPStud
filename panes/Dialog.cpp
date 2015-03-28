#include "panes\Dialog.h"

USING_NS_CC;


PlayerDialog::PlayerDialog()
{
	m_dialogTree = new DialogTree();

	Sprite* dialogBackground = Sprite::create("textures/interface/dialog/background.png");
	dialogBackground->setPosition(Vec2(0, 0));
	dialogBackground->setAnchorPoint(Vec2(0, 0));
	dialogBackground->setTag(DIALOG_BACKGROUND);
	
	m_dialogHeader = Label::createWithTTF("<HEADER>", "fonts/Xerox Serif Wide.ttf", 18);
	m_dialogHeader->setAnchorPoint(Vec2(0, 0));
	m_dialogHeader->setPosition(Vec2(5, dialogBackground->getContentSize().height));

	m_dialogText = Label::createWithTTF("\n", "fonts/Xerox Sans Serif Wide Oblique.ttf", 18);
	m_dialogText->setAnchorPoint(Vec2(0, 1));
	m_dialogText->setPosition(Vec2(10, dialogBackground->getContentSize().height - 10));
	
	MenuItemFont::setFontSize(18);
	auto talk = MenuItemFont::create("Talk!", CC_CALLBACK_1(PlayerDialog::dialogBeginCallback, this));
	m_dialogMenu = Menu::create(talk, nullptr);
	m_dialogMenu->setAnchorPoint(Vec2(0, 0));
	m_dialogMenu->setPosition(Vec2(30, dialogBackground->getContentSize().height - 15));
	
	this->addChild(dialogBackground, DIALOG_BACKGROUND_ORDER);
	this->addChild(m_dialogHeader, DIALOG_TEXT_ORDER);
	this->addChild(m_dialogText, DIALOG_TEXT_ORDER);
	this->addChild(m_dialogMenu, DIALOG_MENU_ORDER);
}

PlayerDialog::~PlayerDialog()
{
	//_eventDispatcher->removeEventListener(m_listener);

	this->removeAllChildrenWithCleanup(true);
	this->removeFromParentAndCleanup(true);
}

PlayerDialog*	PlayerDialog::create()
{
	PlayerDialog* pDialog = new PlayerDialog();

	if (pDialog->init())
	{
		pDialog->autorelease();
		return pDialog;
	}

	CC_SAFE_DELETE(pDialog);
	return nullptr;
}

PlayerDialog*	PlayerDialog::create(const std::string& text)
{
	PlayerDialog* pDialog = new PlayerDialog();

	if (pDialog->init())
	{
		pDialog->autorelease();
		pDialog->setCurrentText(text);
		return pDialog;
	}

	CC_SAFE_DELETE(pDialog);
	return nullptr;
}

// GET
Label*	PlayerDialog::getHeaderText()
{
	return m_dialogHeader;
}

Label*	PlayerDialog::getCurrentText()
{
	return m_dialogText;
}

Menu*	PlayerDialog::getCurrentMenu()
{
	return m_dialogMenu;
}

std::string	PlayerDialog::getCurrentLang()
{
	return m_currentLang;
}

// SET
void	PlayerDialog::setHeaderText(const std::string& text)
{
	m_dialogHeader->setString(text);
}

void	PlayerDialog::setCurrentText(const std::string& text)
{
	m_dialogText->setString(text);
}

void	PlayerDialog::setCurrentMenu(Menu* pMenu)
{
	m_dialogMenu = pMenu;
}

void	PlayerDialog::setCurrentLang(const std::string& lang)
{
	m_currentLang = lang;
}
//

bool	PlayerDialog::loadDialogFromFile(const std::string& filename)
{
	std::string lang = filename.substr(filename.find(".") - 3, 3);

	if (lang == "eng")
		m_dialogText->setSystemFontName("Xerox Sans Serif Wide Oblique");
	else
		m_dialogText->setSystemFontName("Marker Felt");
		
	m_dialogText->setSystemFontSize(18);
	this->setCurrentLang(lang);

	m_dialogTree->push(filename);
	return true;
}

// SUBFUNCTIONS && CALLBACKS
void	PlayerDialog::dialogBeginCallback(Ref* pSender)
{
	this->removeChild(m_dialogMenu, true);

	this->setCurrentText( m_dialogTree->getCurrentNodeText() );

	Vector<MenuItem* > menuVector(m_dialogTree->getAnswers().size());
	for (int i = 0; i < menuVector.capacity(); i++)
	{
		std::string text = (m_dialogTree->getAnswers())[i];
		MenuItemFont* menuItem = MenuItemFont::create(text,
			CC_CALLBACK_1(PlayerDialog::switchDialogCallback, this));
		menuItem->setTag(i);
		menuVector.pushBack(menuItem);
	}

	Sprite* dialogBackground = (Sprite*) this->getChildByTag(DIALOG_BACKGROUND);

	if (menuVector.size() != 0)
		dialogBackground->setTexture("textures/interface/dialog/background_with_answers.png");
	else
		dialogBackground->setTexture("textures/interface/dialog/background.png");

	m_dialogMenu = Menu::createWithArray(menuVector);
	m_dialogMenu->alignItemsHorizontally();
	m_dialogMenu->setPosition(dialogBackground->getPosition().x + dialogBackground->getContentSize().width / 2, 15);
	this->addChild(m_dialogMenu, DIALOG_MENU_ORDER);
}

void	PlayerDialog::switchDialogCallback(cocos2d::Ref* pSender)
{
	// get index of an answer and switch to it
	m_dialogTree->nextNode(((MenuItem*)pSender)->getTag());
	this->dialogBeginCallback(pSender);
}
