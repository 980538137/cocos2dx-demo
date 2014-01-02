#ifndef __UPDATEDEMO_H__
#define __UPDATEDEMO_H__

#include "cocos2d.h"

class UpdateDemo : public cocos2d::CCLayer
{
public:
	virtual bool init();
	static cocos2d::CCScene* scene();
	void menuCloseCallback(CCObject* pSender);
	CREATE_FUNC(UpdateDemo);
	void update(float tmd);
	void myupdate(float tmd);
	void myupdate2(float tmd);
	int a;
	int b;
	int c;
	int x,y;

};
#endif