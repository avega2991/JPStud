#include "sprites\items\Item.h"

USING_NS_CC;


InventoryItem::InventoryItem()
{
	m_name = "Default Name";
	m_description = "Default Description";

	m_useCallback = CC_CALLBACK_1(InventoryItem::useCallback, this);
	m_examineCallback = CC_CALLBACK_1(InventoryItem::examineCallback, this);
}
/*
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
*/
// <GET>
int	InventoryItem::getID()
{
	return m_id;
}

std::string	InventoryItem::getName()
{
	return m_name;
}

std::string	InventoryItem::getDescription()
{
	return m_description;
}

Menu*	InventoryItem::getClickableItem()
{
	return m_clickableItem;
}
// </GET>

// <SET>
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
// </SET>

void	InventoryItem::clickItemCallback(Ref* pSender)
{
	Vec2 menuPosition = m_clickableItem->getPosition();
	Size clickableItemSize = m_clickableItem->getContentSize();
	menuPosition = Vec2(menuPosition.x - clickableItemSize.width,
		menuPosition.y - clickableItemSize.height);
	
	MenuItemImage* useButton = MenuItemImage::create("textures/interface/dictionary/button.png",
		"textures/interface/dictionary/button_selected.png",
		m_useCallback);
	MenuItemImage* examineButton = MenuItemImage::create("textures/interface/dictionary/button.png",
		"textures/interface/dictionary/button_selected.png",
		m_examineCallback);

	useButton->setPosition(Vec2(0, -useButton->getContentSize().height));
	examineButton->setPosition(Vec2(0, examineButton->getContentSize().height));

	useButton->setTag(ITEM_MENU_USE_BUTTON);
	examineButton->setTag(ITEM_MENU_EXAMINE_BUTTON);

	Menu* menu = Menu::create(useButton, examineButton, nullptr);
	menu->setPosition(menuPosition);

	this->getParent()->addChild(menu, ITEM_MENU);
}

void	InventoryItem::useCallback(Ref* pSender)
{

}

void	InventoryItem::examineCallback(Ref* pSender)
{

}