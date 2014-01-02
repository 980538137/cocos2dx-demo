#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"

using namespace cocos2d::extension;

class HelloWorld : public cocos2d::CCLayer,public CCScrollViewDelegate
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

	virtual void scrollViewDidScroll(CCScrollView* view);
	virtual void scrollViewDidZoom(CCScrollView* view);
};

#endif // __HELLOWORLD_SCENE_H__
