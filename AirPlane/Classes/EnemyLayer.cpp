#include "EnemyLayer.h"
#include "GameLayer.h"

EnemyLayer::EnemyLayer(void)
{
	enemy1SpriteFrame = NULL;
	enemy2SpriteFrame = NULL;
	enemy3SpriteFrame_1 = NULL;
	enemy3SpriteFrame_2 = NULL;

	m_pAllEnemy1 = CCArray::create();
	m_pAllEnemy1->retain();

	m_pAllEnemy2 = CCArray::create();
	m_pAllEnemy2->retain();

	m_pAllEnemy3 = CCArray::create();
	m_pAllEnemy3->retain();
}

EnemyLayer::~EnemyLayer(void)
{
	m_pAllEnemy1->release();
	m_pAllEnemy1 = NULL;

	m_pAllEnemy2->release();
	m_pAllEnemy2 = NULL;

	m_pAllEnemy3->release();
	m_pAllEnemy3 = NULL;
}

EnemyLayer* EnemyLayer::create()
{
	EnemyLayer* pRet = new EnemyLayer();
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

bool EnemyLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCLayer::init());
		enemy1SpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1.png");
		enemy2SpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2.png");
		enemy3SpriteFrame_1 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_n1.png");
		enemy3SpriteFrame_2 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_n2.png");

		CCAnimation* animation1 = CCAnimation::create();
		animation1->setDelayPerUnit(0.1f);
		animation1->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down1.png"));
		animation1->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down2.png"));
		animation1->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down3.png"));
		animation1->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down4.png"));

		CCAnimation* animation2 = CCAnimation::create();
		animation2->setDelayPerUnit(0.2f);
		animation2->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2_down1.png"));
		animation2->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2_down2.png"));
		animation2->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2_down3.png"));
		animation2->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2_down4.png"));

		CCAnimation* animation3 = CCAnimation::create();
		animation3->setDelayPerUnit(0.2f);
		animation3->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down1.png"));
		animation3->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down2.png"));
		animation3->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down3.png"));
		animation3->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down4.png"));
		animation3->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down5.png"));
		animation3->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down6.png"));
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation1,"Enemy1Blowup");
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation2,"Enemy2Blowup");
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation3,"Enemy3Blowup");

		this->schedule(schedule_selector(EnemyLayer::addEnemy1),0.5f);
		this->schedule(schedule_selector(EnemyLayer::addEnemy2),3.0f);
		this->schedule(schedule_selector(EnemyLayer::addEnemy3),6.0f);

		bRet  =true;
	} while (0);
	return bRet;
}

void EnemyLayer::addEnemy1(float dt)
{
	Enemy* enemy1 = Enemy::create();
	enemy1->bindSprite(CCSprite::createWithSpriteFrame(enemy1SpriteFrame),ENEMY1_MAX_LIFE);

	CCSize enemySize = enemy1->getSprite()->getContentSize();
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	int minX = enemySize.width/2;
	int maxX = winSize.width - enemySize.width/2;
	int rangeX = maxX - minX;
	int actualX = (rand()%rangeX) + minX;

	enemy1->setPosition(ccp(actualX,winSize.height + enemySize.height/2));
	this->addChild(enemy1);
	this->m_pAllEnemy1->addObject(enemy1);

	float minDuration,maxDuration;
	switch (GameLayer::getCurLevel())
	{
	case EASY:
		minDuration = 2.0f;
		maxDuration = 4.0f;
		break;
	case MIDDLE:
		minDuration = 1.8f;
		maxDuration = 3.6f;
		break;
	case HARD:
		minDuration = 1.6f;
		maxDuration = 3.2f;
		break;
	default:
		minDuration = 2.0f;
		maxDuration = 4.0f;
		break;
	}

	int rangeDuration = maxDuration - minDuration;
	int actualDuration = (rand()%rangeDuration) + minDuration;

	CCFiniteTimeAction* actionMove = CCMoveTo::create(actualDuration,ccp(actualX,0 - enemy1->getSprite()->getContentSize().height/2));
	CCFiniteTimeAction* actionDone = CCCallFuncN::create(this,callfuncN_selector(EnemyLayer::enemy1MoveFinished));
	CCSequence* sequence = CCSequence::create(actionMove,actionDone,NULL);
	enemy1->runAction(sequence);
}



void EnemyLayer::enemy1MoveFinished(CCNode* pSender)
{
	Enemy* enemy1 = (Enemy*)pSender;
	this->removeChild(enemy1,true);
	m_pAllEnemy1->removeObject(enemy1);
}

