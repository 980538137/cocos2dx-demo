#pragma once
#include "cocos2d.h"

USING_NS_CC;

class CCLayer1 : public CCLayer
{
public:
	CCLayer1(void);
	~CCLayer1(void);
	CREATE_FUNC(CCLayer1);

	virtual bool init();
};

