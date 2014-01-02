#include "TestLayer.h"
#include "TableViewTestScene.h"

CTestLayer::CTestLayer(void)
{
}


CTestLayer::~CTestLayer(void)
{
}

bool CTestLayer::init()
{
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		TableViewTestLayer *pLayer = TableViewTestLayer::create();
		this->addChild(pLayer);

		bRet=true;
	} while (0);
	return bRet;
}