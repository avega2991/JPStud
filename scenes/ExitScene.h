#ifndef __EXITSCENE_H__
#define __EXITSCENE_H__

#include "cocos2d.h"
#include "support\ConstValues.h"

//создать MainScene класса, унаследованных от cocos2d Layer класса.
class ExitScene : public cocos2d::Layer
{
public:
	//для определения функции инициализации, я компонент
	virtual bool init();
	//создать сцены
	static cocos2d::Scene* createScene();

	void menuCloseCallback(Ref* pSender);
	//создать сцены макросы
	CREATE_FUNC(ExitScene);
};
#endif // __HELLOWORLD_SCENE_H__