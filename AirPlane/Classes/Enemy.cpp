#include "Enemy.h"

Enemy::Enemy(void)
{
	m_pSprite = NULL;
	m_life = 0;
}

Enemy::~Enemy(void)
{

}

Enemy* Enemy::create()
{
	Enemy* pRet = new Enemy;
	pRet->autorelease();
	return pRet;
}

void Enemy::bindSprite(CCSprite* sprite,int life)
{
	m_pSprite = sprite;
	m_life = life;
	this->addChild(m_pSprite);
}

CCSprite* Enemy::getSprite()
{
	return m_pSprite;
}

int Enemy::getLife()
{
	return m_life;
}

void Enemy::loseLife()
{
	m_life--;
}

CCRect Enemy::getBoundingBox()
{
	CCRect rect = m_pSprite->boundingBox();
	CCPoint point = this->convertToWorldSpace(rect.origin);
	CCRect enemyRect(point.x,point.y,rect.size.width,rect.size.height);
	return enemyRect;
}