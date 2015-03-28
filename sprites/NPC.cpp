#include "sprites\NPC.h"
#include "scenes\FirstScene.h"
#include "panes\PopupMenu.h"

USING_NS_CC;


NonPlayablePerson::NonPlayablePerson()
{
	//loading .png
	SpriteBatchNode* spritebatch = SpriteBatchNode::create("textures/hero.png");

	SpriteFrameCache* cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("textures/hero.plist");

	this->addChild(spritebatch);

	m_directionState = DOWN;

	m_NPCName = "Default_Name";

	m_listener = EventListenerTouchOneByOne::create();
	m_listener->setSwallowTouches(false);
	m_listener->onTouchBegan = CC_CALLBACK_2(NonPlayablePerson::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithFixedPriority(m_listener, NPC_PRIORITY);

	this->schedule(schedule_selector(NonPlayablePerson::onEachFrame));
}

NonPlayablePerson* NonPlayablePerson::create(const std::string &filename)
{
	NonPlayablePerson* nonPlayablePerson = new NonPlayablePerson();

	if (nonPlayablePerson && nonPlayablePerson->initWithSpriteFrameName(filename))
	{
		nonPlayablePerson->autorelease();
		return nonPlayablePerson;
	}

	CC_SAFE_DELETE(nonPlayablePerson);

	return NULL;
}

std::string	NonPlayablePerson::getNPCName()
{
	return m_NPCName;
}

void NonPlayablePerson::setNPCName(const std::string& name)
{
	m_NPCName = name;
}

bool NonPlayablePerson::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	CCLOG("NPC's listener: onTouchBegan x = %f, y = %f", touch->getLocation().x, touch->getLocation().y);
	
	auto labelNpcName = this->getChildByTag(LNAME);

	static short clickNumber = 0;

	if (labelNpcName != nullptr)
	{
		this->removeChildByTag(LNAME);
		m_listener->setSwallowTouches(false);
	}

	if (this->getBoundingBox().containsPoint(touch->getLocation()))
	{
		// first or second click
		clickNumber++;
		clickNumber %= 2;

		// disable/enable player's movement
		if (clickNumber == 1)
			m_listener->setSwallowTouches(true);
		else
			m_listener->setSwallowTouches(false);

		// create label under head of NPC
		auto NPCLabel = Label::create(m_NPCName, "Arial", 14);
		NPCLabel->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height + 3 * BIAS));
		this->addChild(NPCLabel, 2, LNAME);
	}
	else
	{
		clickNumber = 0;
	}
	
	return true;
}

void	NonPlayablePerson::onEachFrame(float dt)
{
	if (this->getParent() == nullptr)
		return;

	auto playerLayer = this->getParent();
	auto player = playerLayer->getChildByTag(PLAYER);

	auto interfaceLayer = playerLayer->getParent()->getChildByTag(INTERFACE_LAYER);

	static bool playerIsNear = false;

	if (geo::Line::length(&player->getPosition(), &this->getPosition()) < player->getContentSize().height)
	{
		if (!playerIsNear)
		{
			playerIsNear = true;
			CCLOG("NPC's listener: player has been reached the NPC"); // panel with the offer to talk instead

			PlayerDialog* dialog = PlayerDialog::create();
			dialog->setPosition(Vec2(20, 11));
			dialog->setHeaderText(m_NPCName);
			dialog->loadDialogFromFile("dialogues/" + std::to_string(this->getTag()) + "jap.dlg");

			interfaceLayer->addChild(dialog, 3, INTERFACE_DIALOG);

			//test popup
			PopupMenu* popup = PopupMenu::create(Director::getInstance()->getVisibleSize().width / 2,
				Director::getInstance()->getVisibleSize().height / 5,
				800, 60);
			popup->setCurrentText("HINT TEST");
			popup->setHeaderText("<HEADER>");
			interfaceLayer->addChild(popup, 4, INTERFACE_POPUP);
			//
		}
	}
	else
	{
		auto dialog = interfaceLayer->getChildByTag(INTERFACE_DIALOG);

		if (dialog != nullptr)
			dialog->removeFromParentAndCleanup(true);
		
		playerIsNear = false;
	}
}

void	NonPlayablePerson::_stopAnimation()
{
	
}
