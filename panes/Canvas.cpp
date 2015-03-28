#include "panes\Canvas.h"
#include "support\ConstValues.h"
#include "support\GLAddition.h"

USING_NS_CC;

Canvas::Canvas()
{
	//create canvas
	//Layer* canvasLayer = Layer::create();

	Sprite* canvasCover = Sprite::create("textures/interface/dictionary/canvas_cover.png");
	canvasCover->setPosition(Vec2(0, 0));
	canvasCover->setAnchorPoint(Vec2(0, 0));

	Sprite* canvasBackground = Sprite::create();
	canvasBackground->setPosition(Vec2(0, 0));
	canvasBackground->setAnchorPoint(Vec2(0, 0));
	canvasBackground->setContentSize(canvasCover->getContentSize());
	canvasBackground->setTextureRect(Rect(0, 0,
		canvasCover->getContentSize().width, canvasCover->getContentSize().height));
	canvasBackground->setColor(Color3B(255, 255, 255));

	//creating "drawing layer"
	m_dynamicTexture = RenderTexture::create(canvasBackground->getContentSize().width, canvasBackground->getContentSize().height);
	m_dynamicTexture->setPosition(Vec2(canvasBackground->getContentSize().width / 2, canvasBackground->getContentSize().height / 2));

	this->addChild(canvasBackground, 1, CANVAS_BACKGROUND);
	this->addChild(canvasCover, 2, CANVAS_COVER);
	this->addChild(m_dynamicTexture, 3, CANVAS_DYNAMIC_TEXTURE);

	//init stencil
	m_brushPoint = Sprite::create("textures/interface/dictionary/black_point.png");
	m_brushPoint->setPosition(Vec2(-100, -100)); // invisible
	this->addChild(m_brushPoint);

	m_brushDepthPx = DEFAULT_BRUSH_DEPTH_PX;

	//set contentSize and Position
	m_size = canvasBackground->getContentSize();
	m_position = Vec2(0, 0);

	//init listener
	m_listener = EventListenerTouchOneByOne::create();
	m_listener->setSwallowTouches(false);
	m_listener->onTouchBegan = CC_CALLBACK_2(Canvas::onTouchBegan, this);
	m_listener->onTouchMoved = CC_CALLBACK_2(Canvas::onTouchMoved, this);
	m_listener->onTouchEnded = CC_CALLBACK_2(Canvas::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithFixedPriority(m_listener, DIALOG_PRIORITY);
}

Canvas::~Canvas()
{
	_eventDispatcher->removeEventListener(m_listener);

	this->removeAllChildrenWithCleanup(true);
	this->removeFromParentAndCleanup(true);

	// delete m_dynamicTexture;
	// delete this;
}

Canvas* Canvas::create()
{
	Canvas*	pCanvas = new Canvas();
	
	if (pCanvas->init())
	{
		pCanvas->autorelease();
		return pCanvas;
	}

	CC_SAFE_DELETE(pCanvas);
	return nullptr;
}

RenderTexture*	Canvas::getDynamicTexture()
{
	return m_dynamicTexture;
}

Sprite*	Canvas::getBrushPoint()
{
	return m_brushPoint;
}

float	Canvas::getBrushDepth()
{
	return m_brushDepthPx;
}

const Size	Canvas::getContentSize()
{
	return m_size;
}

const Vec2	Canvas::getPosition()
{
	return m_position;
}

EventListener*	Canvas::getEventListener()
{
	return m_listener;
}

void	Canvas::setPosition(const Vec2& pos)
{
	m_position = pos;
	Layer::setPosition(pos);
}

void	Canvas::setBrushDepth(float depthPx)
{
	if ((depthPx < MIN_BRUSH_DEPTH_PX) || (depthPx > MAX_BRUSH_DEPTH_PX))
		return;

	m_brushDepthPx = depthPx;
}

void	Canvas::resetDynamicTexture()
{
	m_dynamicTexture->clear(0, 0, 0, 0);
}

void  Canvas::drawEvenlySpacedSprites(Vec2 start, Vec2 end) {
	// begin drawing to the render texture
	m_dynamicTexture->begin();

	float distance = start.getDistance(end);
	if (distance > 1) 
	{
		int d = (int) distance;

		for (int i = 0; i < d; i++)
		{
			float difx = end.x - start.x;
			float dify = end.y - start.y;
			float delta = (float) i / distance;

			Sprite* brush = Sprite::createWithSpriteFrame(m_brushPoint->getSpriteFrame());
			brush->setPosition(Vec2(start.x + (difx * delta), start.y + (dify * delta)));
			brush->setScale(m_brushDepthPx / DEFAULT_BRUSH_DEPTH_PX);
			brush->visit();
		}
	}

	// finish drawing and return context back to the screen
	m_dynamicTexture->end();
}

bool Canvas::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	CCLOG("Canvas's listener: onTouchBegan x = %f, y = %f, name = %s", touch->getLocation().x, touch->getLocation().y, this->getName());
	
	m_listener->setSwallowTouches(true);
	
	return true;
}

void Canvas::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
	CCLOG("Canvas's listener: onTouchMoved x = %f, y = %f", touch->getLocation().x, touch->getLocation().y);
	
	Canvas::drawEvenlySpacedSprites(Vec2(touch->getLocation().x - m_position.x, touch->getLocation().y - m_position.y),
		Vec2(touch->getPreviousLocation().x - m_position.x, touch->getPreviousLocation().y - m_position.y));
}

void Canvas::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	CCLOG("Canvas's listener: onTouchEnded x = %f, y = %f", touch->getLocation().x, touch->getLocation().y);

	// 3. Return touches to player
	m_listener->setSwallowTouches(false);
}
