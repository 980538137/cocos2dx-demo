#ifndef __CONTROLLLAYER_H_
#define __CONTROLLLAYER_H_

#include "cocos2d.h"
#include "NoTouchLayer.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

const int MAX_SCORE = 1000000000;

class ControllLayer : public CCLayer
{
public:
	ControllLayer();
	~ControllLayer();

	static ControllLayer* create();
	virtual bool init();

	void menuPauseCallback(CCObject* pSender);
	void updateScore(int score);
public:
	CCLabelBMFont *scoreItem;
	CCMenuItemImage * pPauseItem;
	NoTouchLayer *noTouchLayer;

};
#endif