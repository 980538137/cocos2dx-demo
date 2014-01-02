//------------------------------
//项目名称：打地鼠
//------------------------------
//功能模块：游戏界面
//作	者：孤狼
//最后修改时间：2013/08/15
//http://gl.paea.cn
//------------------------------
#include "Game.h"
#include "Menu.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;
CCScene* Game::scene()
{
    CCScene * scene = NULL;
    do 
    {
        scene = CCScene::create();
        CC_BREAK_IF(! scene);
        Game *layer = Game::create();
        CC_BREAK_IF(! layer);
        scene->addChild(layer);
    } while (0);
    return scene;
}
//------------------------------
//函数名称：init
//函数作用：初始化
//------------------------------
//最后修改时间：2013/08/14
//------------------------------
bool Game::init()
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(! CCLayer::init());
		//-new-//
		CCSize mysize=CCDirector::sharedDirector()->getVisibleSize();
		CCPoint yuansize=CCDirector::sharedDirector()->getVisibleOrigin();
		//播放音乐,载入声效
		#define MUSIC_FILE	"music/bg.mp3"
		SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(MUSIC_FILE);
		SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1);
//		SimpleAudioEngine::sharedEngine()->playBackgroundMusic(MUSIC_FILE,true);
		//载入声效
//		SimpleAudioEngine::sharedEngine()->preloadEffect("music/hit.mp3");
		//设置背景
		CCSprite* spbg = CCSprite::create("gbg.jpg");
        spbg->setPosition(ccp(mysize.width/2, mysize.height/2));
        this->addChild(spbg, 0);
		//显示分数
		CCSprite * scsp=CCSprite::create("sc.png");
		scsp->setPosition(ccp(yuansize.x+50,mysize.height-20));
		addChild(scsp);
		scnum=0;
		sprintf(cscnum, "%d", scnum);
		CCLabelAtlas* sclable=CCLabelAtlas::create(cscnum, "num.png", 20, 20, '0');
		sclable->setScale(1.5);
		sclable->setPosition(ccp(yuansize.x+100,mysize.height-35));
		addChild(sclable,1,900);
		//显示时间
		CCLabelAtlas* timelabel=CCLabelAtlas::create("60", "num.png", 20, 20, '0');
		timelabel->setScale(1.5);
		timelabel->setPosition(ccp(mysize.width/2,mysize.height-35));
		addChild(timelabel,1,901);
		//开启多点
		this->setTouchEnabled(true);
		//启动游戏
		mnum=0;
		sjid=500;
		gametime=60;
		scheduleUpdate();
		gameovertag=1;//1正常 0游戏结束
		schedule(schedule_selector(Game::upsc),1.0f);
		//-new-//
        bRet = true;
    } while (0);

    return bRet;
}

//------------------------------
//函数名称：update
//函数作用：更新函数
//------------------------------
//最后修改时间：2013/08/14
//------------------------------
void Game::update(float tmd){
	this->addmouse();
}

//------------------------------
//函数名称：delmouse
//函数作用：删除老鼠
//------------------------------
//最后修改时间：2013/08/14
//------------------------------
void Game::delmouse(CCNode*node){
	CCSprite * sp=(CCSprite*)this->getChildByTag(node->getTag());
	this->removeChild(sp);
	this->addmouse();
	mnum=--mnum;
	//扣分
	scnum=--scnum;
	if(scnum<0){
		this->gameover();
	}else{
		Game::changnum(scnum);
	}
}

//------------------------------
//函数名称：delmouse2
//函数作用：删除击中耗子
//------------------------------
//最后修改时间：2013/08/15
//------------------------------
void Game::delmouse2(CCNode * node){
	this->removeChild(node);
}

//------------------------------
//函数名称：changnum
//函数作用：改变分数
//------------------------------
//最后修改时间：2013/08/14
//------------------------------
void Game::changnum(int scnum){
	sprintf(cscnum, "%d", scnum);
	string out(cscnum);
	CCLabelAtlas* sclable=(CCLabelAtlas*)this->getChildByTag(900);
	sclable->setString(out.c_str());
	sclable->retain();
}


