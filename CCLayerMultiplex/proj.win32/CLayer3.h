#pragma once
#include "cocos2d.h"

USING_NS_CC;

class CCLayer3 :
	public CCLayer
{
public:
	CCLayer3(void);
	~CCLayer3(void);

	CREATE_FUNC(CCLayer3);

	virtual bool init();
};

