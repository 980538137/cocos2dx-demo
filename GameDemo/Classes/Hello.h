//------------------------------
//��Ŀ���ƣ������
//------------------------------
//����ģ�飺��ӭ����
//��	�ߣ�����
//����޸�ʱ�䣺2013/07/30
//------------------------------
#ifndef __HELLO_SCENE_H__
#define __HELLO_SCENE_H__
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class Hello : public cocos2d::CCLayer
{
public:
    virtual bool init();  
    static cocos2d::CCScene* scene();
    CREATE_FUNC(Hello);
	void trunscene();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
};

#endif 