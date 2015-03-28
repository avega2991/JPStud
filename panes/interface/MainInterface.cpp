#include "panes\interface\MainInterface.h"

#include "scenes\ExitScene.h"
#include "scenes\FirstScene.h"

USING_NS_CC;

PlayerInterface::PlayerInterface()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	Player* player = Player::getInstance();
	short playerLevel = player->getPlayerLevel();
	long playerExp = player->getPlayerExp();
	long playerExpToLevel = player->getPlayerExpToLevel();

	auto backpack = MenuItemImage::create("textures/interface/player/bagpack00.png", 
		"textures/interface/player/bagpack01.png",
		CC_CALLBACK_1(PlayerInterface::submenuCustomCallback, this));
	auto dictionary = MenuItemImage::create("textures/interface/player/scroll00.png", 
		"textures/interface/player/scroll01.png",
		CC_CALLBACK_1(PlayerInterface::submenuCustomCallback, this));
	auto status = MenuItemImage::create("textures/interface/player/pers00.png", 
		"textures/interface/player/pers01.png",
		CC_CALLBACK_1(PlayerInterface::submenuCustomCallback, this));
	auto exit = MenuItemImage::create("textures/interface/player/exit00.png", 
		"textures/interface/player/exit01.png",
		CC_CALLBACK_1(PlayerInterface::submenuCustomCallback, this));

	backpack->setTag(LBACKPACK);
	dictionary->setTag(LBOOK);
	status->setTag(LSTATUS);
	exit->setTag(LEXIT);

	backpack->setPosition(Vec2(BIAS, 0));
	dictionary->setPosition(Vec2(backpack->getContentSize().width + backpack->getPosition().x + BIAS / 2 * 3, 0));
	status->setPosition(Vec2(dictionary->getContentSize().width + dictionary->getPosition().x + BIAS / 2 * 3 + BIAS / 2, 0));
	exit->setPosition(Vec2(status->getContentSize().width + status->getPosition().x + BIAS / 2 * 3 + BIAS / 2, 0));

	m_interfaceMenu = Menu::create(backpack, dictionary, status, exit, NULL);
	m_interfaceMenu->setPosition(Vec2(visibleSize.width - 182, 53));
	
	//progress bar and empty placeholder
	Vec2 placeholderPosition = Vec2(visibleSize.width - 205, 27);

	m_progressBar = cocos2d::ui::LoadingBar::create();
	m_progressBar->setName("ProgressBar");
	m_progressBar->loadTexture("textures/interface/scaryholder_fullpercentage.png");
	m_progressBar->setPercent(Player::getInstance()->getPlayerExp() / Player::getInstance()->getPlayerExpToLevel());
	m_progressBar->setAnchorPoint(Vec2(0, 0));
	m_progressBar->setPosition(placeholderPosition);
	m_progressBar->setName("progressBar");

	m_placeholder = Sprite::create("textures/interface/scaryholder.png"); //"textures/interface/ico_placeholder.png");
	m_placeholder->setAnchorPoint(Vec2(0, 0));
	m_placeholder->setPosition(placeholderPosition);

	m_levelLabel = Label::createWithSystemFont("LV. " + std::to_string(playerLevel), "Arial", 14);
	m_levelLabel->setAnchorPoint(Vec2(0, 0));
	m_levelLabel->setPosition(Vec2(placeholderPosition.x,
		placeholderPosition.y - m_levelLabel->getContentSize().height));
	m_levelLabel->setName("levelLabel");

	m_percentageLabel = Label::createWithSystemFont("EXP: " + std::to_string(playerExp / playerExpToLevel) + "%", "Arial", 18);
	m_percentageLabel->setAnchorPoint(Vec2(1, 0));
	m_percentageLabel->setPosition(Vec2(placeholderPosition.x + m_placeholder->getContentSize().width,
		placeholderPosition.y - m_percentageLabel->getContentSize().height));
	m_percentageLabel->setName("percentageLabel");

	this->addChild(m_placeholder, 1);
	this->addChild(m_progressBar, 2);
	this->addChild(m_interfaceMenu, 3);
	this->addChild(m_levelLabel, 3);
	this->addChild(m_percentageLabel, 3);

	m_currentSubmenuTag = NULL;

	//audio init
	m_soundEngine = CocosDenshion::SimpleAudioEngine::getInstance();
	//m_soundEngine->preloadEffect("soundeffects/UI/complete.mp3");
		
}

