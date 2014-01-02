#pragma once
#include "cocos2d.h"
#include "CLayer1.h"
#include "CLayer2.h"
#include "CLayer3.h"

USING_NS_CC;

class CCMainScene : public CCScene
{
public:
	CCMainScene(void);
	~CCMainScene(void);

	CREATE_FUNC(CCMainScene);
	virtual bool init();

	void menuCallback(CCObject* pSender);

private:
	CCLayer1* _layer1;
	CCLayer2* _layer2;
	CCLayer3* _layer3;
	int curLayerPos;

	CCLayerMultiplex* _layerMuticomplex;
};

