#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "ui\CocosGUI.h"

#include <vector>

#include "scenes\ExitScene.h"
#include "scenes\FirstScene.h"
#include "support\GLAddition.h"
#include "support\ConstValues.h"

#define MAIN_MENU			1

#define LSTART				11
#define LCONT				12
#define LEXIT				13
#define LLOW				21
#define LMED				22
#define LHIGH				23

class MainMenu : public cocos2d::Layer
{
private:
	CocosDenshion::SimpleAudioEngine*					m_soundEngine;
	
	std::vector<cocos2d::MenuItem*>						m_addedItems;

	// progress bar
	int m_counter = 0;

public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene*								createScene();
	
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    bool												init();
    
	// implement the "static create()" method manually
	CREATE_FUNC(MainMenu);

    // a selector callback
	void												menuCallback(cocos2d::Ref* pSender);
    
	void												checkboxCallback();
    
	void												transitionToMenuExit();
	void												toMenuExit();
	void												updateProgress(float dt);

	//SUBFUNCTIONS
	void												_createMainSubmenu();
	void												_afterCaptured(bool, const std::string&);
	
};

#endif // __MAINMENU_SCENE_H__
