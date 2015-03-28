#include "scenes\MainMenuScene.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
	scene->setTag(MAINMENU_SCENE);

    // 'layer' is an autorelease object
	auto layer = MainMenu::create();
	layer->setTag(MAIN_LAYER);//("MainLayer");

    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
	if ( !Layer::init() )
    {
        return false;
    }
    
	m_soundEngine = CocosDenshion::SimpleAudioEngine::getInstance();
	m_soundEngine->preloadEffect("soundeffects/UI/complete.mp3");
	m_soundEngine->preloadEffect("soundeffects/UI/on.mp3");
	
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto label = Label::createWithTTF("JPStud Cocos2dx multiplatform application", "fonts/Marker Felt.ttf", 24);
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1, "label");


	auto background = Sprite::create("textures/mainmenu/1.jpg");
	background->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(background, 0);
	//animation
	Vector<SpriteFrame*> animFrames;
	//animFrames.reserve(5);
	for (int i = 1; i <= 6; i++)
	{
		animFrames.pushBack(SpriteFrame::create("textures/mainmenu/" + std::to_string(i) + ".jpg", Rect(0, 0, 1024, 768)));
	}
	for (int i = 5; i >= 2; i--)
	{
		animFrames.pushBack(SpriteFrame::create("textures/mainmenu/" + std::to_string(i) + ".jpg", Rect(0, 0, 1024, 768)));
	}
	// create the animation out of the frames
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.15f);
	Animate* animate = Animate::create(animation);
	background->runAction(RepeatForever::create(animate));

    auto startLabel = MenuItemFont::create("Begin", CC_CALLBACK_1(MainMenu::menuCallback, this));
	auto continueLabel = MenuItemFont::create("Take Screenshot", CC_CALLBACK_1(MainMenu::menuCallback, this));
	auto exitLabel = MenuItemFont::create("Exit", CC_CALLBACK_1(MainMenu::menuCallback, this));
	startLabel->setAnchorPoint(Vec2(1, 0.5f));		m_addedItems.push_back(startLabel);
	continueLabel->setAnchorPoint(Vec2(1, 0.5f));	m_addedItems.push_back(continueLabel);
	exitLabel->setAnchorPoint(Vec2(1, 0.5f));		m_addedItems.push_back(exitLabel);
	startLabel->setTag(LSTART);
	continueLabel->setTag(LCONT);
	exitLabel->setTag(LEXIT);
	
	auto menu = Menu::create(startLabel, continueLabel, exitLabel, NULL);
	menu->setPosition(Vec2(visibleSize.width - visibleSize.width / 20, visibleSize.height / 2));
	menu->alignItemsVertically();
	this->addChild(menu, 1, MAIN_MENU);

	//create loading bar
	/*cocos2d::ui::LoadingBar* loadingBar = cocos2d::ui::LoadingBar::create();
	loadingBar->setName("LoadingBar");
	loadingBar->loadTexture("HelloWorld.png");
	loadingBar->setPercent(0);
	loadingBar->setPosition(Point(visibleSize.width / 2.0f, visibleSize.height / 2.0f + loadingBar->getSize().height / 4.0f));
	this->addChild(loadingBar, 1, 10);
	this->schedule(schedule_selector(MainMenu::updateProgress), 0.025f);*/

	//checkbox
	//cocos2d::ui::CheckBox* checkBox = cocos2d::ui::CheckBox::create();
	//checkBox->setTouchEnabled(true);
	//checkBox->loadTextures("icons/checkbox/1_unchecked.png",	//normal
	//	"icons/checkbox/1_unchecked_pressed.png",				//normal_pressed
	//	"icons/checkbox/1_checked.png",						//active
	//	"icons/checkbox/1_checked.png",					//normal_disable
	//	"icons/checkbox/1_checked.png");					//active_disable
	//checkBox->setPosition(Point(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	//checkBox->addEventListener(CC_CALLBACK_0(MainMenu::CheckBoxCallback, this));
	//this->addChild(checkBox, 2);

	m_soundEngine->playBackgroundMusic("soundeffects/background/BrunuhVille - Lumina.mp3");
	
    return true;
}
//TODO
void MainMenu::checkboxCallback()
{

}

void MainMenu::updateProgress(float dt)
{
	cocos2d::ui::LoadingBar* loadingBar = (cocos2d::ui::LoadingBar*)this->getChildByTag(10);
	m_counter++;
	if (m_counter > 100)
	{
		//this->scheduleOnce(schedule_selector(MainMenu::GoToScene), 0);

		unschedule(schedule_selector(MainMenu::updateProgress));
	}
	loadingBar->setPercent(m_counter);
}

