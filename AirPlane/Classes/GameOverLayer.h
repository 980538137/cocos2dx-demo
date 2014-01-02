#ifndef __GAMEOVERLAYER_H_
#define __GAMEOVERLAYER_H_
#include "cocos2d.h"

USING_NS_CC;

class GameOverLayer : public CCLayer
{
public:
	GameOverLayer(void);
	~GameOverLayer(void);

	virtual bool init();

	static GameOverLayer* create(int passScore);

	void menuBackCallback(CCObject* pSender);

	void beginChaneHighestScore(CCNode* pNode);

	virtual void keyBackClicked();//Android back
public:
	int score;

	static int highestHistoryScore;

	CCLabelBMFont* highestScore;

};

#endif