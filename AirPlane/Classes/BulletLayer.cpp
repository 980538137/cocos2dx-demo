#include "BulletLayer.h"
#include "PlaneLayer.h"
using namespace cocos2d;

BulletLayer::BulletLayer(void)
{
	m_pAllBullet = CCArray::create();
	m_pAllBullet->retain();
}

BulletLayer::~BulletLayer(void)
{
	m_pAllBullet->release();
	m_pAllBullet = NULL;
}

BulletLayer* BulletLayer::create()
{
	BulletLayer* pRet = new BulletLayer();
	if(pRet && pRet->init())
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
bool BulletLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCLayer::init());
		CCTexture2D* texture = CCTextureCache::sharedTextureCache()->textureForKey("ui/shoot.png");
		bulletBatchNode = CCSpriteBatchNode::createWithTexture(texture);
		this->addChild(bulletBatchNode);
		bRet = true;
	} while (0);

	return bRet;
	
}
void BulletLayer::AddBullet(float dt)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/bullet.mp3");
	CCSprite* bullet = CCSprite::createWithSpriteFrameName("bullet1.png");
	bulletBatchNode->addChild(bullet);
	m_pAllBullet->addObject(bullet);

	CCPoint planePosition = PlaneLayer::sharedPlane->getChildByTag(AIRPLANE)->getPosition();
	CCPoint bulletPosition = ccp(planePosition.x,planePosition.y + PlaneLayer::sharedPlane->getChildByTag(AIRPLANE)->getContentSize().height/2);
	bullet->setPosition(bulletPosition);

	float length = CCDirector::sharedDirector()->getWinSize().height + bullet->getContentSize().height/2 - bullet->getPosition().y;
	float velocity = 600/1;//pixel/s
	float realMoveDuration = length / velocity;
	CCFiniteTimeAction* actionMove = CCMoveTo::create(realMoveDuration,ccp(bullet->getPosition().x,CCDirector::sharedDirector()->getWinSize().height + bullet->getContentSize().height/2));
	CCFiniteTimeAction* actionDone = CCCallFuncN::create(this,callfuncN_selector(BulletLayer::bulletMoveFinished));
	CCSequence* sequence = CCSequence::create(actionMove,actionDone,NULL);
	bullet->runAction(sequence);

}
void BulletLayer::bulletMoveFinished(CCNode* pSender)
{
	CCSprite* bullet = (CCSprite*)pSender;
	bulletBatchNode->removeChild(bullet,true);
	m_pAllBullet->removeObject(bullet);
}

void BulletLayer::startShoot(float delay)
{
	this->schedule(schedule_selector(BulletLayer::AddBullet),0.1f,kCCRepeatForever,delay);
}

void BulletLayer::stopShoot()
{
	this->unschedule(schedule_selector(BulletLayer::AddBullet));
}

void BulletLayer::removeBullet(CCSprite* bullet)
{
	if(bullet != NULL)
	{
		this->m_pAllBullet->removeObject(bullet);
		this->bulletBatchNode->removeChild(bullet,true);
	}
}