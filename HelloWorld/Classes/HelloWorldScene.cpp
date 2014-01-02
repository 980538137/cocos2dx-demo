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
	this->scheduleUpdate();
	this->setTouchEnabled(true);
	x = 1;
	y = 1;
	x1 = -1;
	y1 = -1;
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();


	_bullets = new CCArray;
	_ducks = new CCArray;
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
	CCSprite* pSprite = CCSprite::create("background800sky.png");

	// position the sprite on the center of the screen
	//pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	pSprite->setAnchorPoint(ccp(0,0));
	pSprite->setPosition(ccp(0,visibleSize.height - pSprite->getContentSize().height));

	// add the sprite as a child to this layer
	this->addChild(pSprite, 0);

	CCSprite* pHillSprite = CCSprite::create("background800hills.png");
	pHillSprite->setAnchorPoint(ccp(0,0));
	pHillSprite->setPosition(ccp(0,0));
	this->addChild(pHillSprite,0);

	CCSprite* pGrassSprite = CCSprite::create("background800grass.png");
	pGrassSprite->setAnchorPoint(ccp(0,0));
	pGrassSprite->setPosition(ccp(0,0));
	this->addChild(pGrassSprite,0);
	//云彩的移动效果
	pLargeCloudSprite = CCSprite::create("largecloud.png");
	pLargeCloudSprite->setAnchorPoint(ccp(0,0));
	pLargeCloudSprite->setPosition(ccp(-pLargeCloudSprite->getContentSize().width,visibleSize.height - pLargeCloudSprite->getContentSize().height - 50));
	CCActionInterval* actionTo = CCMoveTo::create(18,ccp(visibleSize.width,visibleSize.height - pLargeCloudSprite->getContentSize().height - 50));
	CCSequence* cloudAction = CCSequence::create(actionTo,CCCallFunc::create(this,callfunc_selector(HelloWorld::cloudCallback1)),NULL);
	pLargeCloudSprite->runAction(cloudAction);
	this->addChild(pLargeCloudSprite,0);

	pMediumCloudSprite = CCSprite::create("mediumcloud.png");
	pMediumCloudSprite->setAnchorPoint(ccp(0,0));
	pMediumCloudSprite->setPosition(ccp(-pMediumCloudSprite->getContentSize().width,visibleSize.height - pMediumCloudSprite->getContentSize().height-20));
	CCActionInterval* actionTo2 = CCMoveTo::create(24,ccp(visibleSize.width,visibleSize.height - pMediumCloudSprite->getContentSize().height-20));
	CCSequence* cloudAction2 = CCSequence::create(actionTo2,CCCallFunc::create(this,callfunc_selector(HelloWorld::cloudCallback2)),NULL);
	pMediumCloudSprite->runAction(cloudAction2);
	this->addChild(pMediumCloudSprite,0);

	pSmallCloudSprite = CCSprite::create("smallcloud.png");
	pSmallCloudSprite->setAnchorPoint(ccp(0,0));
	pSmallCloudSprite->setPosition(ccp(pSmallCloudSprite->getContentSize().width,visibleSize.height-pSmallCloudSprite->getContentSize().height - 45));
	CCActionInterval* actionTo3 = CCMoveTo::create(36,ccp(visibleSize.width,visibleSize.height - pSmallCloudSprite->getContentSize().height - 45));
	CCSequence* cloudAction3 = CCSequence::create(actionTo3,CCCallFunc::create(this,callfunc_selector(HelloWorld::cloudCallback3)),NULL);
	pSmallCloudSprite->runAction(cloudAction3);
	this->addChild(pSmallCloudSprite,0);


	CCArray* animFrames = getDuckAnimations();
	duckSprite = CCSprite::createWithSpriteFrame((CCSpriteFrame*)animFrames->objectAtIndex(0));
	duckSprite->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
	addChild(duckSprite);
	duckSprite2 = CCSprite::createWithSpriteFrame((CCSpriteFrame*)animFrames->objectAtIndex(0));
	duckSprite2->setPosition(ccp(30,30));
	duckSprite2->setFlipX(true);
	addChild(duckSprite2);

	_ducks->addObject(duckSprite);
	_ducks->addObject(duckSprite2);

	CCActionInterval* duckAction1 = CCMoveTo::create(24,ccp(visibleSize.width,visibleSize.height - pMediumCloudSprite->getContentSize().height-20));
	CCSequence* duckAction = CCSequence::create(duckAction1,CCCallFunc::create(this,callfunc_selector(HelloWorld::cloudCallback2)),NULL);
	CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames,0.2f);
	CCAnimate* animate = CCAnimate::create(animation);
	duckSprite->runAction(CCRepeatForever::create(animate));
	duckSprite->runAction(duckAction);
	CCAnimation* animation2 = CCAnimation::createWithSpriteFrames(animFrames,0.2f);
	CCAnimate* animate2 = CCAnimate::create(animation2);
	duckSprite2->runAction(CCRepeatForever::create(animate2));

	/*CCActionInterval* moveTo = CCMoveTo::create(2,ccp(visibleSize.width/2 + 100,visibleSize.height/2 + 100));
	CCSequence* action1 = CCSequence::create(moveTo,
	CCCallFuncN::create(this,callfuncN_selector(HelloWorld::callback2)),NULL);
	CCActionInterval* moveTo2 = CCMoveTo::create(2,ccp(visibleSize.width/2,visibleSize.height/2));
	CCSequence* action2 = CCSequence::create(moveTo2,
	CCCallFuncN::create(this,callfuncN_selector(HelloWorld::callback3)),NULL);*/


	//duckSprite->runAction(CCRepeatForever::create(CCSequence::create(action1,action2,NULL)));

	CCLabelTTF* label = CCLabelTTF::create("Score:","fonts/Abberancy.ttf",35);
	ccColor3B color = ccc3(0, 0, 0);
	label->setColor(color);
	label->setAnchorPoint(ccp(0,0));
	label->setPosition(ccp(origin.x + 10,visibleSize.height-label->getContentSize().height));

	this->addChild(label,1,6);


	return true;
}

