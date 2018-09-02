#ifndef _ABOUT_SCENE_H_
#define _ABOUT_SCENE_H_

#include "cocos2d.h"
#include "CommonData.h"

class AboutScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(AboutScene);

	void gameBackCallback(cocos2d::Ref* pSender);

};

#endif // !_ABOUT_SCENE_H_
