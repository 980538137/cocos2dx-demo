#ifndef __GameLayer_H_
#define __GameLayer_H_

#include "cocos2d.h"
#include "PlaneLayer.h"
#include "BulletLayer.h"
#include "EnemyLayer.h"
#include "ControllLayer.h"
#include "MultiBulletsLayer.h"
#include "UFOLayer.h"

using namespace cocos2d;

const int ENEMY1_SCORE = 1000;
const int ENEMY2_SCORE = 6000;
const int ENEMY3_SCORE = 30000;

class GameLayer : public CCLayer
{
public:

	CCSprite* background1;
	CCSprite* background2;
	PlaneLayer* planeLayer;
	BulletLayer* bulletLayer;
	EnemyLayer* enemyLayer;
	ControllLayer* controllLayer;
	MultiBulletsLayer* multiBulletsLayer;
	UFOLayer* ufoLayer;

	CCMenu* menuBigBoom;
	CCLabelBMFont* bigBoomCountItem;

	int score;
	int bigBoomCount;
	static Level level;

public:

	GameLayer(void);
	~GameLayer(void);

	static cocos2d::CCScene* scene();

	//static GameLayer* create();

	virtual bool init();

	void backgroundMove(float tmd);

	bool ccTouchBegan(CCTouch *pTouch,CCEvent* pEvent);
	void ccTouchMoved(CCTouch *pTouch,CCEvent* pEvent);
	void ccTouchEnded(CCTouch *pTouch,CCEvent* pEvent);

	void registerWithTouchDispatcher();

	void update(float dt);

	void updateBigBoomCountItem(int bigBoomCount);

	void menuBigBoomCallback(CCObject* pSender);

	static Level getCurLevel();

	CREATE_FUNC(GameLayer);
	

	
};

#endif // !__GameLayer_H__
