#include "MultiBulletsLayer.h"
#include "PlaneLayer.h"

MultiBulletsLayer::MultiBulletsLayer(void)
{
	m_pBulletBatchNode = NULL;
	m_pAllMultiBullets = CCArray::create();
	m_pAllMultiBullets->retain();
} 

MultiBulletsLayer::~MultiBulletsLayer(void)
{
	m_pAllMultiBullets->release();
	m_pAllMultiBullets = NULL;
}

MultiBulletsLayer* MultiBulletsLayer::create()
{
	MultiBulletsLayer* pRet = new MultiBulletsLayer();
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

bool MultiBulletsLayer::init()
{
	bool pRet = false;

	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		CCTexture2D* texture = CCTextureCache::sharedTextureCache()->textureForKey("ui/shoot.png");
		m_pBulletBatchNode = CCSpriteBatchNode::createWithTexture(texture);
		this->addChild(m_pBulletBatchNode);

		pRet = true;
	} while (0);
	return pRet;
}

void MultiBulletsLayer::startShoot()
{
	this->schedule(schedule_selector(MultiBulletsLayer::addMultiBullet),0.1f,60,0.1f);
}

void MultiBulletsLayer::stopShoot()
{
	this->unschedule(schedule_selector(MultiBulletsLayer::addMultiBullet));
}


void MultiBulletsLayer::addMultiBullet(float dt)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/bullet.mp3");
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCSprite* leftBullet = CCSprite::createWithSpriteFrameName("bullet2.png");
	CCSprite* rightBullet = CCSprite::createWithSpriteFrameName("bullet2.png");
	this->m_pBulletBatchNode->addChild(leftBullet);
	this->m_pBulletBatchNode->addChild(rightBullet);
	this->m_pAllMultiBullets->addObject(leftBullet);
	this->m_pAllMultiBullets->addObject(rightBullet);

	CCPoint planePosition = PlaneLayer::sharedPlane->getChildByTag(AIRPLANE)->getPosition();
	CCPoint leftPosition = ccp(planePosition.x - 30,planePosition.y + 35);
	CCPoint rightPosition = ccp(planePosition.x + 30,planePosition.y + 35);
	leftBullet->setPosition(leftPosition);
	rightBullet->setPosition(rightPosition);

	float length = winSize.height + leftBullet->getContentSize().height/2 - leftPosition.y;
	float velocity = 620/1;
	float actualDuration = length/velocity;

	CCFiniteTimeAction* actionLeftMove = CCMoveTo::create(actualDuration,ccp(leftPosition.x,winSize.height + leftBullet->getContentSize().height/2));
	CCFiniteTimeAction* actionLeftDone = CCCallFuncN::create(this,callfuncN_selector(MultiBulletsLayer::multiBulletMoveFinished));
	CCSequence* leftSequence = CCSequence::create(actionLeftMove,actionLeftDone,NULL);
	leftBullet->runAction(leftSequence);

	CCFiniteTimeAction* actionRightMove = CCMoveTo::create(actualDuration,ccp(rightPosition.x,winSize.height + rightBullet->getContentSize().height/2));
	CCFiniteTimeAction* actionRightDone = CCCallFuncN::create(this,callfuncN_selector(MultiBulletsLayer::multiBulletMoveFinished));
	CCSequence* rightSequence = CCSequence::create(actionRightMove,actionRightDone,NULL);
	rightBullet->runAction(rightSequence);
}

void MultiBulletsLayer::multiBulletMoveFinished(CCNode* pSender)
{
	CCSprite* bullet = (CCSprite*)pSender;
	this->m_pAllMultiBullets->removeObject(bullet);
	this->m_pBulletBatchNode->removeChild(bullet,true);

}

void MultiBulletsLayer::removeMultiBullets(CCSprite* multiBullets)
{
	if (multiBullets != NULL)
	{
		this->m_pAllMultiBullets->removeObject(multiBullets);
		this->m_pBulletBatchNode->removeChild(multiBullets,true);
	}
}