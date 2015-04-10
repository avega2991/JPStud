#pragma once

#include "cocos2d.h"
#include "sprites\items\Item.h"
#include "support\AppLib.h"
#include "support\ConstValues.h"

#include <vector>

#define CHEST_LOCKED				0
#define	CHEST_CLOSED				1
#define CHEST_OPENED				2

class TreasureChest : public cocos2d::Sprite
{
private:
	std::vector<InventoryItem*>								m_items;
	BYTE													m_state;
	int														m_keyID;	// if NULL then no need any key

	std::string												m_name;		// filename without _<state>.<extention>

public:
	TreasureChest();
	// ~TreasureChest();

	static TreasureChest*									create();
	static TreasureChest*									create(const std::string& defaultImageFilename);

	BYTE													getState();

	void													pushItem(InventoryItem* item);
	void													setImage(const std::string& filename);
	void													setState(BYTE state);

	void													openChest();

	// SUBFUNCTIONS && CALLBACKS
	void													onEachFrame(float dt);
};
