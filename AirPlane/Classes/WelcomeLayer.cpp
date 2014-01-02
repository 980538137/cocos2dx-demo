#include "WelcomeLayer.h"
#include "GameScene.h"

WelcomeLayer::WelcomeLayer(void)
{

}

WelcomeLayer::~WelcomeLayer(void)
{


}

WelcomeLayer* WelcomeLayer::create()
{
	WelcomeLayer* pRet = new WelcomeLayer();
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
bool WelcomeLayer::init()
{
	bool pRet = false;
	do 
	{
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/shoot_background.plist");
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/shoot.plist");

		CCSize winSize  =CCDirector::sharedDirector()->getWinSize();

		CCSprite* backGround = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background.png"));
		backGround->setPosition(ccp(winSize.width/2,winSize.height/2));
		this->addChild(backGround);

		CCSprite* copyright = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("shoot_copyright.png"));
		copyright->setPosition(ccp(winSize.width/2,winSize.height/2));
		copyright->setAnchorPoint(ccp(0.5,0.0));
		this->addChild(copyright);

		CCSprite* loading = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading1.png"));
		loading->setPosition(ccp(winSize.width/2,winSize.height/2 - 10));
		this->addChild(loading);

		CCAnimation* animation = CCAnimation::create();
		animation->setDelayPerUnit(0.2f);
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading1.png"));
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading2.png"));
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading3.png"));
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading4.png"));

		CCAnimate* animate = CCAnimate::create(animation);
		CCRepeat* repeat = CCRepeat::create(animate,2);
		CCCallFuncN* repeatDone = CCCallFuncN::create(this,callfuncN_selector(WelcomeLayer::loadingDone));
		CCSequence* sequence = CCSequence::create(repeat,repeatDone,NULL);
		loading->runAction(sequence);

		this->setKeypadEnabled(true);

		getHighestHistoryScore();

		pRet = true;
	} while (0);
	return pRet;
}

void WelcomeLayer::loadingDone(CCNode* pNode)
{
	CCScene* pScene = GameScene::create();
	CCTransitionMoveInB* animateScene = CCTransitionMoveInB::create(0.5,pScene);
	CCDirector::sharedDirector()->replaceScene(animateScene);
}

void WelcomeLayer::keyBackClicked()
{
	CCDirector::sharedDirector()->end();
}

bool WelcomeLayer::isHaveSaveFile()
{
	if (!CCUserDefault::sharedUserDefault()->getBoolForKey("isHaveSaveFileXml"))
	{
		CCUserDefault::sharedUserDefault()->setBoolForKey("isHaveSaveFileXml",true);
		CCUserDefault::sharedUserDefault()->setIntegerForKey("HighestScore",0);
		CCUserDefault::sharedUserDefault()->flush();
		return false;
	}
	else
	{
		return true;
	}
}

void WelcomeLayer::getHighestHistoryScore()
{
	if (isHaveSaveFile())
	{
		GameOverLayer::highestHistoryScore = CCUserDefault::sharedUserDefault()->getIntegerForKey("HighestScore",0);
	}
}