#include "scenes\FirstScene.h"
#include "scenes\MainMenuScene.h"

#include "sprites\Player.h"
#include "sprites\NPC.h"
#include "sprites\TreasureChest.h"
#include "panes\interface\MainInterface.h"
#include "panes\Dialog.h"

USING_NS_CC;


Scene* FirstScene::createScene()
{
	auto scene = Scene::create();
	scene->setTag(FIRST_SCENE);

	FirstScene *layer = FirstScene::create();
	layer->setTag(MAIN_LAYER);

	scene->addChild(layer);

	return scene;
}

bool FirstScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	auto label = Label::createWithTTF("FirstScene", "fonts/Marker Felt.ttf", 24);

	label->setAnchorPoint(Vec2(0, 0));												// left-up
	label->setPosition(Vec2(origin.x + 5.0f,
		origin.y + visibleSize.height - label->getContentSize().height - 5.0f));
	this->addChild(label, 10, "debug_label");
	
	//background
	Texture2D* texture = TextureCache::sharedTextureCache()->addImage("textures/background/grass_02.png");
	Texture2D::TexParams backParams = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
	texture->setTexParameters(&backParams);

	auto background = Sprite::createWithTexture(texture, Rect(0, 0, visibleSize.width, visibleSize.height));
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(background, 1, "background");

	//interface
	PlayerInterface* playerInterface = PlayerInterface::create();
	playerInterface->setTag(INTERFACE_OBJECT);

	playerInterface->setContentSize(this->getContentSize());
	playerInterface->setPosition(0, 0);
	
	this->addChild(playerInterface, INTERFACE_ORDER, INTERFACE_LAYER);
	
	// CHECKING EXP UPDATING
	playerInterface->updatePercentage();
	//

	//subjects and obstacles
	auto playerLayer = Layer::create();
	//playerLayer->setContentSize(player->getTexture()->getContentSize());
	playerLayer->setPosition(0, 0);

	Player* player = Player::getInstance();
	player->setPosition(Vec2(origin.y + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));

	playerLayer->addChild(player, 1, PLAYER);

	//NPC
	NonPlayablePerson* npc = NonPlayablePerson::create("1.png");
	npc->setPosition(origin.y + visibleSize.width / 3,
		origin.y + visibleSize.height / 3);
	npc->setNPCName("Default NPC");
	
	playerLayer->addChild(npc, 2, NPC);
	
	//CHEST TEST
	TreasureChest* chest = TreasureChest::create();
	chest->setPosition(visibleSize.width / 2, 3 * visibleSize.height / 4);
	playerLayer->addChild(chest, 2);
	//

	//decorations
	Sprite* treeA = Sprite::create("tree_try.png");
	treeA->setPosition(Vec2(visibleSize.width / 3 - 500, visibleSize.height / 3 - 80));
	treeA->setAnchorPoint(Vec2(0, 0));
	playerLayer->addChild(treeA, 3);

	Sprite* treeB = Sprite::create("tree_try_2.png");
	treeB->setPosition(Vec2(visibleSize.width - 500, -80));
	treeB->setAnchorPoint(Vec2(0, 0));
	playerLayer->addChild(treeB, 4);

	//adding all items to main layer
	this->addChild(playerLayer, PLAYER_LAYER_ORDER, PLAYER_LAYER);

	//event listener
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(false);
	listener->onTouchBegan = CC_CALLBACK_2(FirstScene::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithFixedPriority(listener, BACKGROUND_PRIORITY);

	m_soundEngine = CocosDenshion::SimpleAudioEngine::getInstance();
	//m_soundEngine->playBackgroundMusic("soundeffects/background/BrunuhVille - Magic Of Love.mp3");

	return true;
}

bool FirstScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	CCLOG("Scene's listener: onTouchBegan x = %f, y = %f", touch->getLocation().x, touch->getLocation().y);
	
	Point touchLocation = this->convertTouchToNodeSpace(touch);

	if (this->getChildByTag(PLAYER_LAYER)->getChildByTag(NPC)->getBoundingBox().containsPoint(touchLocation))
	{
		CCLOG("NPC IS TOUCHED");
	}

	return true;
}