PlayerInterface* PlayerInterface::create()
{
	PlayerInterface* playerInterface = new PlayerInterface();

	if (playerInterface->init())
	{
		playerInterface->autorelease();
		return playerInterface;
	}

	CC_SAFE_DELETE(playerInterface);
	return nullptr;
	
}

Menu* PlayerInterface::getExitMenu()
{
	return m_exitMenu;
}

Sprite* PlayerInterface::getExitMenuPlaceholder()
{
	return m_exitMenuPlaceholder;
}

Sprite* PlayerInterface::getButtonPlaceholder()
{
	return m_buttonPlaceholder;
}

Layer* PlayerInterface::getOpenedSubmenuLayer()
{
	return m_currentSubmenuLayer;
}

void	PlayerInterface::updatePercentage()
{
	Player* player = Player::getInstance();
	int expPercentage = player->getPlayerExp() / player->getPlayerExpToLevel();
	m_percentageLabel->setString("EXP: " + std::to_string(expPercentage) + "%");
	m_progressBar->setPercent(expPercentage);
}

// *----------------------*
//	create/delete submenu
// *--------------------*
void	PlayerInterface::submenuCustomCallback(Ref* pSender)
{
	int tag = ((MenuItem *)(pSender))->getTag();

	auto interfaceLayer = this->getParent();
	auto submenuLayer = interfaceLayer->getChildByTag(SUBMENU_LAYER);
		
	//delete any existed submenu if BCLOSE is pressed OR other submenu is existed
	if (tag == BCLOSE || (submenuLayer != nullptr))
	{
		submenuLayer->removeFromParentAndCleanup(true);
		m_currentSubmenuLayer = nullptr;
	}

	Layer* submenu = _createSelectedSubmenu(tag);

	//else view selected submenu if it not exists
	//temp (delete 'IF' after creating all submenu layers)
	if (submenu != nullptr)
	{
		interfaceLayer->addChild(submenu, 3, SUBMENU_LAYER);
		m_currentSubmenuLayer = submenu;
	}
}

void	PlayerInterface::menuExitCallback(Ref* pSender)
{
	int tag = ((MenuItem *)(pSender))->getTag();
		
	if(tag == BCONFIRM)
		_closeProgram();
}

//SUBFUNCTIONS
Layer* PlayerInterface::_createDictionary()
{
	DictionaryInterface* dictionaryInterface = DictionaryInterface::create();

	return dictionaryInterface;
}


Layer*	PlayerInterface::_createStatusMenu()
{
	StatusInterface* statusInterface = StatusInterface::create();

	return statusInterface;
}

