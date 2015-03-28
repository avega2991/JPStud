#include "sprites\Item.h"

USING_NS_CC;

InventoryItem::InventoryItem()
{
	m_name = "Default Name";
	m_description = "Default Description";
}

InventoryItem*	InventoryItem::create(const std::string& name)
{
	InventoryItem* item = new InventoryItem();
	std::string defaultImage = "textures/items/default_item.png";
	if (item && item->initWithFile(defaultImage))
	{
		item->setName(name);
		item->autorelease();
		return item;
	}

	CC_SAFE_DELETE(item);

	return NULL;
}

InventoryItem*	InventoryItem::create(const std::string& name, const std::string& imageFile)
{
	InventoryItem* item = new InventoryItem();

	if (item && item->initWithFile(imageFile))
	{
		item->setName(name);
		item->autorelease();
		return item;
	}

	CC_SAFE_DELETE(item);

	return NULL;
}

// GET
std::string	InventoryItem::getName()
{
	return m_name;
}

std::string	InventoryItem::getDescription()
{
	return m_description;
}
//

// SET
void	InventoryItem::setImage(const std::string& filename)
{
	this->setTexture(Director::getInstance()->getTextureCache()->addImage(filename));
}

void	InventoryItem::setName(const std::string& name)
{
	m_name = name;
}

void	InventoryItem::setDescription(const std::string& desc)
{
	m_description = desc;
}
//
