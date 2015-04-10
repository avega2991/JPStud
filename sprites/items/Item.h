#pragma once

#include "cocos2d.h"
#include <string>

#define ITEM_MENU							10
#define ITEM_MENU_USE_BUTTON				11
#define ITEM_MENU_EXAMINE_BUTTON			12


class InventoryItem : public cocos2d::Sprite
{
protected:
	int																m_id;
	std::string														m_name;
	std::string														m_type;
	std::string														m_description;

	cocos2d::Menu*													m_clickableItem;
	cocos2d::ccMenuCallback											m_useCallback;
	cocos2d::ccMenuCallback											m_examineCallback;
		
public:
	InventoryItem();
	InventoryItem(const std::string& formatString);
	// ~InventoryItem();

	// static InventoryItem*											create(const std::string& name);
	// static InventoryItem*											create(const std::string& name, const std::string& imageFile);
	
	int																getID();
	std::string														getName();
	std::string														getDescription();
	cocos2d::Menu*													getClickableItem();

	virtual void													setImage(const std::string& filename);
	virtual void													setName(const std::string& name);
	virtual void													setDescription(const std::string& description);

	// CALLBACKS
	virtual void													clickItemCallback(Ref*);
	virtual void													useCallback(Ref*);
	virtual void													examineCallback(Ref*);
};