void EnemyLayer::enemy1Blowup(Enemy* enemy1)
{
	enemy1->stopAllActions();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/enemy1_down.mp3");
	CCAnimation* animation = CCAnimationCache::sharedAnimationCache()->animationByName("Enemy1Blowup");
	CCAnimate* animate  =CCAnimate::create(animation);
	CCCallFuncND* removeEnemy1 = CCCallFuncND::create(this,callfuncND_selector(EnemyLayer::removeEnemy1),(void*)enemy1);
	CCSequence* sequence  =CCSequence::create(animate,removeEnemy1,NULL);
	enemy1->getSprite()->runAction(sequence);
}

void EnemyLayer::removeEnemy1(CCNode* pTarge,void* data)
{
	Enemy* enemy1 = (Enemy*)data;
	if(enemy1 != NULL)
	{
		this->removeChild(enemy1,true);
		m_pAllEnemy1->removeObject(enemy1);
	}

}
void EnemyLayer::removeAllEnemy1()
{
	CCObject* obj;
	CCARRAY_FOREACH(m_pAllEnemy1,obj)
	{
		Enemy* enemy1 = (Enemy*)obj;
		if(enemy1->getLife() > 0)
		{
			enemy1Blowup(enemy1);
		}
	}
}

void EnemyLayer::addEnemy2(float dt)
{
	Enemy* enemy2 = Enemy::create();
	enemy2->bindSprite(CCSprite::createWithSpriteFrame(enemy2SpriteFrame),ENEMY2_MAX_LIFE);

	CCSize enemy2Size = enemy2->getSprite()->getContentSize();
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	int minX = enemy2Size.width/2;
	int maxX = winSize.width - enemy2Size.width/2;
	int rangeX = maxX - minX;
	int actualX = (rand()%rangeX) + minX;

	enemy2->setPosition(ccp(actualX,winSize.height + enemy2Size.height/2));
	this->addChild(enemy2);
	this->m_pAllEnemy2->addObject(enemy2);

	float minDuration,maxDuration;
	switch (GameLayer::getCurLevel())
	{
	case EASY:
		minDuration=3.0f;
		maxDuration=6.0f;
		break;
	case MIDDLE:
		minDuration=2.7f;
		maxDuration=5.4f;
		break;
	case HARD:
		minDuration=2.5f;
		maxDuration=5.0f;
		break;
	default:
		minDuration=3.0f;
		maxDuration=6.0f;
		break;
	}

	int rangeDuration = maxDuration - minDuration;
	int actualDuration = (rand()%rangeDuration) + minDuration;

	CCFiniteTimeAction* actionMove = CCMoveTo::create(actualDuration,ccp(actualX,0 - enemy2->getSprite()->getContentSize().height/2));
	CCFiniteTimeAction* actionDone = CCCallFuncN::create(this,callfuncN_selector(EnemyLayer::enemy2MoveFinished));

	CCSequence* sequence = CCSequence::create(actionMove,actionDone,NULL);

	enemy2->runAction(sequence);
}

void EnemyLayer::enemy2MoveFinished(CCNode* pSender)
{
	
	Enemy* enemy2 = (Enemy*)pSender;
	this->removeChild(enemy2,true);
	this->m_pAllEnemy2->removeObject(enemy2);
}

void EnemyLayer::enemy2Blowup(Enemy* enemy2)
{
	enemy2->stopAllActions();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/enemy2_down.mp3");
	CCAnimation* animation = CCAnimationCache::sharedAnimationCache()->animationByName("Enemy2Blowup");
	CCAnimate* animate  =CCAnimate::create(animation);
	CCCallFuncND* removeEnemy2 = CCCallFuncND::create(this,callfuncND_selector(EnemyLayer::removeEnemy2),(void*)enemy2);
	CCSequence* sequence  =CCSequence::create(animate,removeEnemy2,NULL);
	enemy2->getSprite()->runAction(sequence);
}

void EnemyLayer::removeEnemy2(CCNode* pTarget,void* data)
{
	Enemy* enemy2 = (Enemy*)data;
	if (enemy2 != NULL)
	{
		this->removeChild(enemy2,true);
		this->m_pAllEnemy2->removeObject(enemy2);
	}
}

void EnemyLayer::removeAllEnemy2()
{
	CCObject* obj;
	CCARRAY_FOREACH(m_pAllEnemy2,obj)
	{

		Enemy* enemy2 = (Enemy*)obj;
		if(enemy2->getLife() > 0)
		{
			enemy2Blowup(enemy2);
		}
	}

}

