#include "sprites\Player.h"
#include "scenes\FirstScene.h"

USING_NS_CC;

Player*	Player::s_player = nullptr;


Player::Player()
{
	//loading .png
	SpriteBatchNode* spritebatch = SpriteBatchNode::create("textures/hero.png");

	SpriteFrameCache* cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("textures/hero.plist");

	//this->initWithSpriteFrameName("1.png");
	this->addChild(spritebatch);

	//loading animation
	char str1[100];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 1 + (i * 6); j <= 6 + (i * 6); j++)
		{
			sprintf(str1, "%d.png", j);
			SpriteFrame* frame = cache->spriteFrameByName(str1);
			m_animFrames.pushBack(frame);
		}
	}

	m_directionState = DOWN;
	m_prevPosition = this->getPosition();

	m_listener = EventListenerTouchOneByOne::create();
	m_listener->setSwallowTouches(false);
	m_listener->onTouchBegan = CC_CALLBACK_2(Player::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithFixedPriority(m_listener, PLAYER_PRIORITY);

	//function on each frame with player
	this->schedule(schedule_selector(Player::onEachFrame));
}

Player*	Player::getInstance()
{
	if (!s_player)
	{
		s_player = new Player();
		s_player->initWithSpriteFrameName("1.png");
		s_player->initStats();
	}

	return s_player;
}

Player*	Player::create()
{
	Player* player = new Player();

	if (player && player->initWithSpriteFrameName("1.png"))
	{
		player->autorelease();
		return player;
	}

	CC_SAFE_DELETE(player);

	return NULL;
}

void	Player::initStats()
{
	// TODO : LOAD STATS FROM FILE
	// <CHARACTERISTICS>
	s_player->m_playerLevel = 1;
	s_player->m_playerExp = 0;
	s_player->m_playerExpToLevel = 92;
	s_player->m_playerTitle = "Shoshinsha"; // "Shougakkou no seito";
	// </CHARACTERISTICS>
}

EventListenerTouchOneByOne*	Player::getEventListener()
{
	return m_listener;
}

Vec2	Player::getPrevPosition()
{
	return m_prevPosition;
}

// <GET_CHARACTERISTICS>
short	Player::getPlayerLevel()
{
	return m_playerLevel;
}

long	Player::getPlayerExp()
{
	return m_playerExp;
}

long	Player::getPlayerExpToLevel()
{
	return m_playerExpToLevel;
}

std::string	Player::getPlayerTitle()
{
	return m_playerTitle;
}
// </GET_CHARACTERISTICS>

void	Player::moveTo(const cocos2d::Point& touch)
{
	//auto movSprite = this->getChildByName("movSprite");
	Point *a = new Point(this->getPosition().x, this->getPosition().y);
	Point *b = new Point(touch.x, touch.y);
	
	//if moving not finished
	if (this->getActionByTag(MOVE) != nullptr)
	{
		this->stopActionByTag(MOVE);
		this->runAction(CallFuncN::create(CC_CALLBACK_0(Player::_stopAnimation, this)));
	}

	//switch animation
	int xDirection = (b->x > a->x) ? RIGHT : LEFT;
	int yDirection = (b->y > a->y) ? UP : DOWN;
	m_directionState = (abs(b->x - a->x) > abs(b->y - a->y)) ? xDirection : yDirection;

	m_playFrames.clear();
	int begin = 0;
	int end = m_animFrames.size() - 1;

	switch (m_directionState)
	{
	case DOWN:
		begin = 0; end = 5;
		break;
	case LEFT:
		begin = 6; end = 11;
		break;
	case RIGHT:
		begin = 12; end = 17;
		break;
	default: //case UP:
		begin = 18; end = 23;
		break;
	}
	for (Vector<SpriteFrame*>::iterator it = m_animFrames.begin() + begin; it != m_animFrames.begin() + end; it++)
		m_playFrames.pushBack(*it);

	Animation* animation = Animation::createWithSpriteFrames(m_playFrames, 0.15f);
	Animate* animate = Animate::create(animation);
	//

	auto movingAnimate = RepeatForever::create(animate);
	movingAnimate->setTag(MOVE_ANIM);

	auto move = MoveTo::create(geo::Line::length(a, b) / 100,
		Vec2(touch.x, touch.y));// + this->getContentSize().height / 2 - BIAS));
	//after finishing moving sprite -> stop animation
	auto moveSequence = Sequence::create(move, CallFuncN::create(CC_CALLBACK_0(Player::_stopAnimation, this)), nullptr);
	moveSequence->setTag(MOVE);

	this->runAction(movingAnimate);
	this->runAction(moveSequence);
}

bool	Player::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	CCLOG("Player's listener: onTouchBegan x = %f, y = %f", touch->getLocation().x, touch->getLocation().y);
	
	this->moveTo(touch->getLocation());

	return true;
}

void	Player::onEachFrame(float dt)
{
	static bool bLocked = false;

	Vector<Node*> obstacles = this->getParent()->getChildren();
	obstacles.erase(obstacles.find(this));

	Vec2 playerPosition = this->getPosition();

	for (Vector<Node*>::iterator it = obstacles.begin(); it != obstacles.end(); it++)
	{
		// swap layers if intersect by OY and order is lower
		Vec2 obstaclePosition = (*it)->getPosition();
		if ((playerPosition.y < obstaclePosition.y) && (m_prevPosition.y > obstaclePosition.y))
		{
			if (this->getLocalZOrder() < (*it)->getLocalZOrder())
				this->setLocalZOrder(this->getLocalZOrder() + 2);
		}
		else if ((playerPosition.y > obstaclePosition.y) && (m_prevPosition.y < obstaclePosition.y))
		{
			if (this->getLocalZOrder() > (*it)->getLocalZOrder())
				this->setLocalZOrder(this->getLocalZOrder() - 2);
		}

		// stop moving if collide
		// TODO: BYPASS THE OBSTACLE
		/*Rect playerFloorBox = geo::getFloorBox(&(this->getBoundingBox()));
		Rect obstacleFloorBox = geo::getFloorBox(&((*it)->getBoundingBox()));

		if (playerFloorBox.intersectsRect(obstacleFloorBox))
		{
			if (!bLocked)
			{
				this->_stopAnimation();
				this->stopAllActions();
				bLocked = true;
			}
		}
		else
			bLocked = false;*/
	}

	m_prevPosition = playerPosition;
}

//SUBFUNCTIONS
void	Player::_stopAnimation()
{
	if (this->getActionByTag(MOVE_ANIM) != nullptr)
		this->stopActionByTag(MOVE_ANIM);

	std::string frameName = std::to_string(m_directionState) + ".png";
	
	this->setSpriteFrame(frameName);
}
