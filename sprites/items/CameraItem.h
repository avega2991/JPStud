#pragma once

#include "cocos2d.h"

#include "sprites\items\Item.h"


// SINGLETON
class CameraItem : public InventoryItem
{
private:
	static CameraItem*												s_camera;

public:
	CameraItem();
	// ~CameraItem();

	
};