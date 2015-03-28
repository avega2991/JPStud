#include "sprites\TreasureChest.h"

USING_NS_CC;

TreasureChest::TreasureChest()
{
	m_state = CHEST_CLOSED;
	m_name = "Default_Name.png";

	this->schedule(schedule_selector(TreasureChest::onEachFrame));
}

TreasureChest*	TreasureChest::create()
{
	TreasureChest* chest = new TreasureChest();
	std::string filename = "textures/chests/default_chest_closed.png";

	chest->m_name = filename.substr(0, filename.find('.') - 6);

	if (chest && chest->initWithFile(filename))
	{
		chest->autorelease();
		return chest;
	}

	CC_SAFE_DELETE(chest);

	return NULL;
}

TreasureChest*	TreasureChest::create(const std::string& imageFile)
{
	TreasureChest* chest = new TreasureChest();
	
	chest->m_name = imageFile.substr(0, imageFile.find('.') - 6);

	if (chest && chest->initWithFile(imageFile))
	{
		chest->autorelease();
		return chest;
	}

	CC_SAFE_DELETE(chest);

	return NULL;
}

// GET
BYTE	TreasureChest::getState()
{
	return m_state;
}
//

// SET
void	TreasureChest::pushItem(InventoryItem* item)
{
	m_items.push_back(item);
}

void	TreasureChest::setImage(const std::string& filename)
{
	this->setTexture(Director::getInstance()->getTextureCache()->addImage(filename));
}

void	TreasureChest::setState(BYTE state)
{
	m_state = state;

	if (m_state == CHEST_OPENED)
		this->setImage(m_name + "opened.png");
	else
		this->setImage(m_name + "closed.png");
}
//

void	TreasureChest::openChest()
{
	this->setState(CHEST_OPENED);
}

// SUBFUNCTIONS && CALLBACKS
void	TreasureChest::onEachFrame(float dt)
{
	if (this->getParent() == nullptr)
		return;

	auto playerLayer = this->getParent();
	auto player = playerLayer->getChildByTag(PLAYER);

	static bool playerIsNear = false;

	auto a = this->getPosition();
	auto b = this->getContentSize();

	if (geo::Line::length(&player->getPosition(), &this->getPosition()) < player->getContentSize().height / 2)
	{
		if (!playerIsNear)
		{
			playerIsNear = true;
			CCLOG("NPC's listener: player has been reached the CHEST"); // panel with the offer to talk instead

			this->openChest();
		}
	}
	else
	{
		playerIsNear = false;
	}

	if (this->getState() == CHEST_OPENED)
		this->unschedule(schedule_selector(TreasureChest::onEachFrame));
}
