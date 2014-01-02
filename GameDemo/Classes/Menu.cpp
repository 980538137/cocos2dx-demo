//------------------------------
//项目名称：打地鼠
//------------------------------
//功能模块：菜单界面
//作	者：孤狼
//最后修改时间：2013/07/30
//http://gl.paea.cn
//------------------------------
#include "Menu.h"
#include "Game.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;
CCScene* Menu::scene()
{
    CCScene * scene = NULL;
    do 
    {
        scene = CCScene::create();
        CC_BREAK_IF(! scene);
        Menu *layer = Menu::create();
        CC_BREAK_IF(! layer);
        scene->addChild(layer);
    } while (0);
    return scene;
}

//------------------------------
//函数名称：init
//函数作用：初始化
//------------------------------
//最后修改时间：2013/08/14
//------------------------------
bool Menu::init()
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(! CCLayer::init());
		//-new-//
		CCSize mysize=CCDirector::sharedDirector()->getVisibleSize();
		CCPoint yuansize=CCDirector::sharedDirector()->getVisibleOrigin();
		//播放音乐
		#define MUSIC_FILE	"music/bg.mp3"
		SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(MUSIC_FILE);
		SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1);
//		SimpleAudioEngine::sharedEngine()->playBackgroundMusic(MUSIC_FILE,true);
		//设置背景
		CCSprite* spbg = CCSprite::create("bj.png");
        spbg->setPosition(ccp(mysize.width/2, mysize.height/2));
        this->addChild(spbg, 0);
		//草
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("c.plist");
		CCSprite * spc1=CCSprite::createWithSpriteFrameName("c1.png");
		CCSprite * spc2=CCSprite::createWithSpriteFrameName("c2.png");
		CCSprite * spc3=CCSprite::createWithSpriteFrameName("c3.png");
		spc1->setPosition(ccp(mysize.width/2-150,yuansize.y+40));
		spc2->setPosition(ccp(mysize.width/2+100,yuansize.y+40));
		spc3->setPosition(ccp(mysize.width/2+300,yuansize.y+40));
		this->addChild(spc1,100);
		this->addChild(spc2,101);
		this->addChild(spc3,100);
		//老鼠
		CCSprite *spls1=CCSprite::create("ls1.png");
		CCSprite *spls2=CCSprite::create("ls2.png");
		spls1->setPosition(ccp(yuansize.x+100,-100));
		spls2->setPosition(ccp(mysize.width/2+100,-100));
		spls1->setScale(0.5);
		spls2->setScale(0.5);
		this->addChild(spls1,1);
		this->addChild(spls2,1);
		CCActionInterval * aclsup1=CCMoveTo::create(3.0f,ccp(yuansize.x+100,100));
		CCActionInterval * aclsup2=CCMoveTo::create(5.0f,ccp(mysize.width/2+100,100));
		CCActionInterval * aclsup3=CCMoveTo::create(3.0f,ccp(mysize.width/2+200,100));
		CCActionInterval * aclsup4=CCMoveTo::create(2.0f,ccp(mysize.width/2-200,100));
		CCActionInterval * aclsdown1=CCMoveTo::create(3.0f,ccp(yuansize.x+100,-100));
		CCActionInterval * aclsdown2=CCMoveTo::create(4.0f,ccp(mysize.width/2+100,-100));
		CCActionInterval * aclsdown3=CCMoveTo::create(1.0f,ccp(mysize.width/2+200,-100));
		CCActionInterval * aclsdown4=CCMoveTo::create(3.0f,ccp(mysize.width/2-200,-100));
		CCActionInterval * deng=CCDelayTime::create(3);
		CCFiniteTimeAction * acls1=CCSequence::create(aclsup4,deng,aclsdown4,deng,aclsup1,deng,aclsdown2,deng,aclsup2,deng,aclsdown3,deng,aclsup3,deng,aclsdown1,NULL);
		CCFiniteTimeAction * acls2=CCSequence::create(aclsup1,deng,aclsdown1,deng,aclsup3,deng,aclsdown3,deng,aclsup4,deng,aclsdown1,deng,aclsup4,deng,aclsdown4,NULL);
		CCFiniteTimeAction * dols1=CCRepeat::create(acls1,20);
		CCFiniteTimeAction * dols2=CCRepeat::create(acls2,20);
		spls1->runAction(dols1);
		spls2->runAction(dols2);
		//云彩
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("yun.plist");
		CCSprite * spy1=CCSprite::createWithSpriteFrameName("y1.png");
		CCSprite * spy2=CCSprite::createWithSpriteFrameName("y2.png");
		CCSprite * spy3=CCSprite::createWithSpriteFrameName("y3.png");
		CCSprite * spy4=CCSprite::createWithSpriteFrameName("y4.png");
		spy1->setPosition(ccp(mysize.width/2-150,mysize.height-20));
		spy2->setPosition(ccp(mysize.width/2+150,mysize.height-30));
		spy3->setPosition(ccp(mysize.width/2,mysize.height-40));
		spy4->setPosition(ccp(mysize.width/2+200,mysize.height-50));
		spy1->setScale(0.5f);
		spy2->setScale(0.4f);
		spy3->setScale(0.6f);
		spy4->setScale(0.7f);
		this->addChild(spy1);
		this->addChild(spy2);
		this->addChild(spy3);
		this->addChild(spy4);
		CCActionInterval * acyunle1=CCMoveTo::create(33.0f,ccp(-200,mysize.height-20));
		CCActionInterval * acyunle2=CCMoveTo::create(36.0f,ccp(-200,mysize.height-50));
		CCActionInterval * acyunle3=CCMoveTo::create(21.0f,ccp(-200,mysize.height-30));
		CCActionInterval * acyunle4=CCMoveTo::create(12.0f,ccp(-200,mysize.height-40));
		CCActionInterval * acyunri1=CCMoveTo::create(29.0f,ccp(mysize.width+200,mysize.height-40));
		CCActionInterval * acyunri2=CCMoveTo::create(54.0f,ccp(mysize.width+200,mysize.height-50));
		CCActionInterval * acyunri3=CCMoveTo::create(15.0f,ccp(mysize.width+200,mysize.height-10));
		CCActionInterval * acyunri4=CCMoveTo::create(27.0f,ccp(mysize.width+200,mysize.height-20));
		CCFiniteTimeAction * acyun1=CCSequence::create(acyunle1,acyunri1,NULL);
		CCFiniteTimeAction * acyun2=CCSequence::create(acyunri2,acyunle2,NULL);
		CCFiniteTimeAction * acyun3=CCSequence::create(acyunle3,acyunri3,NULL);
		CCFiniteTimeAction * acyun4=CCSequence::create(acyunle4,acyunri4,NULL);
		CCFiniteTimeAction * doyun1=CCRepeat::create(acyun1,20);
		CCFiniteTimeAction * doyun2=CCRepeat::create(acyun2,20);
		CCFiniteTimeAction * doyun3=CCRepeat::create(acyun3,20);
		CCFiniteTimeAction * doyun4=CCRepeat::create(acyun4,20);
		spy1->runAction(doyun1);
		spy2->runAction(doyun2);
		spy3->runAction(doyun3);
		spy4->runAction(doyun4);
		//菜单
		CCMenuItemImage * button1 = CCMenuItemImage::create("b1.png","b1.png",this,menu_selector(Menu::rungame));
		CCMenuItemImage * button2 = CCMenuItemImage::create("b2.png","b2.png",this,menu_selector(Menu::menuCloseCallback));
		button1->setPosition(ccp(mysize.width/2,mysize.height/2+30));
		button2->setPosition(ccp(mysize.width/2,mysize.height/2-30));
        CCMenu* pMenu = CCMenu::create(button1,button2, NULL);
        pMenu->setPosition(CCPointZero);
        this->addChild(pMenu, 1);
		

		//-new-//
        bRet = true;
    } while (0);

    return bRet;
}

//------------------------------
//函数名称：rungame
//函数作用：运行游戏
//------------------------------
//最后修改时间：2013/08/14
//------------------------------
void Menu::rungame(CCObject* pSender){
	CCScene * gamescene=Game::scene();
	CCTransitionScene * tt=CCTransitionCrossFade::create(0.1f,gamescene);
	CCDirector::sharedDirector()->replaceScene(tt);
}

//------------------------------
//函数名称：menuCloseCallback
//函数作用：退出游戏
//------------------------------
//最后修改时间：2013/08/14
//------------------------------
void Menu::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
}

//------------------------------
//函数名称：onEnter\onEnterTransitionDidFinish\onExit
//函数作用：生命周期函数
//------------------------------
//最后修改时间：2013/08/14
//------------------------------
void Menu::onEnter(){
	CCLayer::onEnter();
}
void Menu::onEnterTransitionDidFinish(){
	CCLayer::onEnterTransitionDidFinish();
}
void Menu::onExit(){
	CCLayer::onExit();
}

