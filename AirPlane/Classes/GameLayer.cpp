#include "GameLayer.h"

using namespace cocos2d;

Level GameLayer::level = EASY;

GameLayer::GameLayer(void)
{
	background1 = NULL;
	background2 = NULL;
	planeLayer = NULL;
	bulletLayer = NULL;
	enemyLayer = NULL;
	controllLayer = NULL;

	score = 0;
	bigBoomCount = 0;
	menuBigBoom = NULL;
	bigBoomCountItem = NULL;
}

GameLayer::~GameLayer(void)
{

}

CCScene* GameLayer::scene()
{
	CCScene* scene = CCScene::create();
	GameLayer* layer = GameLayer::create();
	scene->addChild(layer);
	return scene;
}

//GameLayer* GameLayer::create()
//{
//	GameLayer* gameLayer = new GameLayer();
//	if(gameLayer && gameLayer->init())
//	{
//		gameLayer->autorelease();
//		return gameLayer;
//	}
//	else
//	{
//		CC_SAFE_DELETE(gameLayer);
//		return NULL;
//	}
//}


bool GameLayer::init()
{
	CCLOG("GameLayer::init()");
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCLayer::init());
		level = EASY;
		//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/shoot_background.plist");

		background1 = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background.png"));
		background1->setAnchorPoint(ccp(0,0));
		background1->setPosition(ccp(0,0));
		this->addChild(background1);
		background2 = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background.png"));
		background2->setAnchorPoint(ccp(0,0)); 
		background2->setPosition(ccp(0,background1->getContentSize().height - 2));
		this->addChild(background2);

		this->planeLayer = PlaneLayer::create();
		this->addChild(planeLayer,1);

		this->bulletLayer = BulletLayer::create();
		this->addChild(bulletLayer);
		bulletLayer->startShoot();

		this->multiBulletsLayer = MultiBulletsLayer::create();
		this->addChild(multiBulletsLayer);
		//this->multiBulletsLayer->startShoot();

		this->enemyLayer = EnemyLayer::create();
		this->addChild(enemyLayer);

		this->controllLayer = ControllLayer::create();
		this->addChild(controllLayer);
		
		this->ufoLayer = UFOLayer::create();
		this->addChild(ufoLayer);
		


		this->schedule(schedule_selector(GameLayer::backgroundMove),0.01f);

		this->setTouchEnabled(true);

		this->scheduleUpdate();

	} while (0);
	return true;
}

void GameLayer::backgroundMove(float tmd)
{
	background1->setPositionY(background1->getPositionY() - 2);
	background2->setPositionY(background1->getPositionY() + background1->getContentSize().height - 2);
	if(background2->getPositionY() == 0)
	{
		background1->setPositionY(0);
	}
}

bool GameLayer::ccTouchBegan(CCTouch* pTouch,CCEvent* pEvent)
{
	CCLOG("begin");
	return true;
}

void GameLayer::ccTouchMoved(CCTouch* pTouch,CCEvent* pEvent)
{
	//CCLOG("move");
	if(this->planeLayer->isAlive)
	{
		CCPoint beginPoint = pTouch->getLocationInView();
		beginPoint = CCDirector::sharedDirector()->convertToGL(beginPoint);
		CCRect planeRect = planeLayer->getChildByTag(AIRPLANE)->boundingBox();
		planeRect.origin.x -= 15;
		planeRect.origin.y -= 15;
		planeRect.size.width += 30;
		planeRect.size.height += 30;
		if(planeRect.containsPoint(beginPoint))
		{
			CCPoint endPoint = pTouch->getPreviousLocation();
			//endPoint = CCDirector::sharedDirector()->convertToGL(endPoint);
			CCPoint offset = ccpSub(beginPoint,endPoint);
			CCPoint toPoint=ccpAdd(this->planeLayer->getChildByTag(AIRPLANE)->getPosition(),offset); 


			planeLayer->MoveTo(endPoint);


		}
	}
}

void GameLayer::ccTouchEnded(CCTouch* pTouch,CCEvent* pEvent)
{
	CCLOG("end");
}

void GameLayer::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this,0,true);
}

