//------------------------------
//��Ŀ���ƣ������
//------------------------------
//����ģ�飺�˵�����
//��	�ߣ�����
//����޸�ʱ�䣺2013/07/30
//------------------------------
#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
class Menu : public cocos2d::CCLayer
{
public:
	virtual bool init();  
	static cocos2d::CCScene* scene();
	void menuCloseCallback(CCObject* pSender);
	CREATE_FUNC(Menu);
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();

	//������Ϸ
	void rungame(CCObject* pSender);
};

#endif 