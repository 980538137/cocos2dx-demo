//------------------------------
//项目名称：打地鼠
//------------------------------
//功能模块：欢迎界面
//作	者：孤狼
//最后修改时间：2013/07/30
//http://gl.paea.cn
//------------------------------
#include "Hello.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "Menu.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;
CCScene* Hello::scene()
{
    CCScene * scene = NULL;
    do 
    {
        scene = CCScene::create();
        CC_BREAK_IF(! scene);
        Hello *layer = Hello::create();
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
bool Hello::init()
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(! CCLayer::init());
		//-new-//
		CCSize mysize=CCDirector::sharedDirector()->getVisibleSize();
		//创建logo
        CCSprite* plogo = CCSprite::create("logo.png");
        plogo->setPosition(ccp(mysize.width/2, mysize.height/2));
        this->addChild(plogo, 0);
		//播放音乐
		#define MUSIC_FILE	"music/logo.mp3"
		SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(MUSIC_FILE);
		SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1);
//		SimpleAudioEngine::sharedEngine()->playBackgroundMusic(MUSIC_FILE,false);
		//创建显示动画
		CCActionInterval * ain=CCFadeIn::create(0.5f);
		CCActionInterval * aout=CCFadeOut::create(0.5f);
		CCActionInterval * at=CCDelayTime::create(1);
		CCFiniteTimeAction * ac=CCSequence::create(ain,at,aout,CCCallFunc::create(this,callfunc_selector(Hello::trunscene)),NULL);
		plogo->runAction(ac);
		//-new-//
        bRet = true;
    } while (0);
    return bRet;
}

//------------------------------
//函数名称：trunscene
//函数作用：切换场景
//------------------------------
//最后修改时间：2013/08/14
//------------------------------
void Hello::trunscene(){
	CCScene * menuscene=Menu::scene();
	CCTransitionScene * tt=CCTransitionCrossFade::create(0.1f,menuscene);
	CCDirector::sharedDirector()->replaceScene(tt);
}


//------------------------------
//函数名称：onEnter\onEnterTransitionDidFinish\onExit
//函数作用：生命周期函数
//------------------------------
//最后修改时间：2013/08/14
//------------------------------
void Hello::onEnter(){
	CCLayer::onEnter();
	
}
void Hello::onEnterTransitionDidFinish(){
	CCLayer::onEnterTransitionDidFinish();
}
void Hello::onExit(){
	CCLayer::onExit();
	this->removeAllChildrenWithCleanup(true);
}

