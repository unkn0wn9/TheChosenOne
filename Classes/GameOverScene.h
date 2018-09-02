#ifndef GAMEOVERSCENE_H__
#define GAMEOVERSCENE_H__
#include "cocos2d.h"
#include "CommonData.h"

class GameOverScene :public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene(int);
	virtual bool init(int);
	static GameOverScene* create(int);
};
#endif // !GAMEOVERSCENE_H__

