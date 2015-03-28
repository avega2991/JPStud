#pragma once

#include "cocos2d.h"

#include "sprites\Player.h"

// ORDERS
#define STATUS_BACKGROUND_ORDER											1
#define STATUS_SPRITE_ORDER												2
#define STATUS_LABEL_ORDER												3

// CONSTANTS
#define STATUS_POLYGON_OFFSET											20


class StatusInterface : public cocos2d::Layer
{
private:


public:
	StatusInterface();
	virtual ~StatusInterface();

	static StatusInterface*												create();

};