void GameLayer::update(float dt)
{
	if (level == EASY && score > 600000)
	{
		level = MIDDLE;
	}
	if (level == MIDDLE && score > 1000000)
	{
		level = HARD;
	}
	CCArray* bulletsToDelete = CCArray::create();
	bulletsToDelete->retain();
	CCObject* bt,*et,*ut;

	//Enemy1 && Bullet
	CCARRAY_FOREACH(this->bulletLayer->m_pAllBullet,bt)
	{
		CCSprite* bullet = (CCSprite*)bt;
		CCRect bulletRect = CCRectMake(
			bullet->getPosition().x - (bullet->getContentSize().width/2),
			bullet->getPosition().y - (bullet->getContentSize().height/2),
			bullet->getContentSize().width,
			bullet->getContentSize().height);
		CCArray* enemy1sToDelete = CCArray::create();
		enemy1sToDelete->retain();
		CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy1,et)
		{
			Enemy* enemy1 = (Enemy*)et;
			CCRect enemy1Rect = CCRectMake(enemy1->getPosition().x - (enemy1->getContentSize().width/2) - 15,
				enemy1->getPosition().y - (enemy1->getContentSize().height/2),
				enemy1->getContentSize().width + 30,
				enemy1->getContentSize().height);
			if(enemy1Rect.intersectsRect(bulletRect))
			{
				CCLOG("conflict1");
				if(enemy1->getLife() == 1)
				{
					enemy1->loseLife();
					bulletsToDelete->addObject(bullet);
					enemy1sToDelete->addObject(enemy1);
					score += ENEMY1_SCORE;
					controllLayer->updateScore(score);
				}
			}
		}
		CCARRAY_FOREACH(enemy1sToDelete,et)
		{
			Enemy* enemy1 = (Enemy*)et;
			this->enemyLayer->enemy1Blowup(enemy1);
		}
		enemy1sToDelete->release();

	}
	CCARRAY_FOREACH(bulletsToDelete,bt)
	{
		CCSprite* bullet = (CCSprite*)bt;
		this->bulletLayer->removeBullet(bullet);
	}
	bulletsToDelete->release();

	CCArray* bulletsToDelete2 = CCArray::create();
	bulletsToDelete2->retain();
	//Enemy2 && Bullet
	CCARRAY_FOREACH(this->bulletLayer->m_pAllBullet,bt)
	{
		CCSprite* bullet = (CCSprite*)bt;
		CCRect bulletRect = CCRectMake(bullet->getPosition().x - bullet->getContentSize().width/2,
			bullet->getPosition().y - bullet->getContentSize().height/2,
			bullet->getContentSize().width,
			bullet->getContentSize().height);
		CCArray* enemy2ToDelete = CCArray::create();
		enemy2ToDelete->retain();
		CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy2,et)
		{
			Enemy* enemy2 = (Enemy*)et;
			CCRect enemy2Rect = CCRectMake(enemy2->getPosition().x - enemy2->getContentSize().width/2 - 50,
				enemy2->getPosition().y - enemy2->getContentSize().height/2,
				enemy2->getContentSize().width+100,
				enemy2->getContentSize().height);
			if (enemy2Rect.intersectsRect(bulletRect))
			{
				CCLOG("conflict2");
				if (enemy2->getLife() > 1)
				{
					enemy2->loseLife();
					bulletsToDelete2->addObject(bullet);
				}
				else if (enemy2->getLife() == 1)
				{
					enemy2->loseLife();
					bulletsToDelete2->addObject(bullet);
					enemy2ToDelete->addObject(enemy2);
					score += ENEMY2_SCORE;
					controllLayer->updateScore(score);
				}
				else;
			}
		}
		CCARRAY_FOREACH(enemy2ToDelete,et)
		{
			Enemy* enemy2 = (Enemy*)et;
			this->enemyLayer->enemy2Blowup(enemy2);
		}
		enemy2ToDelete->release();
	}
	CCARRAY_FOREACH(bulletsToDelete2,bt)
	{
		CCSprite* bullet =(CCSprite*)bt;
		this->bulletLayer->removeBullet(bullet);
	}
	bulletsToDelete2->release();

	CCArray* bulletsToDelete3 = CCArray::create();
	bulletsToDelete3->retain();
	//Enemy3 && Bullet
	CCARRAY_FOREACH(this->bulletLayer->m_pAllBullet,bt)
	{
		CCSprite* bullet = (CCSprite*)bt;
		CCRect bulletRect = CCRectMake(bullet->getPosition().x - bullet->getContentSize().width/2,
			bullet->getPosition().y - bullet->getContentSize().height/2,
			bullet->getContentSize().width,
			bullet->getContentSize().height);
		CCArray* enemy3ToDelete = CCArray::create();
		enemy3ToDelete->retain();
		CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy3,et)
		{
			Enemy* enemy3 = (Enemy*)et;
			CCRect enemy3Rect = CCRectMake(enemy3->getPosition().x - enemy3->getContentSize().width/2 - 70,
				enemy3->getPosition().y - enemy3->getContentSize().height/2,
				enemy3->getContentSize().width+140,
				enemy3->getContentSize().height);
			if (enemy3Rect.intersectsRect(bulletRect))
			{
				if (enemy3->getLife() > 1)
				{
					enemy3->loseLife();
					bulletsToDelete3->addObject(bullet);
				}
				else if (enemy3->getLife() == 1)
				{
					enemy3->loseLife();
					bulletsToDelete3->addObject(bullet);
					enemy3ToDelete->addObject(enemy3);
					score += ENEMY3_SCORE;
					controllLayer->updateScore(score);
				}
				else;
			}
		}
		CCARRAY_FOREACH(enemy3ToDelete,et)
		{
			Enemy* enemy3 = (Enemy*)et;
			this->enemyLayer->enemy3Blowup(enemy3);
		}
		enemy3ToDelete->release();
	}
	CCARRAY_FOREACH(bulletsToDelete3,bt)
	{
		CCSprite* bullet =(CCSprite*)bt;
		this->bulletLayer->removeBullet(bullet);
	}
	bulletsToDelete3->release();

	//enemy1 && multiBullets
	CCArray* multiBulletsToDelete = CCArray::create();
	multiBulletsToDelete->retain();
	CCARRAY_FOREACH(this->multiBulletsLayer->m_pAllMultiBullets,bt)
	{
		CCSprite* multiBullet = (CCSprite*)bt;
		CCRect multiBulletRect = CCRectMake(multiBullet->getPosition().x - multiBullet->getContentSize().width/2,
			multiBullet->getPosition().y - multiBullet->getContentSize().height/2,
			multiBullet->getContentSize().width,
			multiBullet->getContentSize().height);
		CCArray* enemy1ToDelete = CCArray::create();
		enemy1ToDelete->retain();
		CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy1,et)
		{
			Enemy* enemy1 = (Enemy*)et;
			CCRect enemy1Rect = CCRectMake(enemy1->getPosition().x - (enemy1->getContentSize().width/2) - 15,
				enemy1->getPosition().y - (enemy1->getContentSize().height/2),
				enemy1->getContentSize().width + 30,
				enemy1->getContentSize().height);
			if (enemy1Rect.intersectsRect(multiBulletRect))
			{
				if (enemy1->getLife() == 1)
				{
					enemy1->loseLife();
					multiBulletsToDelete->addObject(multiBullet);
					enemy1ToDelete->addObject(enemy1);
					score += ENEMY1_SCORE;
					this->controllLayer->updateScore(score);
				}
			}
		}
		CCARRAY_FOREACH(enemy1ToDelete,et)
		{
			Enemy* enemy1 = (Enemy*)et;
			this->enemyLayer->enemy1Blowup(enemy1);
		}
		enemy1ToDelete->release();
	}
	CCARRAY_FOREACH(multiBulletsToDelete,bt)
	{
		CCSprite* multiBullet = (CCSprite*)bt;
		this->multiBulletsLayer->removeMultiBullets(multiBullet);
	}
	multiBulletsToDelete->release();

	//enemy2 && multiBullets
	CCArray* multiBulletsToDelete2 = CCArray::create();
	multiBulletsToDelete2->retain();
	CCARRAY_FOREACH(this->multiBulletsLayer->m_pAllMultiBullets,bt)
	{
		CCSprite* multiBullet = (CCSprite*)bt;
		CCRect multiBulletRect = CCRectMake(multiBullet->getPosition().x - multiBullet->getContentSize().width/2,
			multiBullet->getPosition().y - multiBullet->getContentSize().height/2,
			multiBullet->getContentSize().width,
			multiBullet->getContentSize().height);

		CCArray* enemy2ToDelete = CCArray::create();
		enemy2ToDelete->retain();
		CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy2,et)
		{
			Enemy* enemy2 = (Enemy*)et;
			CCRect enemy2Rect = CCRectMake(enemy2->getPosition().x - enemy2->getContentSize().width/2 - 50,
				enemy2->getPosition().y - enemy2->getContentSize().height/2,
				enemy2->getContentSize().width+100,
				enemy2->getContentSize().height);
			if (enemy2Rect.intersectsRect(multiBulletRect))
			{
				if (enemy2->getLife() > 1)
				{
					enemy2->loseLife();
					multiBulletsToDelete2->addObject(multiBullet);
				}else if (enemy2->getLife() == 1)
				{
					enemy2->loseLife();
					multiBulletsToDelete2->addObject(multiBullet);
					enemy2ToDelete->addObject(enemy2);
					score += ENEMY2_SCORE;
					this->controllLayer->updateScore(score);
				}
			}
		}
		CCARRAY_FOREACH(enemy2ToDelete,et)
		{
			Enemy* enemy2 = (Enemy*)et;
			this->enemyLayer->enemy2Blowup(enemy2);
		}
		enemy2ToDelete->release();
	}
	CCARRAY_FOREACH(multiBulletsToDelete2,bt)
	{
		CCSprite* multiBullet = (CCSprite*)bt;
		this->multiBulletsLayer->removeMultiBullets(multiBullet);
	}
	multiBulletsToDelete2->release();

	//enemy3 && multiBullets
	CCArray* multiBulletsToDelete3 = CCArray::create();
	multiBulletsToDelete3->retain();
	CCARRAY_FOREACH(this->multiBulletsLayer->m_pAllMultiBullets,bt)
	{
		CCSprite* multiBullet = (CCSprite*)bt;
		CCRect multiBulletRect = CCRectMake(multiBullet->getPosition().x - multiBullet->getContentSize().width/2,
			multiBullet->getPosition().y - multiBullet->getContentSize().height/2,
			multiBullet->getContentSize().width,
			multiBullet->getContentSize().height);

		CCArray* enemy3ToDelete = CCArray::create();
		enemy3ToDelete->retain();
		CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy3,et)
		{
			Enemy* enemy3 = (Enemy*)et;
			CCRect enemy3Rect = CCRectMake(enemy3->getPosition().x - enemy3->getContentSize().width/2 - 70,
				enemy3->getPosition().y - enemy3->getContentSize().height/2,
				enemy3->getContentSize().width+140,
				enemy3->getContentSize().height);
			if (enemy3Rect.intersectsRect(multiBulletRect))
			{
				if (enemy3->getLife() > 1)
				{
					enemy3->loseLife();
					multiBulletsToDelete3->addObject(multiBullet);
				}else if (enemy3->getLife() == 1)
				{
					enemy3->loseLife();
					multiBulletsToDelete2->addObject(multiBullet);
					enemy3ToDelete->addObject(enemy3);
					score += ENEMY3_SCORE;
					this->controllLayer->updateScore(score);
				}
			}
		}
		CCARRAY_FOREACH(enemy3ToDelete,et)
		{
			Enemy* enemy3 = (Enemy*)et;
			this->enemyLayer->enemy3Blowup(enemy3);
		}
		enemy3ToDelete->release();
	}
	CCARRAY_FOREACH(multiBulletsToDelete3,bt)
	{
		CCSprite* multiBullet = (CCSprite*)bt;
		this->multiBulletsLayer->removeMultiBullets(multiBullet);
	}
	multiBulletsToDelete3->release();


	//enemy1 && airPlane
	CCRect airPlaneRect = this->planeLayer->getChildByTag(AIRPLANE)->boundingBox();
	CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy1,et)
	{
		Enemy* enemy1 = (Enemy*)et;
		CCRect enemy1Rect = CCRectMake(enemy1->getPosition().x - (enemy1->getContentSize().width/2),
			enemy1->getPosition().y - (enemy1->getContentSize().height/2),
			enemy1->getContentSize().width,
			enemy1->getContentSize().height);
		if (enemy1->getLife() > 0)
		{
			if (airPlaneRect.intersectsRect(enemy1Rect))
			{
				this->unscheduleAllSelectors();
				this->bulletLayer->stopShoot();
				this->multiBulletsLayer->stopShoot();
				this->planeLayer->blowUp(score);
				this->enemyLayer->enemy1Blowup(enemy1);
			}
		}
	}

	//enemy2 && airPlane
	CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy2,et)
	{
		Enemy* enemy2 = (Enemy*)et;
		//CCRect enemy2Rect = enemy2->getSprite()->boundingBox();
		CCRect enemy2Rect = CCRectMake(
			enemy2->getPosition().x - enemy2->getSprite()->getContentSize().width/2,
			enemy2->getPosition().y - enemy2->getSprite()->getContentSize().height/2,
			enemy2->getContentSize().width,
			enemy2->getContentSize().height);
		if (enemy2->getLife() > 0)
		{
			if (airPlaneRect.intersectsRect(enemy2Rect))
			{
				this->unscheduleAllSelectors();
				this->bulletLayer->stopShoot();
				this->multiBulletsLayer->stopShoot();
				this->planeLayer->blowUp(score);
				this->enemyLayer->enemy2Blowup(enemy2);
			}
		}
	}

	//enemy3 && airPlane
	CCARRAY_FOREACH(this->enemyLayer->m_pAllEnemy3,et)
	{
		Enemy* enemy3 = (Enemy*)et;
		//CCRect enemy2Rect = enemy2->getSprite()->boundingBox();
		CCRect enemy3Rect = CCRectMake(
			enemy3->getPosition().x - enemy3->getSprite()->getContentSize().width/2,
			enemy3->getPosition().y - enemy3->getSprite()->getContentSize().height/2,
			enemy3->getContentSize().width,
			enemy3->getContentSize().height);
		if (enemy3->getLife() > 0)
		{
			if (airPlaneRect.intersectsRect(enemy3Rect))
			{
				this->unscheduleAllSelectors();
				this->bulletLayer->stopShoot();
				this->multiBulletsLayer->stopShoot();
				this->planeLayer->blowUp(score);
				this->enemyLayer->enemy3Blowup(enemy3);
			}
		}
	}

	//multiBullets && airplane
	CCARRAY_FOREACH(this->ufoLayer->m_pAllMultiBullets,ut)
	{
		CCSprite* multiBullets = (CCSprite*)ut;
		CCRect multiBulletsRect = CCRectMake(
			multiBullets->getPosition().x - multiBullets->getContentSize().width/2,
			multiBullets->getPosition().y - multiBullets->getContentSize().height/2,
			multiBullets->getContentSize().width,
			multiBullets->getContentSize().height);
		if (airPlaneRect.intersectsRect(multiBulletsRect))
		{
			this->ufoLayer->removeMultiBullets(multiBullets);
			this->bulletLayer->stopShoot();
			this->multiBulletsLayer->startShoot();
			this->bulletLayer->startShoot(6.0f);
		}
	}

	CCARRAY_FOREACH(this->ufoLayer->m_pAllBigBoom,ut)
	{
		CCSprite* bigBoom = (CCSprite*)ut;
		CCRect bigBoomRect = CCRectMake(bigBoom->getPosition().x - bigBoom->getContentSize().width/2,
			bigBoom->getPosition().y - bigBoom->getContentSize().height/2,
			bigBoom->getContentSize().width,
			bigBoom->getContentSize().height);
		if (airPlaneRect.intersectsRect(bigBoomRect))
		{
			this->ufoLayer->removeBigBoom(bigBoom);
			bigBoomCount++;
			updateBigBoomCountItem(bigBoomCount);
		}
	}

}

