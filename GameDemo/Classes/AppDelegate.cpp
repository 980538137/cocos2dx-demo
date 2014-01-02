#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "Hello.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

	
	//是否开始自适屏
	//kResolutionExactFit        //自动缩放宽高全部显示（会变形）
	//kResolutionNoBorder     //不留黑边全屏展示（不变形，但是长的那边会被裁减）
	//kResolutionShowAll        //全部展示不裁剪（可能会留黑边）
	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(800, 480, kResolutionNoBorder);
	
    // turn on display FPS
    pDirector->setDisplayStats(true);


    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene = Hello::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();

    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
