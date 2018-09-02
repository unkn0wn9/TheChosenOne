#ifndef _PAUSE_SCENE_H_
#define _PAUSE_SCENE_H_

#include "cocos2d.h"
#include "CommonData.h"

class PauseScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(PauseScene);

	void gameBackCallback(cocos2d::Ref* pSender);
	void gameQuitCallback(cocos2d::Ref* pSender);

};

#endif // !_PAUSE_SCENE_H_
