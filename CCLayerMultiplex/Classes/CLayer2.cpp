#include "CLayer2.h"


CCLayer2::CCLayer2(void)
{
}


CCLayer2::~CCLayer2(void)
{
}

bool CCLayer2::init()
{
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

		CCLabelTTF* pLabel = CCLabelTTF::create("Hello Layer2", "Arial", 30);

		// position the label on the center of the screen
		pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
			origin.y + visibleSize.height - pLabel->getContentSize().height));

		// add the label as a child to this layer
		this->addChild(pLabel, 1);

		// add "HelloWorld" splash screen"
		CCSprite* pSprite = CCSprite::create("HelloWorld.png");
		pSprite->setScale(0.8);

		// position the sprite on the center of the screen
		pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

		// add the sprite as a child to this layer
		this->addChild(pSprite, 0);
		bRet=true;
	} while (0);
	return bRet;
}
