#pragma once

#include "cocos2d.h"

#include "support\AppLib.h"
#include "support\ConstValues.h"

#define BIAS				4		//line from the bottom of picture and legs of the player

#define DOWN				1
#define LEFT				7
#define RIGHT				13
#define UP					19

#define MOVE				90
#define MOVE_ANIM			91

//NOT USED
typedef enum MovingState
{
	msNone = 0,
	msMov = 1,
	msRun = 2
};
//

typedef int DirectionState;

class Player : public cocos2d::Sprite
{
private:
	MovingState																m_movingState;
	DirectionState															m_directionState;

	cocos2d::Vector<cocos2d::SpriteFrame*>									m_animFrames;		// all frames
	cocos2d::Vector<cocos2d::SpriteFrame*>									m_playFrames;		// running frames
	cocos2d::EventListenerTouchOneByOne*									m_listener;

	cocos2d::Vec2															m_prevPosition;

	// CHARACTERISTICS
	short																	m_playerLevel;
	long																	m_playerExp;		// NOT PERCENTAGE
	long																	m_playerExpToLevel;
	std::string																m_playerTitle;		// NOT NECCESSARY

	// singleton object
	static Player*															s_player;

public:
	Player();

	static Player*															getInstance();
	void																	initStats();
	
	cocos2d::Vec2															getPrevPosition();
	cocos2d::EventListenerTouchOneByOne*									getEventListener();

	// <GET_CHARACTERISTICS>
	short																	getPlayerLevel();
	long																	getPlayerExp();
	long																	getPlayerExpToLevel();
	std::string																getPlayerTitle();
	// </GET_CHARACTERISTICS>

	void																	moveTo(const cocos2d::Point&);

	bool																	onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	void																	onEachFrame(float);

	// SUBFUNCTIONS
	void																	_stopAnimation();

	// DEPRECATED
	static Player*															create();
};