//------------------------------
//函数名称：gameover
//函数作用：游戏失败
//------------------------------
//最后修改时间：2013/08/14
//------------------------------
void Game::gameover(){
	//删除所有元素
	this->removeAllChildren();
	//音乐处理
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.3f);
	//设置结束标记
	gameovertag=0;
	//停止所有更新
	unscheduleAllSelectors();
	CCSize mysize=CCDirector::sharedDirector()->getVisibleSize();
	CCPoint yuansize=CCDirector::sharedDirector()->getVisibleOrigin();
	//添加背景
	CCSprite*bgsp=CCSprite::create("over.jpg");
	bgsp->setPosition(ccp(mysize.width/2,mysize.height/2));
	this->addChild(bgsp,0);
	//添加分数
	CCSprite*maxs=CCSprite::create("maxs.png");
	maxs->setPosition(ccp(mysize.width/2-200,mysize.height/2-100));
	this->addChild(maxs,1);
	char ss[20];
	if(maxscnum<0){
		maxscnum=0;
	}
	sprintf(ss,"%d",maxscnum);
	CCTextFieldTTF * mytext=CCTextFieldTTF::textFieldWithPlaceHolder(ss,"Arial",24);
	mytext->setPosition(ccp(mysize.width/2,mysize.height/2-100));
	this->addChild(mytext);
	//添加菜单
	CCMenuItemImage * button1 = CCMenuItemImage::create("backmenu.png","backmenu.png",this,menu_selector(Game::backtomenu));
	CCMenuItemImage * button2 = CCMenuItemImage::create("runagain.png","runagain.png",this,menu_selector(Game::backtorun));
	button1->setPosition(ccp(mysize.width/2-200,yuansize.y+50));
	button2->setPosition(ccp(mysize.width/2+200,yuansize.y+50));
    CCMenu* pMenu = CCMenu::create(button1,button2, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
}

//------------------------------
//函数名称：backtomenu
//函数作用：返回菜单页面
//------------------------------
//最后修改时间：2013/08/14
//------------------------------
void Game::backtomenu(CCObject* pSender){
	CCScene * menuscene=Menu::scene();
	CCTransitionScene * tt=CCTransitionCrossFade::create(0.1f,menuscene);
	CCDirector::sharedDirector()->replaceScene(tt);
}

//------------------------------
//函数名称：backtorun
//函数作用：返回重新运行游戏
//------------------------------
//最后修改时间：2013/08/14
//------------------------------
void Game::backtorun(CCObject* pSender){
	CCScene * gamescene=Game::scene();
	CCTransitionScene * tt=CCTransitionCrossFade::create(0.1f,gamescene);
	CCDirector::sharedDirector()->replaceScene(tt);
}

//------------------------------
//函数名称：upsc
//函数作用：计时函数
//------------------------------
//最后修改时间：2013/08/15
//------------------------------
void Game::upsc(float tmd){
	gametime--;
	if(gametime>0){
		char ctimes[20];
		sprintf(ctimes, "%d", gametime);
		string time(ctimes);
		CCLabelAtlas* sclable=(CCLabelAtlas*)this->getChildByTag(901);
		sclable->setString(time.c_str());
	}else{
		this->gameover();
	}
}

//------------------------------
//函数名称：registerWithTouchDispatcher
//函数作用：注册多点触控
//------------------------------
//最后修改时间：2013/08/14
//------------------------------
void Game::registerWithTouchDispatcher(void){
	//注册监听
	CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this,0);
}

