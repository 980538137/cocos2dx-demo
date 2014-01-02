//------------------------------
//项目名称：打地鼠
//------------------------------
//功能模块：游戏界面
//作	者：孤狼
//最后修改时间：2013/08/04
//------------------------------
#ifndef __GAME1_SCENE_H__
#define __GAME1_SCENE_H__
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
class Game : public cocos2d::CCLayer
{
public:
    virtual bool init();  
    static cocos2d::CCScene* scene();
    CREATE_FUNC(Game);
	//生命周期
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	//游戏更新函数
	void update(float tmd);
	//计时函数
	void upsc(float tmd);
	//时间
	int gametime;
	//耗子个数
	int mnum;
	//耗子tag数组
	int tags[10];
	//分数
	int maxscnum;//最高分
	int scnum;	//当前分
	char cscnum[20];
	//随机ID
	int sjid;
	//改变分数
	void changnum(int num);
	//游戏失败
	void gameover();
	int gameovertag;
	//增加老鼠
	void addmouse();
	//删除过境耗子
	void delmouse(CCNode*node);
	//删除击中耗子
	void delmouse2(CCNode * node);
	//触屏事件
	virtual void registerWithTouchDispatcher(void);
	virtual void ccTouchesBegan(CCSet * set,CCEvent * e);
	//菜单回调
	void backtomenu(CCObject* pSender);
	void backtorun(CCObject* pSender);
};

#endif 