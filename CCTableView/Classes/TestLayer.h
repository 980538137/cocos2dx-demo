#pragma once
#include "cocos2d.h"

USING_NS_CC;

class CTestLayer :
	public CCLayer
{
public:
	CTestLayer(void);
	~CTestLayer(void);

	CREATE_FUNC(CTestLayer);
	virtual bool init();
};