//------------------------------
//函数名称：ccTouchesBegan
//函数作用：多点按下
//------------------------------
//最后修改时间：2013/08/14
//------------------------------
void Game::ccTouchesBegan(CCSet * set,CCEvent * e){
	if(gameovertag==1){
		CCSetIterator iter=set->begin();
		//这里的iter相当于系统分配的数字，
		//set->begin()获取第一个数字
		//set->end()就是最后一位
		for(;iter!=set->end();iter++){
			//获取触点
			CCTouch * mytouch=(CCTouch *)(* iter);
			//获取坐标
			CCPoint point=mytouch->getLocation();
			//查找老鼠
			for(int i=4;i<10;i++){
				CCSprite *sp=(CCSprite*)this->getChildByTag(tags[i]);
				int maxx=sp->getPositionX()+40;
				int minx=sp->getPositionX()-40;
				int maxy=sp->getPositionY()+40;
				int miny=sp->getPositionY()-40;
				if(maxx>point.x&&point.x>minx){
					if(maxy>point.y&&point.y>miny){
						//播放音乐
						SimpleAudioEngine::sharedEngine()->setEffectsVolume(1);
//						SimpleAudioEngine::sharedEngine()->playEffect("music/hit.mp3",false);
						//加载死老鼠
						CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("mouse.plist");
						CCSprite *spd=CCSprite::createWithSpriteFrameName("1s.png");
						spd->setScale(0.5);
						spd->setPosition(sp->getPosition());
						this->removeChild(sp);
						this->addChild(spd);
						CCActionInterval * a1=CCBlink::create(2.0f,3);
						CCFiniteTimeAction * aaa=CCSequence::create(a1,CCCallFuncN::create(this,callfuncN_selector(Game::delmouse2)),NULL);
						spd->runAction(aaa);
						for(int ii=i;ii>3;ii--){
							tags[ii]=tags[ii-1];
						}
						this->addmouse();
						mnum=--mnum;
						scnum=++scnum;
						if(maxscnum<scnum){
							maxscnum=scnum;
						}
						this->changnum(scnum);
					}
				}
			}
		}
	}
}

void Game::addmouse(){
	//获取相对坐标系
	CCSize mysize=CCDirector::sharedDirector()->getVisibleSize();
	CCPoint yuansize=CCDirector::sharedDirector()->getVisibleOrigin();
	//增加老鼠
	if(mnum<=5){
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("mouse.plist");
		//随机数a(0-9)
		int a = rand()%(10);
		//随机数hy(50-379)
		int hy=50+rand()%(380);
		//随机ID
		sjid=++sjid;
		if(sjid>599){
			sjid=500;
		}
		//加入列表
		for(int i=1;i<10;i++){
			tags[i-1]=tags[i];
		}
		tags[9]=sjid;	
		if(a<=4){
			CCSprite * spc1=CCSprite::createWithSpriteFrameName("1.png");
			spc1->setPosition(ccp(-40,hy));
			spc1->setScale(0.5);
			this->addChild(spc1,2,sjid);
			CCActionInterval*c1=CCMoveTo::create(20.0f,ccp(mysize.width+40,hy));
			CCCallFuncN * back1=CCCallFuncN::create(this,callfuncN_selector(Game::delmouse));
			CCFiniteTimeAction * cq1=CCSequence::create(c1,back1,NULL);
			spc1->runAction(cq1);
		}else{
			CCSprite * spc2=CCSprite::createWithSpriteFrameName("2.png");
			spc2->setPosition(ccp(mysize.width+40,hy));
			spc2->setScale(0.5);
			this->addChild(spc2,2,sjid);
			CCActionInterval*c2=CCMoveTo::create(20.0f,ccp(-40,hy));
			CCCallFuncN * back2=CCCallFuncN::create(this,callfuncN_selector(Game::delmouse));
			CCFiniteTimeAction * cq2=CCSequence::create(c2,back2,NULL);
			spc2->runAction(cq2);
		}
		//增加数量
		mnum=++mnum;
	}
}

//------------------------------
//函数名称：onEnter
//函数作用：载入事件
//------------------------------
//最后修改时间：2013/08/14
//------------------------------
void Game::onEnter(){
	CCLayer::onEnter();
}

//------------------------------
//函数名称：onEnterTransitionDidFinish
//函数作用：载入完成事件
//------------------------------
//最后修改时间：2013/08/14
//------------------------------
void Game::onEnterTransitionDidFinish(){
	CCLayer::onEnterTransitionDidFinish();
}

//------------------------------
//函数名称：onExit
//函数作用：离开事件
//------------------------------
//最后修改时间：2013/08/14
//------------------------------
void Game::onExit(){
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
	SimpleAudioEngine::sharedEngine()->unloadEffect("music/hit.mp3");
}

