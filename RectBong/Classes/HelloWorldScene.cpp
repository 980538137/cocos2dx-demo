#include "HelloWorldScene.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
	scheduleUpdate();

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
    
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

	CCSprite* sp1 = CCSprite::create("a.png");
	sp1->setPosition(ccp(100,visibleSize.height/2));
	this->addChild(sp1,1,1);

	CCSprite* sp2 = CCSprite::create("b.png");
	sp2->setPosition(ccp(visibleSize.width - 100,visibleSize.height/2));
	this->addChild(sp2,1,2);

	CCLabelTTF* ttf = CCLabelTTF::create("none","Arial",20);
	ttf->setPosition(ccp(visibleSize.width/2,visibleSize.height - 50));
	this->addChild(ttf,1,3);

	sp1->runAction(CCMoveTo::create(5,ccp(visibleSize.width - 140,visibleSize.height/2)));
    
    return true;
}

void HelloWorld::update(float tmd)
{
	CCLOG("Update");
	CCSprite* sp1 = (CCSprite*)this->getChildByTag(1);
	CCSprite* sp2 = (CCSprite*)this->getChildByTag(2);
	CCLabelTTF* ttf = (CCLabelTTF*)this->getChildByTag(3);
	if(isbong(sp1->getPosition(),20,sp2->getPosition(),20)){
		ttf->setString("bong!!!");
	}else{
		ttf->setString("none");
	}
}

bool HelloWorld::isbong(CCPoint p1,float r1,CCPoint p2,float r2)
{
	if(sqrt(pow(p1.x - p2.x,2) + pow(p1.y-p2.y,2)) > (r1 + r2))
	{
		return false;
	}else{
		return true;
	}
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
