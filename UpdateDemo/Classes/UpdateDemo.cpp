#include "UpdateDemo.h"

using namespace cocos2d;


CCScene* UpdateDemo::scene()
{
	CCScene * scene = NULL;
	do 
	{
		scene = CCScene::create();
		CC_BREAK_IF(! scene);
		UpdateDemo *layer = UpdateDemo::create();
		CC_BREAK_IF(! layer);
		scene->addChild(layer);
	} while (0);
	return scene;
}


bool UpdateDemo::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCLayer::init());
		CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
			"CloseNormal.png",
			"CloseSelected.png",
			this,
			menu_selector(UpdateDemo::menuCloseCallback));
		CC_BREAK_IF(! pCloseItem);

		pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));
		CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
		pMenu->setPosition(CCPointZero);
		CC_BREAK_IF(! pMenu);
		this->addChild(pMenu, 1);


		CCSize mysize=CCDirector::sharedDirector()->getWinSize();
		CCSprite * sp1=CCSprite::create("CloseNormal.png");
		sp1->setPosition(ccp(0,mysize.height-50));
		this->addChild(sp1,0,521);
		CCSprite * sp2=CCSprite::create("CloseNormal.png");
		sp2->setPosition(ccp(0,mysize.height-150));
		this->addChild(sp2,0,522);
		CCSprite * sp3=CCSprite::create("CloseNormal.png");
		sp3->setPosition(ccp(0,mysize.height-250));
		this->addChild(sp3,0,523);
		a=1;
		b=1;
		c=1;
		x = 1;
		y = 1;
		scheduleUpdate();
		schedule(schedule_selector(UpdateDemo::myupdate),1.0f);
		scheduleOnce(schedule_selector(UpdateDemo::myupdate2),3.0f);



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

		CCSprite* sprite = CCSprite::createWithSpriteFrame(frame0);
		sprite->setPosition(ccp(mysize.width/2,mysize.height/2));
		addChild(sprite);

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

		CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames,0.2f);
		CCAnimate* animate = CCAnimate::create(animation);

		CCSprite* duckSprite = CCSprite::createWithSpriteFrame(frame0);
		duckSprite->setPosition(ccp(mysize.width/2,mysize.height/2));
		addChild(duckSprite,0,524);
		duckSprite->runAction(CCRepeatForever::create(animate));
		bRet = true;
	} while (0);

	return bRet;
}


void UpdateDemo::update(float tmd){
	CCSprite * sp=(CCSprite*)this->getChildByTag(524);
	//if(a==1){
	//	//sp->setPositionX(sp->getPositionX()+1);
	//	sp->setPosition(ccp(sp->getPositionX()+ 1,sp->getPositionY() + 1));
	//}else{
	//	//sp->setPositionX(sp->getPositionX()-1);
	//	sp->setPosition(ccp(sp->getPositionX() - 1,sp->getPositionY() - 1));
	//}
	//if(sp->getPositionX()<0){
	//	a=1;
	//}
	//if(sp->getPositionX()>800){
	//	a=-1;
	//}
	if(x == 1 && y == 1)
	{
		sp->setPosition(ccp(sp->getPositionX() + 1,sp->getPositionY() + 1));
	}
	else if(x == -1 && y == 1)
	{
		sp->setPosition(ccp(sp->getPositionX() - 1,sp->getPositionY() + 1));
	}
	else if(x == 1 && y == -1)
	{
		sp->setPosition(ccp(sp->getPositionX() + 1,sp->getPositionY() - 1));
	}
	else if(x == -1 && y == -1)
	{
		sp->setPosition(ccp(sp->getPositionX() - 1,sp->getPositionY() - 1));
	}
	if(sp->getPositionX() < 0)
	{
		x = 1;
		sp->setFlipX(false);
	}
	if(sp->getPositionX() > 600)
	{
		x = -1;
		sp->setFlipX(true);
	}
	if(sp->getPositionY() < 0)
	{
		y = 1;
	}
	if(sp->getPositionY() > 450)
	{
		y = -1;
	}
}

void UpdateDemo::myupdate(float tmd){
	CCSprite * sp=(CCSprite*)this->getChildByTag(522);
	if(b==1){
		sp->setPositionX(sp->getPositionX()+10);
	}else{
		sp->setPositionX(sp->getPositionX()-10);
	}
	if(sp->getPositionX()<0){
		b=1;
	}
	if(sp->getPositionX()>480){
		b=-1;
	}
}

void UpdateDemo::myupdate2(float tmd){
	CCSprite * sp=(CCSprite*)this->getChildByTag(523);
	if(c==1){
		sp->setPositionX(sp->getPositionX()+100);
	}else{
		sp->setPositionX(sp->getPositionX()-100);
	}
	if(sp->getPositionX()<0){
		c=1;
	}
	if(sp->getPositionX()>480){
		c=-1;
	}
}


void UpdateDemo::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();
}