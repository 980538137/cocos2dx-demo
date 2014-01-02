#include "GameScene.h"

GameScene::GameScene(void)
{
	_gameLayer = NULL;
}

GameScene::~GameScene(void)
{

}

GameScene* GameScene::create()
{
	GameScene* pRet = new GameScene();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool GameScene::init()
{
	bool bRet = false;
	do
	{
		//CC_BREAK_IF(!GameScene::init());
		_gameLayer = GameLayer::create();
		//CC_BREAK_IF(!_gameLayer);
		this->addChild(_gameLayer);
		bRet = true;
	} while (0);
	return bRet;

}