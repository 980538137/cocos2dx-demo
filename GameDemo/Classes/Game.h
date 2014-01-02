//------------------------------
//��Ŀ���ƣ������
//------------------------------
//����ģ�飺��Ϸ����
//��	�ߣ�����
//����޸�ʱ�䣺2013/08/04
//------------------------------
#ifndef __GAME1_SCENE_H__
#define __GAME1_SCENE_H__
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
class Game : public cocos2d::CCLayer
{
public:
    virtual bool init();  
    static cocos2d::CCScene* scene();
    CREATE_FUNC(Game);
	//��������
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	//��Ϸ���º���
	void update(float tmd);
	//��ʱ����
	void upsc(float tmd);
	//ʱ��
	int gametime;
	//���Ӹ���
	int mnum;
	//����tag����
	int tags[10];
	//����
	int maxscnum;//��߷�
	int scnum;	//��ǰ��
	char cscnum[20];
	//���ID
	int sjid;
	//�ı����
	void changnum(int num);
	//��Ϸʧ��
	void gameover();
	int gameovertag;
	//��������
	void addmouse();
	//ɾ����������
	void delmouse(CCNode*node);
	//ɾ�����к���
	void delmouse2(CCNode * node);
	//�����¼�
	virtual void registerWithTouchDispatcher(void);
	virtual void ccTouchesBegan(CCSet * set,CCEvent * e);
	//�˵��ص�
	void backtomenu(CCObject* pSender);
	void backtorun(CCObject* pSender);
};

#endif 