//���� ����� ����� � ������ ��������, ����� ��� helloworld ������, ����� � ���������
#include "scenes\ExitScene.h"
#include "scenes\MainMenuScene.h"
//������ ���������� NewScene ��� ����� ������
USING_NS_CC;
//������� �������� �����
Scene* ExitScene::createScene()
{
	//������������� ��������� ������ ������� �����
	auto scene = Scene::create();
	scene->setTag(EXIT_SCENE);

	//������� MainScene ����
	ExitScene *layer = ExitScene::create();

	scene->setName("ExitScene");

	scene->addChild(layer);
	// ���������� �����
	return scene;
}

// ���������������� MainScene ����
bool ExitScene::init()
{
	this->setName("ExitScene");
	//���� �� �������� �������������
	if (!Layer::init())
	{
		return false;
	}
	//�������� ���������� ��������� ����� ������� �������
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//����� �������������
	Point origin = Director::getInstance()->getVisibleOrigin();
	//������� ������ �������� ���������� ���, ��������������, ���������� ��������� ����������� ��������, ���������� �������� ��������� �����������, ����� ���������� MainScene menuCloseCallback �������� �����.
	auto closeItem = MenuItemImage::create(
		"textures/interface/player/CloseNormal.png",
		"textures/interface/player/CloseSelected.png",
		CC_CALLBACK_1(ExitScene::menuCloseCallback, this));
	//��� ��������� ����������� ������ �������� ������� ���� �������
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));
	//������� ����, ����������, �������� ��������, �� ����������� �������� ��������� ��������
	auto menu = Menu::create(closeItem, NULL);
	//���� ��� ������������� ����� ������������� ���� �������, � ����� ���������� ����� ����� ������
	menu->setPosition(Point::ZERO);
	//����� �������� � ���� ����
	this->addChild(menu, 1);
	//��� ������������ ������� � ������ ���������� ������ �������� 2
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