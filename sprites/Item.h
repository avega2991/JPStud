#pragma once

#include "cocos2d.h"
#include <string>


class InventoryItem : public cocos2d::Sprite
{
private:
	int																m_id;
	std::string														m_name;
	std::string														m_type;
	std::string														m_description;

public:
	InventoryItem();
	InventoryItem(const std::string& formatString);
	// ~InventoryItem();

	static InventoryItem*											create(const std::string& name);
	static InventoryItem*											create(const std::string& name, const std::string& imageFile);
	
	int																getID();
	std::string														getName();
	std::string														getDescription();

	void															setImage(const std::string& filename);
	void															setName(const std::string& name);
	void															setDescription(const std::string& description);
};
