#ifndef _JOY_STICK_H_
#define _JOY_STICK_H_

#include "cocos2d.h"
#include "CommonData.h"
#include "Player.h"
#include "PauseScene.h"

using namespace CommonData;

typedef enum {
	ROCKER,
	SHOOT_BUTTON,
	SWITCH_BUTTON,
	PAUSE_BUTTON
}TOUCH_TYPE;

class JoyStick : public cocos2d::Layer   //JoyStick类从层继承
{
public:
	virtual bool init() override;
	
	CREATE_FUNC(JoyStick);

	virtual void onEnter() override;
	virtual void onExit() override;

	// 触摸三事件
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;

	/*检查当前角度并设置方向*/
	void checkDirection(float angle);

	cocos2d::Sprite* getRocker();
	cocos2d::Sprite* getRockerBg();
	float getAngle();
	Direction getDir();
	PLAYER *m_player;
	Scene* pauseScene;
	Label* hpLable;
	Label* mpLable;

	void setTotalHp(int totalHp);
	void setHp(int hp);

	void setTotalMp(int totalMp);
	void setMp(int mp);

	void sendMessage(cocos2d::String m);

private:
	cocos2d::EventListenerTouchOneByOne* listener;  /*定义为成员变量，方便移除监听*/
	cocos2d::Sprite* rocker; 
	cocos2d::Sprite* rocker_bg;

	//按钮
	cocos2d::Sprite* shootButton;
	cocos2d::Sprite* switchButton;
	cocos2d::Sprite* pauseButton;
	Direction dir;
	float angle;
	TOUCH_TYPE currentTouch;

	//数值
	int m_totalHp;
	int m_hp;
	int m_totalMp;
	int m_mp;

	//Message
	cocos2d::Label* message;
};

#endif // !_JOY_STICK_H_
