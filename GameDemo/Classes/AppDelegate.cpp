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

	
	//�Ƿ�ʼ������
	//kResolutionExactFit        //�Զ����ſ��ȫ����ʾ������Σ�
	//kResolutionNoBorder     //�����ڱ�ȫ��չʾ�������Σ����ǳ����Ǳ߻ᱻ�ü���
	//kResolutionShowAll        //ȫ��չʾ���ü������ܻ����ڱߣ�
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
