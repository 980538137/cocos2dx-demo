#include "CLayer3.h"


CCLayer3::CCLayer3(void)
{
}


CCLayer3::~CCLayer3(void)
{
}

bool CCLayer3::init()
{
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

		CCLabelTTF* pLabel = CCLabelTTF::create("Hello Layer3", "Arial", 30);

		// position the label on the center of the screen
		pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
			origin.y + visibleSize.height - pLabel->getContentSize().height));

		// add the label as a child to this layer
		this->addChild(pLabel, 1);

		// add "HelloWorld" splash screen"
		CCSprite* pSprite = CCSprite::create("HelloWorld.png");

		// position the sprite on the center of the screen
		pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

		// add the sprite as a child to this layer
		this->addChild(pSprite, 0);
		bRet=true;
	} while (0);
	return bRet;
}