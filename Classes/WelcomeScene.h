#ifndef _WELCOME_SCENE_H_
#define _WELCOME_SCENE_H_

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

class WelcomeScene : public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(WelcomeScene);
	void gameBeginCallback(cocos2d::Ref* pSender);
	void gameOptionCallback(cocos2d::Ref* pSender);
	void gameQuitCallback(cocos2d::Ref* pSender);
	void gameVolumeAddCallback(cocos2d::Ref* pSender);
	void gameVolumeMinusCallback(cocos2d::Ref* pSender);
	void gameLevelCallback(cocos2d::Ref* pSender);
	void gameBackCallback(cocos2d::Ref* pSender);
	void gameAboutCallback(Ref* pSender);
private:
	cocos2d::Sprite* title;
	cocos2d::Label* volumeLabel;
	cocos2d::Label* levelLabel;
};


#endif // !_WELCOME_SCENE_H_
