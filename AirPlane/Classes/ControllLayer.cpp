#include "ControllLayer.h"

ControllLayer::ControllLayer(void)
{
	scoreItem = NULL;
	pPauseItem = NULL;
}

ControllLayer::~ControllLayer(void)
{

}

ControllLayer* ControllLayer::create()
{
	ControllLayer* pRet = new ControllLayer();
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

bool ControllLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		
		CCSprite* normalPause = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_pause_nor.png"));
		CCSprite* pressedPause = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_pause_press.png"));
		pPauseItem = CCMenuItemImage::create();
		pPauseItem->initWithNormalSprite(normalPause,pressedPause,NULL,this,menu_selector(ControllLayer::menuPauseCallback));
		pPauseItem->setPosition(ccp(pPauseItem->getContentSize().width/2 + 10,winSize.height - pPauseItem->getContentSize().height/2 - 10));
		CCMenu *menuPause = CCMenu::create(pPauseItem,NULL);
		menuPause->setPosition(CCPointZero);
		this->addChild(menuPause,101);
		
		scoreItem = CCLabelBMFont::create("0","fonts/font.fnt");
		scoreItem->setColor(ccc3(143,146,147));
		scoreItem->setAnchorPoint(ccp(0,0.5));
		scoreItem->setPosition(ccp(pPauseItem->getPositionX() + pPauseItem->getContentSize().width/2 + 5,pPauseItem->getPositionY()));
		this->addChild(scoreItem);

		bRet = true;
	} while (0);
	return bRet;
}

void ControllLayer::menuPauseCallback(CCObject* pSender)
{
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/button.mp3");
	if (!CCDirector::sharedDirector()->isPaused())
	{
		pPauseItem->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_resume_nor.png"));
		pPauseItem->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_resume_pressed.png"));
		/*CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();*/
		CCDirector::sharedDirector()->pause();
		noTouchLayer = NoTouchLayer::create();
		this->addChild(noTouchLayer);
	}
	else
	{
		pPauseItem->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_resume_nor.png"));
		pPauseItem->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_resume_pressed.png"));
		//CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		CCDirector::sharedDirector()->resume();
		this->removeChild(noTouchLayer,true);
	}
}

void ControllLayer::updateScore(int score)
{
	if (score >= 0 && score <= MAX_SCORE)
	{
		CCString *strScore = CCString::createWithFormat("%d",score);
		scoreItem->setString(strScore->m_sString.c_str());
	}
}