#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;
class HelloWorld : public cocos2d::CCLayer
{

public:
	CCSprite* pLargeCloudSprite;
	CCSprite* pMediumCloudSprite;
	CCSprite* pSmallCloudSprite;

	CCSprite* duckSprite;
	CCSprite* duckSprite2;

	int x,y;
	int x1,y1;
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

	void cloudCallback1();
	void cloudCallback2();
	void cloudCallback3();

	void update(float tmd);

	CCArray* getDuckAnimations();

	void ccTouchesEnded(cocos2d::CCSet* touches,cocos2d::CCEvent* event);
protected:
	CCArray* _bullets;
	CCArray* _ducks;

};

#endif // __HELLOWORLD_SCENE_H__
