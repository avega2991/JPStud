#ifndef __EXITSCENE_H__
#define __EXITSCENE_H__

#include "cocos2d.h"
#include "support\ConstValues.h"

//������� MainScene ������, �������������� �� cocos2d Layer ������.
class ExitScene : public cocos2d::Layer
{
public:
	//��� ����������� ������� �������������, � ���������
	virtual bool init();
	//������� �����
	static cocos2d::Scene* createScene();

	void menuCloseCallback(Ref* pSender);
	//������� ����� �������
	CREATE_FUNC(ExitScene);
};
#endif // __HELLOWORLD_SCENE_H__