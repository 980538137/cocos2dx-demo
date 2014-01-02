#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class MultiBulletsLayer : public CCLayer
{
public:
	MultiBulletsLayer(void);
	~MultiBulletsLayer(void);
	static MultiBulletsLayer* create();

	virtual bool init();

	void addMultiBullet(float dt);
	void multiBulletMoveFinished(CCNode* pSender);
	void removeMultiBullets(CCSprite* multiBullets);

	void startShoot();
	void stopShoot();

	


public:
	CCSpriteBatchNode* m_pBulletBatchNode;
	CCArray* m_pAllMultiBullets;
};