void EnemyLayer::addEnemy3(float dt)
{
	Enemy* enemy3 = Enemy::create();
	enemy3->bindSprite(CCSprite::createWithSpriteFrame(enemy3SpriteFrame_1),ENEMY3_MAX_LIFE);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSize enemy3Size = enemy3->getSprite()->getContentSize();

	int minX = enemy3Size.width/2;
	int maxX = winSize.width - enemy3Size.width/2;
	int rangeX = maxX - minX;
	int actualX = (rand()%rangeX) + minX;

	enemy3->setPosition(ccp(actualX,winSize.height + enemy3Size.height/2));
	this->addChild(enemy3);
	this->m_pAllEnemy3->addObject(enemy3);

	int minDuration,maxDuration;
	switch (GameLayer::getCurLevel())
	{
	case EASY:
		minDuration=4.0;
		maxDuration=8.0;
		break;
	case MIDDLE:
		minDuration=3.6;
		maxDuration=7.2;
		break;
	case HARD:
		minDuration=3.2;
		maxDuration=6.4;
		break;
	default:
		minDuration=4.0;
		maxDuration=8.0;
		break;
	}
	int rangeDuration = maxDuration - minDuration;
	int acutalDuration = rand()%rangeDuration + minDuration;

	CCFiniteTimeAction* moveAction = CCMoveTo::create(acutalDuration,ccp(actualX,0 - enemy3Size.height/2));
	CCFiniteTimeAction* actionDone = CCCallFuncN::create(this,callfuncN_selector(EnemyLayer::enemy3MoveFinished));
	CCSequence* sequence = CCSequence::create(moveAction,actionDone,NULL);
	enemy3->runAction(sequence);

	CCAnimation* animation = CCAnimation::create();
	animation->setDelayPerUnit(0.2f);
	animation->addSpriteFrame(enemy3SpriteFrame_1);
	animation->addSpriteFrame(enemy3SpriteFrame_2);
	CCAnimate*  animate = CCAnimate::create(animation);
	enemy3->getSprite()->runAction(CCRepeatForever::create(animate));

}

void EnemyLayer::enemy3MoveFinished(CCNode* pSender)
{
	Enemy* enemy3 = (Enemy*)pSender;
	this->removeChild(enemy3,true);
	this->m_pAllEnemy3->removeObject(enemy3);
}

void EnemyLayer::enemy3Blowup(Enemy* enemy3)
{
	enemy3->stopAllActions();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/enemy3_down.mp3");
	CCAnimation* animation = CCAnimationCache::sharedAnimationCache()->animationByName("Enemy3Blowup");
	CCAnimate* animate = CCAnimate::create(animation);
	CCCallFuncND *actionDone = CCCallFuncND::create(this,callfuncND_selector(EnemyLayer::removeEnemy3),(void*)enemy3);
	CCSequence* sequence = CCSequence::create(animate,actionDone,NULL);
	enemy3->getSprite()->runAction(sequence);
}

void EnemyLayer::removeEnemy3(CCNode* pTarge,void* data)
{
	Enemy* enemy3 = (Enemy*)data;
	if (enemy3 != NULL)
	{
		this->removeChild(enemy3,true);
		this->m_pAllEnemy3->removeObject(enemy3);
	}

}

void EnemyLayer::removeAllEnemy3()
{
	CCObject* obj;
	CCARRAY_FOREACH(m_pAllEnemy3,obj)
	{
		Enemy* enemy3 = (Enemy*)obj;
		if (enemy3->getLife() > 0)
		{
			enemy3Blowup(enemy3);
		}
	}
}

void EnemyLayer::removeAllEnemy()
{
	CCObject* obj;

	CCARRAY_FOREACH(m_pAllEnemy1,obj)
	{
		Enemy* enemy1 = (Enemy*)obj;
		if(enemy1->getLife() > 0)
		{
			enemy1Blowup(enemy1);
		}
	}

	CCARRAY_FOREACH(m_pAllEnemy2,obj)
	{

		Enemy* enemy2 = (Enemy*)obj;
		if(enemy2->getLife() > 0)
		{
			enemy2Blowup(enemy2);
		}
	}
	CCARRAY_FOREACH(m_pAllEnemy3,obj)
	{

		Enemy* enemy3 = (Enemy*)obj;
		if(enemy3->getLife() > 0)
		{
			enemy2Blowup(enemy3);
		}
	}
}