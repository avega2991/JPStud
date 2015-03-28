#include "panes\interface\StatusInterface.h"

USING_NS_CC;


StatusInterface::StatusInterface()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Player* player = Player::getInstance();

	// <SPRITES>
	auto background = Sprite::create("textures/interface/status/status_background.png");

	auto playerStatusIcon = Sprite::create("textures/heroframes/1.png");
	playerStatusIcon->setScale(1.5f);
	playerStatusIcon->setPosition(Vec2(playerStatusIcon->getContentSize().width / 2 - background->getContentSize().width / 2 + 35, 0));

	auto rectWithBorder = DrawNode::create();
	Vec2 vertices[] =
	{
		Vec2(playerStatusIcon->getPosition().x - playerStatusIcon->getContentSize().width / 2 - STATUS_POLYGON_OFFSET,
		playerStatusIcon->getPosition().y - playerStatusIcon->getContentSize().height / 2 - STATUS_POLYGON_OFFSET),
		Vec2(playerStatusIcon->getPosition().x - playerStatusIcon->getContentSize().width / 2 - STATUS_POLYGON_OFFSET,
		playerStatusIcon->getPosition().y + playerStatusIcon->getContentSize().height / 2 + STATUS_POLYGON_OFFSET),
		Vec2(playerStatusIcon->getPosition().x + playerStatusIcon->getContentSize().width / 2 + STATUS_POLYGON_OFFSET,
		playerStatusIcon->getPosition().y + playerStatusIcon->getContentSize().height / 2 + STATUS_POLYGON_OFFSET),
		Vec2(playerStatusIcon->getPosition().x + playerStatusIcon->getContentSize().width / 2 + STATUS_POLYGON_OFFSET,
		playerStatusIcon->getPosition().y - playerStatusIcon->getContentSize().height / 2 - STATUS_POLYGON_OFFSET),
	};
	rectWithBorder->drawPolygon(vertices, 4, Color4F(1.0f, 1.0f, 1.0f, 0), 2, Color4F(0.2f, 0.2f, 0.2f, 1));

	this->addChild(background, STATUS_BACKGROUND_ORDER);
	this->addChild(playerStatusIcon, STATUS_SPRITE_ORDER);
	this->addChild(rectWithBorder, STATUS_SPRITE_ORDER);
	// </SPRITES>
	
	// <STATS_LABELS>
	Label* levelLabel = Label::create("LV. " + std::to_string(player->getPlayerLevel()), "Arial", 18);
	Label* expLabel = Label::create("EXP: " + std::to_string(player->getPlayerExp()) + " / " + std::to_string(player->getPlayerExpToLevel()), "Arial", 18);
	Label* titleLabel = Label::create(player->getPlayerTitle(), "Arial", 18);

	levelLabel->setAnchorPoint(Vec2(0, 1));
	expLabel->setAnchorPoint(Vec2(1, 1));
	titleLabel->setAnchorPoint(Vec2(0, 1));

	levelLabel->setPosition(Vec2(-(background->getContentSize().width / 2) + 10, background->getContentSize().height / 2 - 5));// background->getContentSize().height - 10));
	expLabel->setPosition(Vec2(background->getContentSize().width / 2 - 10, levelLabel->getPosition().y));
	titleLabel->setPosition(Vec2(levelLabel->getPosition().x, levelLabel->getPosition().y - 20));

	this->addChild(levelLabel, STATUS_LABEL_ORDER);
	this->addChild(expLabel, STATUS_LABEL_ORDER);
	this->addChild(titleLabel, STATUS_LABEL_ORDER);
	// </STATS_LABELS>
	
	this->setPosition(visibleSize.width - background->getContentSize().width / 2 - 20,
		visibleSize.height / 2);
}

StatusInterface::~StatusInterface()
{
	this->removeAllChildrenWithCleanup(true);
	this->removeFromParentAndCleanup(true);
}

StatusInterface*	StatusInterface::create()
{
	StatusInterface* statusInterface = new StatusInterface();

	if (statusInterface->init())
	{
		statusInterface->autorelease();
		return statusInterface;
	}

	CC_SAFE_DELETE(statusInterface);
	return nullptr;
}

