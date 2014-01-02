#ifndef __BULLETLAYER_H_
#define __BULLETLAYER_H_
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;
class BulletLayer : public CCLayer
{
public:

	BulletLayer(void);
	~BulletLayer(void);
	
	virtual bool init();
	static BulletLayer* create();
	void AddBullet(float dt);
	void bulletMoveFinished(CCNode* pSender);
	void removeBullet(CCSprite* bullet);

	void startShoot(float delay = 0.0f);
	
	void stopShoot();
public:
	CCSpriteBatchNode* bulletBatchNode;
	CCArray* m_pAllBullet;

};
#endif // !__BULLETLAYER_H__