void GameLayer::updateBigBoomCountItem(int bigBoomCount)
{
	if (menuBigBoom == NULL)
	{
		CCSprite* normalBoom = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bomb.png"));
		CCSprite* pressedBoom = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bomb.png"));

		CCMenuItemImage* pBigBoomItem = CCMenuItemImage::create();
		pBigBoomItem->initWithNormalSprite(normalBoom,pressedBoom,NULL,this,menu_selector(GameLayer::menuBigBoomCallback));
		pBigBoomItem->setPosition(pBigBoomItem->getContentSize().width/2 + 10,pBigBoomItem->getContentSize().height/2 + 10);
		menuBigBoom = CCMenu::create(pBigBoomItem,NULL);
		menuBigBoom->setPosition(CCPointZero);
		this->addChild(menuBigBoom);

		CCString* strScore = CCString::createWithFormat("X %d",bigBoomCount);
		bigBoomCountItem = CCLabelBMFont::create(strScore->m_sString.c_str(),"fonts/font.fnt");
		bigBoomCountItem->setColor(ccc3(143,146,147));
		bigBoomCountItem->setPosition(ccp(normalBoom->getContentSize().width + bigBoomCountItem->getContentSize().width/2 + 10,bigBoomCountItem->getContentSize().height/2 + 20));
		this->addChild(bigBoomCountItem);
	}
	else
	{
		if (bigBoomCount == 0)
		{
			menuBigBoom->setVisible(false);
			bigBoomCountItem->setVisible(false);
		}
		else if (bigBoomCount > 0)
		{
			menuBigBoom->setVisible(true);
			bigBoomCountItem->setVisible(true);
			CCString* strScore = CCString::createWithFormat("X %d",bigBoomCount);
			bigBoomCountItem->setString(strScore->m_sString.c_str());
		}
	}

}

void GameLayer::menuBigBoomCallback(CCObject* pSender)
{
	if (bigBoomCount >0)
	{
		bigBoomCount--;
		score += this->enemyLayer->m_pAllEnemy1->count() * ENEMY1_SCORE;
		score += this->enemyLayer->m_pAllEnemy2->count() * ENEMY2_SCORE;
		this->enemyLayer->removeAllEnemy();
		this->controllLayer->updateScore(score);
		updateBigBoomCountItem(bigBoomCount);
	}
	

}

Level GameLayer::getCurLevel()
{
	return level;
}