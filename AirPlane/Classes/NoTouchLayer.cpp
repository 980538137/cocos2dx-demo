#include "NoTouchLayer.h"

NoTouchLayer* NoTouchLayer::create()
{
	NoTouchLayer* pRet = new NoTouchLayer();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
}
bool NoTouchLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	setTouchEnabled(true);
	return true;
}

void NoTouchLayer::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-127,true);
	CCLayer::registerWithTouchDispatcher();
}

bool NoTouchLayer::ccTouchBegan(CCTouch *touch,CCEvent * event)
{
	return true;
}

void NoTouchLayer::ccTouchMoved(CCTouch *touch,CCEvent * event)
{


}

void NoTouchLayer::ccTouchEnded(CCTouch *touch,CCEvent * event)
{

}