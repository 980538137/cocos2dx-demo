#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

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

	CCSprite* pSprite = CCSprite::create("HelloWorld.png");

	// position the sprite on the center of the screen
	pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(pSprite,0);


	CCTextFieldTTF *textField = CCTextFieldTTF::textFieldWithPlaceHolder("Input...","Helvetica", 24);

	textField->setPosition(ccp(visibleSize.width*0.5, visibleSize.height*0.7));

	textField->setScale(2.0f);
	addChild(textField);



	//绑定接口

	textField->setDelegate(this);

	//开启输入

	textField->attachWithIME();

	//关闭输入

	//textField->detachWithIME();



	return true;
}


//当用户启动虚拟键盘时的回调函数

bool HelloWorld::onTextFieldAttachWithIME(CCTextFieldTTF *pSender)

{

	CCLOG("启动输入");

	//return false;

	return true;//不启动

}

//当用户关闭虚拟键盘时的回调函数

bool HelloWorld::onTextFieldDetachWithIME(CCTextFieldTTF *pSender)

{

	CCLOG("关闭输入");

	return  false;

	//return true:不关闭

}

//当用户进行输入时的回调函数

bool HelloWorld::onTextFieldInsertText(CCTextFieldTTF *pSender,const char *text,int nLen)

{

	CCLOG("输入字符...");

	return  false;

	//return true:不会输入进字符




}

//当用户删除文字时的回调函数

bool HelloWorld::onTextFieldDeleteBackward(CCTextFieldTTF *pSender,const char *delText,int nLen)

{

	CCLOG("删除字符");

	return  false;

	//return true:不删除

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
