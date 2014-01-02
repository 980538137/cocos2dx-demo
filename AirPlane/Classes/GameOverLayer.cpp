#include "GameOverLayer.h"
#include "GameLayer.h"
USING_NS_CC;

int GameOverLayer::highestHistoryScore = 0;

GameOverLayer::GameOverLayer(void)
{
	score = 0;
	highestScore = NULL;
}

GameOverLayer::~GameOverLayer(void)
{

}

GameOverLayer* GameOverLayer::create(int passScore)
{
	GameOverLayer* pRet = new GameOverLayer();
	pRet->score = passScore;
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

bool GameOverLayer::init()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCSprite* backGround = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("gameover.png"));
	backGround->setPosition(ccp(winSize.width/2,winSize.height/2));
	this->addChild(backGround);

	CCSprite* normalBackToGame = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("btn_finish.png"));
	CCSprite* pressedBackToGame = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("btn_finish.png"));
	CCMenuItemImage* pBackItem = CCMenuItemImage::create();
	pBackItem->initWithNormalSprite(normalBackToGame,pressedBackToGame,NULL,this,menu_selector(GameOverLayer::menuBackCallback));
	pBackItem->setPosition(ccp(winSize.width - normalBackToGame->getContentSize().width/2 - 10,normalBackToGame->getContentSize().height/2 + 10));
	CCMenu* menuBack = CCMenu::create(pBackItem,NULL);
	menuBack->setPosition(CCPointZero);
	this->addChild(menuBack);

	/*CCString* strScore = CCString::createWithFormat("%d",score);
	const char *str = strScore->m_sString.c_str();
	CCLabelTTF* label = CCLabelTTF::create(str,"Arial",24);
	label->setPosition(ccp(winSize.width/2,winSize.height/2));
	this->addChild(label);*/

	CCString* strScore = CCString::createWithFormat("%d",score);
	CCLabelBMFont* finalScore = CCLabelBMFont::create(strScore->m_sString.c_str(),"fonts/font.fnt");
	finalScore->setPosition(ccp(winSize.width/2,winSize.height/2));
	finalScore->setColor(ccc3(143,146,147));
	this->addChild(finalScore);

	CCDelayTime* delay = CCDelayTime::create(1.0f);
	CCScaleTo* scaleBig = CCScaleTo::create(1.0f,3.0f);
	CCScaleTo* scaleLittle = CCScaleTo::create(0.3f,2.0f);
	CCFiniteTimeAction* sequence = CCSequence::create(delay,scaleBig,scaleLittle,NULL);
	finalScore->runAction(sequence);

	CCString* strHighestScore = CCString::createWithFormat("%d",highestHistoryScore);
	highestScore = CCLabelBMFont::create(strHighestScore->m_sString.c_str(),"fonts/font.fnt");
	highestScore->setPosition(ccp(140,winSize.height - 30));;
	highestScore->setColor(ccc3(143,146,147));
	highestScore->setAnchorPoint(ccp(0,0.5));
	this->addChild(highestScore);

	if (score > highestHistoryScore)
	{
		CCUserDefault::sharedUserDefault()->setIntegerForKey("HighestScore",score);
		CCUserDefault::sharedUserDefault()->flush();

		highestHistoryScore = score;
		CCDelayTime* delayChange  =CCDelayTime::create(1.3f);
		CCMoveBy* moveOut = CCMoveBy::create(0.1f,ccp(0,100));
		CCCallFuncN* beginChange = CCCallFuncN::create(this,callfuncN_selector(GameOverLayer::beginChaneHighestScore));
		CCMoveBy* moveIn = CCMoveBy::create(0.1f,ccp(0,-100));
		CCFiniteTimeAction* sequence = CCSequence::create(delayChange,moveOut,beginChange,moveIn,NULL);
		highestScore->runAction(sequence);
	}
	this->setKeypadEnabled(true);

	return true;
}

void GameOverLayer::menuBackCallback(CCObject* pSender)
{
	CCLOG("restart");

	CCScene* pScene = GameLayer::scene();
	CCTransitionMoveInL* animateScene =   CCTransitionMoveInL::create(0.8f,pScene);
	CCDirector::sharedDirector()->replaceScene(animateScene);
}

void GameOverLayer::beginChaneHighestScore(CCNode* pNode)
{
	CCString* changeScore = CCString::createWithFormat("%d",score);
	highestScore->setString(changeScore->m_sString.c_str());
}

void GameOverLayer::keyBackClicked()
{
	CCDirector::sharedDirector()->end();
}