void MainMenu::menuCallback(cocos2d::Ref* pSender)
{
	MenuItem* pMenuItem = (MenuItem *)(pSender);

	int tag = pMenuItem->getTag();

	switch (tag)
	{
	case LSTART:
	{
				   m_soundEngine->playEffect("soundeffects/UI/on.mp3");
				   Menu* menu = (Menu*) this->getChildByTag(MAIN_MENU);
				   auto seq = Sequence::create(FadeOut::create(0.2f),
					   CallFunc::create(CC_CALLBACK_0(MainMenu::_createMainSubmenu, this)),
					   FadeIn::create(0.2f), nullptr);
				   menu->runAction(seq);
				   break;
	}
	case LCONT:
	{
				  m_soundEngine->playEffect("soundeffects/UI/on.mp3");
				  glAddition::captureRectToTGA(Rect(0, 0, 
					  Director::getInstance()->getVisibleSize().width, 
					  Director::getInstance()->getVisibleSize().height),
					  "taken_screenshot.tga");
				  //utils::captureScreen(CC_CALLBACK_2(MainMenu::_afterCaptured, this), "D:/screen.jpg");
				  break;
	}
	case LEXIT:
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
				  MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
				  return;
#endif
				  auto scene = Scene::create();
				  scene->addChild(ExitScene::create());

				  m_soundEngine->stopBackgroundMusic(true);
				  m_soundEngine->playEffect("soundeffects/UI/complete.mp3");
				  Director::getInstance()->replaceScene(TransitionFade::create(.5, scene));
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
				  exit(0);
#endif
				  break;
	}
	default:
	{
			   // REPLACE IT WHEN NECCESSARY
			   MenuItemFont::setFontSize(18);
			   //
			   //TODO change scene switch add
			   m_soundEngine->stopBackgroundMusic(true);
			   Director::getInstance()->replaceScene(TransitionFade::create(.5, (Scene*) FirstScene::createScene()));
	}
	}
}

void MainMenu::transitionToMenuExit()
{
	auto size = Director::getInstance()->getWinSize();		//get the windows size.

	auto clipper = ClippingNode::create();		// create the ClippingNode object

	auto stencil = DrawNode::create();		// create the DrawNode object which can draw dots, segments and polygons.

	Point triangle[3];		// init the  triangle vertexes.
	triangle[0] = Point(-size.width * 1.5f, -size.height / 2);
	triangle[1] = Point(size.width * 1.5f, -size.height / 2);
	triangle[2] = Point(0, size.height);
	Color4F green(0, 1, 0, 1);

	stencil->drawPolygon(triangle, 3, green, 0, green);		//use the drawNode to draw the triangle to cut the ClippingNode.

	clipper->setAnchorPoint(Point(0.5f, 0.5f));		// set the ClippingNode anchorPoint, to make sure the drawNode at the center of ClippingNode
	clipper->setPosition(size.width / 2, size.height / 2);
	clipper->setStencil(stencil);	//set the cut triangle in the ClippingNode.
	clipper->setInverted(true);		//make sure the content is show right side.

	Sprite* blackRect = Sprite::create("black_screen.png");		//create a black screen sprite to make sure the bottom is black.

	clipper->addChild(blackRect);	//to make sure the bottom is black.

	this->addChild(clipper, 500);

	// the Clipping node triangle  add some actions to make the triangle scale and rotate.  
	stencil->runAction(EaseSineOut::create(Spawn::create(ScaleTo::create(2.5f, 0.0f, 0.0f), RotateBy::create(2.5f, 540),
		Sequence::create(DelayTime::create(2.5f), CallFunc::create(this, callfunc_selector(MainMenu::toMenuExit)), NULL), NULL)));

}

void MainMenu::toMenuExit()
{
	//get the game scene and run it.
	Director::getInstance()->replaceScene(TransitionMoveInL::create(.5, (Scene*) ExitScene::create()));
}

//SUBFUNCTIONS:
void MainMenu::_createMainSubmenu()
{
	//create new menu items
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Label* label = (Label*)this->getChildByName("label");
	Menu* menu = (Menu*)this->getChildByTag(1);

	label->removeFromParentAndCleanup(true);

	for (std::vector<MenuItem*>::iterator it = m_addedItems.begin(); it != m_addedItems.end(); it++)
	{
		(*it)->removeFromParentAndCleanup(true);
	}
	m_addedItems.clear();

	label = Label::createWithTTF("Check your knowledge level", "fonts/Marker Felt.ttf", 24);
	label->setPosition(Vec2(visibleSize.width / 2,
		visibleSize.height - label->getContentSize().height));
	this->addChild(label, 1, "label");

	auto lowLabel = MenuItemFont::create("Beginner", CC_CALLBACK_1(MainMenu::menuCallback, this));
	auto medLabel = MenuItemFont::create("I can read kana", CC_CALLBACK_1(MainMenu::menuCallback, this));
	auto highLabel = MenuItemFont::create("I'm N5 Level", CC_CALLBACK_1(MainMenu::menuCallback, this));
	menu->addChild(lowLabel, 1);		m_addedItems.push_back(lowLabel);
	menu->addChild(medLabel, 1);		m_addedItems.push_back(medLabel);
	menu->addChild(highLabel, 1);		m_addedItems.push_back(highLabel);
	lowLabel->setTag(LLOW);
	medLabel->setTag(LMED);
	highLabel->setTag(LHIGH);
	menu->alignItemsVertically();
	lowLabel->setAnchorPoint(Vec2(1, 0.5f));
	medLabel->setAnchorPoint(Vec2(1, 0.5f));
	highLabel->setAnchorPoint(Vec2(1, 0.5f));
}

void MainMenu::_afterCaptured(bool succeed, const std::string& outputFile)
{
	if (succeed)
	{
		log(" screen shot%s", outputFile.c_str());
	}
	else
	{
		log("Capture screen failed.");
	}
}