Layer* PlayerInterface::_createExitMenu()
{
	//INSERT LATER
	auto yes = MenuItemImage::create(
		"textures/interface/button_placeholder.png",
		"textures/interface/button_placeholder_selected.png",
		CC_CALLBACK_1(PlayerInterface::menuExitCallback, this));
	auto no = MenuItemImage::create(
		"textures/interface/button_placeholder.png",
		"textures/interface/button_placeholder_selected.png",
		CC_CALLBACK_1(PlayerInterface::submenuCustomCallback, this));
	auto close = MenuItemImage::create(
		"textures/interface/button_close.png",
		"textures/interface/button_close_selected.png",
		CC_CALLBACK_1(PlayerInterface::submenuCustomCallback, this));

	yes->setTag(BCONFIRM);
	no->setTag(BCLOSE);
	close->setTag(BCLOSE);

	//placeholder for exit menu
	Vec2 exitPlaceholderPosition = Vec2(m_placeholder->getPosition().x,
		m_placeholder->getPosition().y + m_placeholder->getContentSize().height + BIAS);

	m_exitMenuPlaceholder = Sprite::create("textures/interface/exitmenu_placeholder.png");
	m_exitMenuPlaceholder->setAnchorPoint(Vec2(0, 0));
	m_exitMenuPlaceholder->setPosition(exitPlaceholderPosition);

	yes->setAnchorPoint(Vec2(0, 0));
	yes->setPosition(Vec2(yes->getContentSize().width * 2 / 3, BIAS));
	no->setAnchorPoint(Vec2(1, 0));
	no->setPosition(Vec2(m_exitMenuPlaceholder->getContentSize().width - yes->getContentSize().width * 2 / 3, BIAS));
	close->setAnchorPoint(Vec2(1, 1));
	close->setPosition(Vec2(m_exitMenuPlaceholder->getContentSize().width,
		m_exitMenuPlaceholder->getContentSize().height));

	m_exitMenu = Menu::create(yes, no, close, NULL);
	m_exitMenu->setContentSize(m_exitMenuPlaceholder->getContentSize());
	m_exitMenu->setPosition(exitPlaceholderPosition);
	m_exitMenu->setName("exitMenu");

	auto labelText = Label::create("Are you sure?", "Arial", 18);
	labelText->setPosition(Vec2(exitPlaceholderPosition.x + yes->getPosition().x,
		exitPlaceholderPosition.y + yes->getContentSize().height + yes->getContentSize().height * 2 / 3));
	labelText->setAnchorPoint(Vec2(0, 0));
	auto labelYes = Label::create("Yes", "Arial", 16);
	labelYes->setPosition(Vec2(exitPlaceholderPosition.x + yes->getPosition().x + yes->getContentSize().width / 2,
		exitPlaceholderPosition.y + yes->getPosition().y + yes->getContentSize().height / 2));
	labelYes->setAnchorPoint(Vec2(0.5f, 0.5f));
	auto labelNo = Label::create("No", "Arial", 16);
	labelNo->setPosition(Vec2(exitPlaceholderPosition.x + no->getPosition().x - no->getContentSize().width / 2,
		exitPlaceholderPosition.y + no->getPosition().y + yes->getContentSize().height / 2));
	labelNo->setAnchorPoint(Vec2(0.5f, 0.5f));

	m_exitMenuLayer = Layer::create();
	m_exitMenuLayer->addChild(m_exitMenuPlaceholder, 1);
	m_exitMenuLayer->addChild(m_exitMenu, 2);
	m_exitMenuLayer->addChild(labelText, 3);
	m_exitMenuLayer->addChild(labelYes, 3);
	m_exitMenuLayer->addChild(labelNo, 3);

	return m_exitMenuLayer;
}
//TODO
Layer* PlayerInterface::_createSelectedSubmenu(int tag)
{
	if (tag == m_currentSubmenuTag)
	{
		m_currentSubmenuTag = NULL;
		return nullptr;
	}

	m_currentSubmenuTag = tag;

	switch (tag)
	{
	/*case LBACKPACK:
		return _createInventory();
		break;*/
	case LBOOK:
		return _createDictionary();
		break;
	case LSTATUS:
		return _createStatusMenu();
		break;
	case LEXIT:
		return _createExitMenu();
	default:
		//not existed menu yet
		return nullptr;
	}
}

void	PlayerInterface::_closeProgram()
{
	auto labelExit = Label::create("Quitting the program...", "fonts/Marker Felt.ttf", 24);
	labelExit->setPosition(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2);
	Director::getInstance()->getRunningScene()->addChild(labelExit, 5);
	Director::getInstance()->getRunningScene()->runAction(Sequence::create(FadeOut::create(1.0f), DelayTime::create(1.0f),
		CallFuncN::create(CC_CALLBACK_0(PlayerInterface::_toExitScene, this)), nullptr));
}

void	PlayerInterface::_toExitScene()
{
	auto scene = Scene::create();
	scene->addChild(ExitScene::create());

	m_soundEngine->playEffect("soundeffects/UI/complete.mp3");
	Director::getInstance()->replaceScene(TransitionFade::create(.5, scene));
}

//DEPRECATED
bool	PlayerInterface::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	return true;
}
