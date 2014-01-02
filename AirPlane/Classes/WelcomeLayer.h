#pragma once

#include "cocos2d.h"

USING_NS_CC;

class WelcomeLayer : public CCLayer
{
public:
	WelcomeLayer(void);
	~WelcomeLayer(void);

	static WelcomeLayer* create();
	virtual bool init();

	void loadingDone(CCNode* pNode);

	void keyBackClicked();
	bool isHaveSaveFile();
	void getHighestHistoryScore();
};