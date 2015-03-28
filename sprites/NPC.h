#pragma once

#include "cocos2d.h"

#include "support\ConstValues.h"
#include "panes\interface\MainInterface.h"
#include "panes\Dialog.h"

#define BIAS		4		//line from the bottom of picture and legs of the player

#define DOWN				1
#define LEFT				7
#define RIGHT				13
#define UP					19

#define MOVE				90
#define MOVE_ANIM			91

#define LNAME				911

typedef int DirectionState;

class NonPlayablePerson : public cocos2d::Sprite
{
private:
	DirectionState								m_directionState;

	std::string									m_NPCName;
	//cocos2d::Vector<cocos2d::SpriteFrame*> m_animFrames;	//all frames
	//cocos2d::Vector<cocos2d::SpriteFrame*> m_playFrames;	//running frames
	cocos2d::EventListenerTouchOneByOne*		m_listener;

public:
	NonPlayablePerson();

	static NonPlayablePerson*					create(const std::string&);

	std::string									getNPCName();

	void										setNPCName(const std::string&);

	bool										onTouchBegan(cocos2d::Touch*, cocos2d::Event*);

	void										onEachFrame(float);

	//SUBFUNCTIONS:
	void										_stopAnimation();
};
