#ifndef __PLANELAYER_H__
#define __PLANELAYER_H__

#include "cocos2d.h"
#include "GameOverScene.h"
using namespace cocos2d;

const int AIRPLANE = 747;

class PlaneLayer : public CCLayer
{
public:
	PlaneLayer(void);
	~PlaneLayer(void);
	
	static PlaneLayer* create();

	virtual bool init();

	void MoveTo(CCPoint location);

	void blowUp(int score);

	void removePlane();
public:
	static PlaneLayer* sharedPlane;
	bool isAlive;
	int score;
};
#endif // !__PLANELAYER_H__
