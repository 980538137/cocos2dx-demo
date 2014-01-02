#pragma once

#include "cocos2d.h"
#include "WelcomeLayer.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class WelcomeScene : public CCScene
{
public:
	WelcomeScene(void);
	~WelcomeScene(void);
	static WelcomeScene* create();
	virtual bool init();

	void preloadMusic();
public:
	WelcomeLayer* _welcomeLayer;

};