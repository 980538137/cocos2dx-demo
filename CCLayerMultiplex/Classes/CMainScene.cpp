#include "CMainScene.h"


CCMainScene::CCMainScene(void)
{
	_layer1=NULL;
	_layer2=NULL;
	_layer3=NULL;
	curLayerPos=0;
}


CCMainScene::~CCMainScene(void)
{
}

bool CCMainScene::init()
{
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!CCScene::init());

		_layer1=CCLayer1::create();
		_layer2=CCLayer2::create();
		_layer3=CCLayer3::create();

		_layerMuticomplex=CCLayerMultiplex::create(_layer1,_layer2,_layer3,NULL);
		this->addChild(_layerMuticomplex);

		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

		CCMenuItemImage *pCloseItem1 = CCMenuItemImage::create(
			"w_b.png",
			"w_b.png",
			this,
			menu_selector(CCMainScene::menuCallback));

		CCMenuItemImage *pCloseItem2 = CCMenuItemImage::create(
			"r_b.png",
			"r_b.png",
			this,
			menu_selector(CCMainScene::menuCallback));

		CCMenuItemImage *pCloseItem3 = CCMenuItemImage::create(
			"g_b.png",
			"g_b.png",
			this,
			menu_selector(CCMainScene::menuCallback));

		// create menu, it's an autorelease object
		pCloseItem1->setTag(0);
		pCloseItem2->setTag(1);
		pCloseItem3->setTag(2);
		CCMenu* pMenu = CCMenu::create(pCloseItem1, pCloseItem2, pCloseItem3, NULL);
		pMenu->alignItemsHorizontallyWithPadding(-1);
		pMenu->setPosition(visibleSize.width/2,25);
		this->addChild(pMenu, 1);
		bRet=true;
	} while (0);
	return bRet;
}

void CCMainScene::menuCallback(CCObject* pSender)
{
	int item=((CCMenuItemImage*)pSender)->getTag();
	if (item!=curLayerPos)
	{
		_layerMuticomplex->switchTo(item);
		curLayerPos=item;
	}
}