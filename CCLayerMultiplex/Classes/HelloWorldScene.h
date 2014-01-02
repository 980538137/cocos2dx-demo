#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "CLayer1.h"
#include "CLayer2.h"
#include "CLayer3.h"
class HelloWorld : public cocos2d::CCLayer
{
public:
	HelloWorld(void);
	~HelloWorld(void);

	CREATE_FUNC(HelloWorld);
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually

private:
	CCLayer1* _layer1;
	CCLayer2* _layer2;
	CCLayer3* _layer3;

	int curLayerPos;

	CCLayerMultiplex* _layerMultiplex;
    
};

#endif // __HELLOWORLD_SCENE_H__
