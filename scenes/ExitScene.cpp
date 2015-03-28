//этот класс начал в проект создани€, когда это helloworld класса, здесь € исправить
#include "scenes\ExitScene.h"
#include "scenes\MainMenuScene.h"
//ѕроект называетс€ NewScene так нужно ссылки
USING_NS_CC;
//создать основной сцены
Scene* ExitScene::createScene()
{
	//»спользование сценариев класса создать сцены
	auto scene = Scene::create();
	scene->setTag(EXIT_SCENE);

	//создать MainScene слой
	ExitScene *layer = ExitScene::create();

	scene->setName("ExitScene");

	scene->addChild(layer);
	// ¬озвращает сцены
	return scene;
}

// инициализировать MainScene слой
bool ExitScene::init()
{
	this->setName("ExitScene");
	//слой ли успешной инициализации
	if (!Layer::init())
	{
		return false;
	}
	//получить координаты интерфейс экран видимой области
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//место происхождени€
	Point origin = Director::getInstance()->getVisibleOrigin();
	//создать кнопки закрыти€ параметров дл€, соответственно, нормальное состо€ние отображени€ картинки, фотографии операции отдельные государства, метод называетс€ MainScene menuCloseCallback называют метод.
	auto closeItem = MenuItemImage::create(
		"textures/interface/player/CloseNormal.png",
		"textures/interface/player/CloseSelected.png",
		CC_CALLBACK_1(ExitScene::menuCloseCallback, this));
	//дл€ просмотра расположены кнопки закрыти€ позиции ниже правого
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));
	//создать меню, пожалуйста, обратите внимание, не об€зательно €вл€етс€ последний параметр
	auto menu = Menu::create(closeItem, NULL);
	//меню дл€ инициализации место происхождени€ этой позиции, € также необходимо найти врем€ пон€ть
	menu->setPosition(Point::ZERO);
	//чтобы добавить в меню слой
	this->addChild(menu, 1);
	//вид вертикальной позиции в центре фотографии кнопку ƒобавить 2
	auto loadSprite = Sprite::create("animations/loadExit/0.png");
	loadSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(loadSprite, 1);

	auto label = Label::createWithTTF("Powered by Cocos2d", "fonts/Marker Felt.ttf", 24);
	auto labelThank = Label::createWithTTF("Thanks for using JPStud App", "fonts/Marker Felt.ttf", 24);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2, loadSprite->getPosition().y - 40));
	labelThank->setPosition(Vec2(origin.x + visibleSize.width / 2, loadSprite->getPosition().y + 40));
	this->addChild(label, 1);
	this->addChild(labelThank, 1);

	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(15);
	for (int i = 0; i < 15; i++)
	{
		char fileName[30];
		sprintf(fileName, "animations/loadExit/%d.png", i);
		animFrames.pushBack(SpriteFrame::create(fileName, Rect(0, 0, 300, 300)));
	}

	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	Animate* animate = Animate::create(animation);

	loadSprite->runAction(RepeatForever::create(animate));
	this->runAction(Sequence::create(DelayTime::create(4.0f), 
		CallFuncN::create(CC_CALLBACK_1(ExitScene::menuCloseCallback, this)), nullptr));

	return true;
}

void ExitScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}