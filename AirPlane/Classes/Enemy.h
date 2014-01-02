#ifndef __ENEMY_H_
#define __ENEMY_H_

#include "cocos2d.h"

using namespace cocos2d;

class Enemy : public CCNode
{
public:
	Enemy(void);
	~Enemy(void);
	static Enemy* create();
	void bindSprite(CCSprite* sprite,int life);
	CCSprite* getSprite();
	int getLife();
	void loseLife();
	CCRect getBoundingBox();
private:
	CCSprite* m_pSprite;
	int m_life;
};

#endif // !__Enemy_H_
