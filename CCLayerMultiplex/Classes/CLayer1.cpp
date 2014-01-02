#include "CLayer1.h"


CCLayer1::CCLayer1(void)
{
}


CCLayer1::~CCLayer1(void)
{
}

bool CCLayer1::init()
{
	bool bRet = false;
	do
	{

		CC_BREAK_IF(!CCLayer1::init());

		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

		CCLabelTTF* pLabel = CCLabelTTF::create("Hello Layer1","Arial",30);
		pLabel->setPosition(ccp(origin.x + visibleSize.width/2,origin.y + visibleSize.height - pLabel->getContentSize().height));
		this->addChild(pLabel,1);

		CCSprite* pSprite = CCSprite::create("HelloWorld.png");
		pSprite->setScale(0.5);
		pSprite->setPosition(ccp(origin.x + visibleSize.width/2,origin.y+visibleSize.height/2));
		this->addChild(pSprite,0);
		bRet = true;
	} while (0);
	return bRet;
}
