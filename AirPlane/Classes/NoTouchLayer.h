#ifndef __NOTOUCHLAYER_H_
#define __NOTOUCHLAYER_H_

#include "cocos2d.h"

using namespace cocos2d;

class NoTouchLayer : public CCLayer
{
public:
	static NoTouchLayer* create();
	virtual bool init();

	virtual void registerWithTouchDispatcher();

	virtual bool ccTouchBegan(CCTouch *touch,CCEvent * event);
	virtual void ccTouchMoved(CCTouch *touch,CCEvent * event);
	virtual void ccTouchEnded(CCTouch *touch,CCEvent * event);

};

#endif