#pragma once

#include "cocos2d.h"
#include "GameLayer.h"

USING_NS_CC;  

class GameScene : public CCScene
{
public:
	GameScene(void);
	~GameScene(void);

	//SCENE_CREATE_FUNC(GameScene);
	static GameScene* create();
	virtual bool init();
public:
	GameLayer* _gameLayer;

};

