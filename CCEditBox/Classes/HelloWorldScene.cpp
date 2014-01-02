#include "HelloWorldScene.h"

USING_NS_CC;
using namespace cocos2d;
using namespace CocosDenshion;

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

	//CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);

	//// position the label on the center of the screen
	//pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
	//	origin.y + visibleSize.height - pLabel->getContentSize().height));

	//// add the label as a child to this layer
	//this->addChild(pLabel, 1);

	//// add "HelloWorld" splash screen"
	//CCSprite* pSprite = CCSprite::create("HelloWorld.png");

	//// position the sprite on the center of the screen
	//pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	//this->addChild(pSprite,0);


	CCScale9Sprite * scale9one = CCScale9Sprite::create("boxbg.png");
	CCEditBox * myeditbox1=CCEditBox::create(CCSizeMake(200,40),scale9one);
	myeditbox1->setInputMode(kEditBoxInputModeSingleLine);
	myeditbox1->setPosition(ccp(visibleSize.width/2,visibleSize.height-100));
	this->addChild(myeditbox1);
	myeditbox1->setDelegate(this);
	CCEditBox * myeditbox2=CCEditBox::create(CCSizeMake(200,40),scale9one);
	myeditbox2->setInputMode(kEditBoxInputModeSingleLine);
	myeditbox2->setInputFlag(kEditBoxInputFlagPassword);
	myeditbox2->setPosition(ccp(visibleSize.width/2,visibleSize.height-200));
	this->addChild(myeditbox2);
	myeditbox2->setDelegate(this);

	return true;
}

void HelloWorld::editBoxEditingDidBegin(cocos2d::extension::CCEditBox * myeditbox){

}
void HelloWorld::editBoxEditingDidEnd(cocos2d::extension::CCEditBox * myeditbox){

}

void HelloWorld::editBoxTextChanged(cocos2d::extension::CCEditBox * myeditbox,const std::string&text){

}

void HelloWorld::editBoxReturn(cocos2d::extension::CCEditBox * myeditbox){

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
