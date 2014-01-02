#include "UFOLayer.h"

UFOLayer::UFOLayer(void)
{
	m_pAllMultiBullets = CCArray::create();
	m_pAllMultiBullets->retain();

	m_pAllBigBoom = CCArray::create();
	m_pAllBigBoom->retain();

}

UFOLayer::~UFOLayer(void)
{
	m_pAllMultiBullets->release();
	m_pAllMultiBullets = NULL;

	m_pAllBigBoom->release();
	m_pAllBigBoom = NULL;

}

UFOLayer* UFOLayer::create()
{
	UFOLayer* pRet = new UFOLayer();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}
 
bool UFOLayer::init()
{
	bool pRet = false;

	do 
	{

		this->schedule(schedule_selector(UFOLayer::addMultiBullets),20.0f,kCCRepeatForever,0.0f);
		this->schedule(schedule_selector(UFOLayer::addBigBoom),20.0f,kCCRepeatForever,5.0f);
		pRet = true;
	} while (0);
	return pRet;
}

void UFOLayer::addMultiBullets(float dt)
{
	CCSprite* multiBullets = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ufo1.png"));

	CCSize multiBulletsSize = multiBullets->getContentSize();
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	int minX = multiBulletsSize.width/2;
	int maxX = winSize.width - multiBulletsSize.width/2;
	int rangeX = maxX - minX;
	int actualX = (rand()%rangeX) + minX;

	multiBullets->setPosition(ccp(actualX,winSize.height + multiBulletsSize.height/2));
	this->addChild(multiBullets);
	this->m_pAllMultiBullets->addObject(multiBullets);

	CCMoveBy* move1 = CCMoveBy::create(0.5f,CCPointMake(0,-150));
	CCMoveBy* move2 = CCMoveBy::create(0.3f,CCPointMake(0,100));
	CCMoveBy* move3 = CCMoveBy::create(1.0f,CCPointMake(0,0-winSize.height - multiBulletsSize.height/2));
	CCCallFuncN* moveDone = CCCallFuncN::create(this,callfuncN_selector(UFOLayer::multiBulletsMoveFinished));
	CCSequence* sequence = CCSequence::create(move1,move2,move3,moveDone,NULL);

	multiBullets->runAction(sequence);
}

void UFOLayer::addBigBoom(float dt)
{
	CCSprite* bigBoom = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ufo2.png"));

	CCSize bigBoomSize = bigBoom->getContentSize();
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	int minX = bigBoomSize.width/2;
	int maxX = winSize.width - bigBoomSize.width/2;
	int rangeX = maxX - minX;
	int actualX = (rand()%rangeX) + minX;

	bigBoom->setPosition(ccp(actualX,winSize.height + bigBoomSize.height/2));
	this->addChild(bigBoom);
	this->m_pAllBigBoom->addObject(bigBoom);

	CCMoveBy* move1 = CCMoveBy::create(0.5f,CCPointMake(0,-150));
	CCMoveBy* move2 = CCMoveBy::create(0.3f,CCPointMake(0,100));
	CCMoveBy* move3 = CCMoveBy::create(1.0f,CCPointMake(0,0-winSize.height-bigBoomSize.height/2));
	CCCallFuncN* moveDone = CCCallFuncN::create(this,callfuncN_selector(UFOLayer::bigBoomMoveFinished));
	CCSequence* sequence = CCSequence::create(move1,move2,move3,moveDone,NULL);

	bigBoom->runAction(sequence);

}

void UFOLayer::multiBulletsMoveFinished(CCNode* pSender)
{
	CCSprite* multiBullets = (CCSprite*)pSender;
	this->m_pAllMultiBullets->removeObject(multiBullets);
	this->removeChild(multiBullets,true);
}

void UFOLayer::removeMultiBullets(CCSprite* multiBullets)
{
	this->removeChild(multiBullets,true);
	this->m_pAllMultiBullets->removeObject(multiBullets);
}



void UFOLayer::bigBoomMoveFinished(CCNode* pSender)
{
	CCSprite* bigBoom = (CCSprite*)pSender;
	this->m_pAllBigBoom->removeObject(bigBoom,true);
	this->removeChild(bigBoom);
}

void UFOLayer::removeBigBoom(CCSprite* bigBoom)
{
	this->m_pAllBigBoom->removeObject(bigBoom,true);
	this->removeChild(bigBoom);
}