void HelloWorld::ccTouchesEnded(CCSet* touches,CCEvent* event)
{
	CCTouch* touch = (CCTouch*)(touches->anyObject());
	CCPoint location =  touch->getLocation();
	CCLog("++++++++++after   x:%f,   y:%f",location.x,location.y);

	CCSprite* bullet = CCSprite::create("shot800.png");
	bullet->setPosition(ccp(location.x,location.y));
	this->addChild(bullet);
	_bullets->addObject(bullet);
}

CCArray* HelloWorld::getDuckAnimations()
{
	CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("duckallframes800.png");
	CCSpriteFrame* frame0 = CCSpriteFrame::createWithTexture(texture,CCRect(80*0,64*0,80,64));
	CCSpriteFrame* frame1 = CCSpriteFrame::createWithTexture(texture,CCRect(80*1,64*0,80,64));
	CCSpriteFrame* frame2 = CCSpriteFrame::createWithTexture(texture,CCRect(80*2,64*0,80,64));
	CCSpriteFrame* frame3 = CCSpriteFrame::createWithTexture(texture,CCRect(80*3,64*0,80,64));
	CCSpriteFrame* frame4 = CCSpriteFrame::createWithTexture(texture,CCRect(80*0,64*1,80,64));
	CCSpriteFrame* frame5 = CCSpriteFrame::createWithTexture(texture,CCRect(80*1,64*1,80,64));
	CCSpriteFrame* frame6 = CCSpriteFrame::createWithTexture(texture,CCRect(80*2,64*1,80,64));
	CCSpriteFrame* frame7 = CCSpriteFrame::createWithTexture(texture,CCRect(80*3,64*1,80,64));
	CCSpriteFrame* frame8 = CCSpriteFrame::createWithTexture(texture,CCRect(80*0,64*2,80,64));
	CCSpriteFrame* frame9 = CCSpriteFrame::createWithTexture(texture,CCRect(80*1,64*2,80,64));
	CCSpriteFrame* frame10 = CCSpriteFrame::createWithTexture(texture,CCRect(80*2,64*2,80,64));
	CCSpriteFrame* frame11 = CCSpriteFrame::createWithTexture(texture,CCRect(80*3,64*2,80,64));

	CCArray* animFrames = new CCArray(12);
	animFrames->addObject(frame0);
	animFrames->addObject(frame1);
	animFrames->addObject(frame2);
	animFrames->addObject(frame3);
	animFrames->addObject(frame4);
	animFrames->addObject(frame5);
	animFrames->addObject(frame6);
	animFrames->addObject(frame7);
	animFrames->addObject(frame8);
	animFrames->addObject(frame9);
	animFrames->addObject(frame10);
	animFrames->addObject(frame11);
	return animFrames;
}

