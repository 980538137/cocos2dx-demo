#include "TestScene.h"


CTestScene::CTestScene(void)
{
	_testlayer=NULL;
}


CTestScene::~CTestScene(void)
{
}

bool CTestScene::init()
{
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!CCScene::init());

		_testlayer=CTestLayer::create();
		this->addChild(_testlayer);

		bRet=true;
	} while (0);
	return bRet;
}