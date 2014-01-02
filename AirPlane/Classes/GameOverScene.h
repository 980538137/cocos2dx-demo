#ifndef __GAMEOVERSCENE_H_
#define __GAMEOVERSCENE_H_

#include "cocos2d.h"
#include "GameOverLayer.h"

using namespace cocos2d;

class GameOverScene : public CCScene
{
public:
	GameOverScene(void);
	~GameOverScene(void);

	virtual bool init();
	static GameOverScene* create(int passScore);

public:
	GameOverLayer* gameOverLayer;
	int score;
};
#endif