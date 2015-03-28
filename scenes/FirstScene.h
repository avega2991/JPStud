#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "support\AppLib.h"
#include "support\ConstValues.h"


class FirstScene : public cocos2d::Layer
{
private:
	CocosDenshion::SimpleAudioEngine*					m_soundEngine;

public:

	bool												init();

	static cocos2d::Scene*								createScene();

	bool												onTouchBegan(cocos2d::Touch*, cocos2d::Event*);

	CREATE_FUNC(FirstScene);
};
