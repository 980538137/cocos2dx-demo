//------------------------------
//项目名称：打地鼠
//------------------------------
//功能模块：菜单界面
//作	者：孤狼
//最后修改时间：2013/07/30
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

	//启动游戏
	void rungame(CCObject* pSender);
};

#endif 