void HelloWorld::update(float tmd)
{
	/*CCLabelTTF * label = (CCLabelTTF*)this->getChildByTag(6);
	char str[10];
	sprintf(str,"%f",tmd);
	label->setString(str);*/
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	/*char p[10] ;
	itoa(visibleSize.width, p, 10); 
	CCLog(p);*/
	/*if(x == 1 && y == 1)
	{
		duckSprite->setPosition(ccp(duckSprite->getPositionX() + 1,duckSprite->getPositionY() + 1));
	}
	else if(x == -1 && y == 1)
	{
		duckSprite->setPosition(ccp(duckSprite->getPositionX() - 1,duckSprite->getPositionY() + 1));
	}
	else if(x == 1 && y == -1)
	{
		duckSprite->setPosition(ccp(duckSprite->getPositionX() + 1,duckSprite->getPositionY() - 1));
	}
	else if(x == -1 && y == -1)
	{
		duckSprite->setPosition(ccp(duckSprite->getPositionX() - 1,duckSprite->getPositionY() - 1));
	}
	if(duckSprite->getPositionX() < 0)
	{
		x = 1;
		duckSprite->setFlipX(false);
	}
	if(duckSprite->getPositionX() > visibleSize.width)
	{
		x = -1;
		duckSprite->setFlipX(true);
	}
	if(duckSprite->getPositionY() < 0)
	{
		y = 1;
	}
	if(duckSprite->getPositionY() > visibleSize.height)
	{
		y = -1;
	}

	if(x1 == 1 && y1 == 1)
	{
		duckSprite2->setPosition(ccp(duckSprite2->getPositionX() + 1,duckSprite2->getPositionY() + 1));
	}
	else if(x1 == -1 && y1 == 1)
	{
		duckSprite2->setPosition(ccp(duckSprite2->getPositionX() - 1,duckSprite2->getPositionY() + 1));
	}
	else if(x1 == 1 && y1 == -1)
	{
		duckSprite2->setPosition(ccp(duckSprite2->getPositionX() + 1,duckSprite2->getPositionY() - 1));
	}
	else if(x1 == -1 && y1 == -1)
	{
		duckSprite2->setPosition(ccp(duckSprite2->getPositionX() - 1,duckSprite2->getPositionY() - 1));
	}
	if(duckSprite2->getPositionX() < 0)
	{
		x1 = 1;
		duckSprite2->setFlipX(false);
	}
	if(duckSprite2->getPositionX() > visibleSize.width)
	{
		x1 = -1;
		duckSprite2->setFlipX(true);
	}
	if(duckSprite2->getPositionY() < 0)
	{
		y1 = 1;
	}
	if(duckSprite2->getPositionY() > visibleSize.height)
	{
		y1 = -1;
	}*/

	
	CCArray* bulletsToDelete = new CCArray;
	CCObject* it = NULL;
	CCObject* jt = NULL;
	CCARRAY_FOREACH(_bullets,it)
	{
		CCSprite* bullet = dynamic_cast<CCSprite*>(it);
		CCRect bulletRect = CCRectMake(bullet->getPosition().x - (bullet->getContentSize().width/2),bullet->getPosition().y-(bullet->getContentSize().height/2),bullet->getContentSize().width,bullet->getContentSize().height);
		
		CCArray* ducksToDelete = new CCArray;
		CCARRAY_FOREACH(_ducks,jt)
		{
			CCSprite* duck = dynamic_cast<CCSprite*>(jt);
			CCRect duckRect = CCRectMake(duck->getPosition().x - (duck->getContentSize().width/2),duck->getPosition().y - (duck->getContentSize().height/2),duck->getContentSize().width,duck->getContentSize().height);
			if(bulletRect.intersectsRect(duckRect))
			{
				ducksToDelete->addObject(duck);
			}
		}


		CCARRAY_FOREACH(ducksToDelete,jt)
		{
			CCSprite* duck = dynamic_cast<CCSprite*>(jt);
			_ducks->removeObject(duck);
			this->removeChild(duck,true);
		}
		/*if(ducksToDelete->count() > 0)
		{*/
			bulletsToDelete->addObject(bullet);
		//}
		ducksToDelete->release();
	}

	CCARRAY_FOREACH(bulletsToDelete,it)
	{
		CCSprite* bullet = dynamic_cast<CCSprite*>(it);
		_bullets->removeObject(bullet);
		this->removeChild(bullet,true);
	}
	bulletsToDelete->release();
}



void HelloWorld::cloudCallback1()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	pLargeCloudSprite->setPosition(ccp(-pLargeCloudSprite->getContentSize().width,visibleSize.height - pLargeCloudSprite->getContentSize().height - 50));

	CCActionInterval* actionTo = CCMoveTo::create(18,ccp(visibleSize.width,visibleSize.height - pLargeCloudSprite->getContentSize().height-50));
	CCSequence* cloudAction = CCSequence::create(actionTo,CCCallFunc::create(this,callfunc_selector(HelloWorld::cloudCallback1)),NULL);
	pLargeCloudSprite->runAction(cloudAction);
}
void HelloWorld::cloudCallback2()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	pMediumCloudSprite->setPosition(ccp(-pMediumCloudSprite->getContentSize().width,visibleSize.height - pMediumCloudSprite->getContentSize().height-20));
	CCActionInterval* actionTo2 = CCMoveTo::create(24,ccp(visibleSize.width,visibleSize.height - pMediumCloudSprite->getContentSize().height-20));
	CCSequence* cloudAction2 = CCSequence::create(actionTo2,CCCallFunc::create(this,callfunc_selector(HelloWorld::cloudCallback2)),NULL);
	pMediumCloudSprite->runAction(cloudAction2);
}

void HelloWorld::cloudCallback3()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	pSmallCloudSprite->setPosition(ccp(pSmallCloudSprite->getContentSize().width,visibleSize.height-pSmallCloudSprite->getContentSize().height - 45));
	CCActionInterval* actionTo3 = CCMoveTo::create(36,ccp(visibleSize.width,visibleSize.height - pSmallCloudSprite->getContentSize().height - 45));
	CCSequence* cloudAction3 = CCSequence::create(actionTo3,CCCallFunc::create(this,callfunc_selector(HelloWorld::cloudCallback3)),NULL);
	pSmallCloudSprite->runAction(cloudAction3);
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
