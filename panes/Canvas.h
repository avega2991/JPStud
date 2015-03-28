#pragma once

#include "cocos2d.h"

#define CANVAS_BACKGROUND							110
#define CANVAS_COVER								120
#define CANVAS_DYNAMIC_TEXTURE						130

#define MAX_BRUSH_DEPTH_PX							16
#define MIN_BRUSH_DEPTH_PX							8
#define DEFAULT_BRUSH_DEPTH_PX						8


class Canvas : public cocos2d::Layer
{
private:
	cocos2d::RenderTexture*							m_dynamicTexture;
	cocos2d::Size									m_stencilSize;

	cocos2d::EventListenerTouchOneByOne*			m_listener;

	cocos2d::Size									m_size;
	cocos2d::Vec2									m_position;

	cocos2d::Sprite*								m_brushPoint;
	float											m_brushDepthPx;

public:
	Canvas();
	~Canvas();

	static Canvas*									create();

	cocos2d::RenderTexture*							getDynamicTexture();
	cocos2d::Sprite*								getBrushPoint();
	float											getBrushDepth();

	virtual const cocos2d::Size						getContentSize();
	virtual const cocos2d::Vec2						getPosition();

	cocos2d::EventListener*							getEventListener();
	
	void											setPosition(const cocos2d::Vec2&);
	void											setBrushDepth(float depthPx);
	
	void											resetDynamicTexture();

	void											drawEvenlySpacedSprites(cocos2d::Vec2, cocos2d::Vec2);
	
	bool											onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	void											onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
	void											onTouchEnded(cocos2d::Touch*, cocos2d::Event*);

};