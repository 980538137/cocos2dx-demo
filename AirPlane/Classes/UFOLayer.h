#pragma once

#include "cocos2d.h"

USING_NS_CC;

class UFOLayer : public CCLayer
{
public:
	UFOLayer(void);
	~UFOLayer(void);

	static UFOLayer* create();

	virtual bool init();

	void addMultiBullets(float dt);

	void multiBulletsMoveFinished(CCNode* pSender);

	void removeMultiBullets(CCSprite* multiBullets);

	void addBigBoom(float dt);

	void bigBoomMoveFinished(CCNode* pSender);

	void removeBigBoom(CCSprite* bigBoom);
public:
	CCArray* m_pAllMultiBullets;
	CCArray* m_pAllBigBoom;
};