#pragma once
#include "cocos2d.h"

USING_NS_CC;

class CCLayer2 :
	public CCLayer
{
public:
	CCLayer2(void);
	~CCLayer2(void);

	CREATE_FUNC(CCLayer2);

	virtual bool init();
};

