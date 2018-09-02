#include "JoyStick.h"
#include "CommonData.h"
#include "GameOverScene.h"
#include "SimpleAudioEngine.h"
#include "PauseScene.h"

USING_NS_CC;
using namespace CommonData;

bool JoyStick::init()
{
	if (!Layer::init()) {
		return false;
	}

	currentTouch = ROCKER;
	m_hp = PLAYER_HP;
	m_totalHp = PLAYER_HP;

	// 标签字体配置
	TTFConfig ttfConfig;
	ttfConfig.fontFilePath = "Marker Felt.ttf";
	ttfConfig.fontSize = 20;

	//摇杆背景及相对层类位置
	rocker_bg = Sprite::create("joystickBg.png");
	rocker_bg->setPosition(Vec2(110,110));
	addChild(rocker_bg);

	//摇杆及相对层类位置
	rocker = Sprite::create("joystick.png");
	rocker->setPosition(Vec2(110, 110));
	addChild(rocker);

	//射击按钮
	shootButton = Sprite::create("Button_Shoot-untouch.png");
	shootButton->setPosition(Vec2(VISIBLE_SIZE.width - 110, 110));
	addChild(shootButton);

	//切枪按钮
	switchButton = Sprite::create("Button_Weapon-Gun-untouch.png");
	switchButton->setPosition(Vec2(VISIBLE_SIZE.width - 50, 225));
	addChild(switchButton);

	//暂停按钮
	pauseButton = Sprite::create("Button_Pause-untouch.png");
	pauseButton->setPosition(Vec2(VISIBLE_SIZE.width - 80, VISIBLE_SIZE.height - 40));
	addChild(pauseButton);

	//生命值图标
	auto hpIco = Sprite::create("Module_HP.png");
	hpIco->setPosition(Vec2(50, VISIBLE_SIZE.height - 25));
	addChild(hpIco);

	//生命条
	auto hpBar = Sprite::create("Module_HP-Bar.png");
	hpBar->setAnchorPoint(Vec2(0, 0.5));
	hpBar->setPosition(Vec2(70, VISIBLE_SIZE.height - 25));
	addChild(hpBar);

	//生命值显示
	hpLable = Label::createWithTTF(ttfConfig, StringUtils::format("%d", m_totalHp));
	hpLable->setAnchorPoint(Vec2(0, 0.5));
	hpLable->setPosition(Vec2(100, VISIBLE_SIZE.height - 28));
	addChild(hpLable);

	//子弹数图标
	auto mpIco = Sprite::create("Module_MP.png");
	mpIco->setPosition(Vec2(250, VISIBLE_SIZE.height - 25));
	addChild(mpIco);

	//子弹条
	auto mpBar = Sprite::create("Module_MP-Bar.png");
	mpBar->setAnchorPoint(Vec2(0, 0.5));
	mpBar->setPosition(Vec2(270, VISIBLE_SIZE.height - 25));
	addChild(mpBar);

	//子弹数显示
	mpLable = Label::createWithTTF(ttfConfig, StringUtils::format("10000"));
	mpLable->setAnchorPoint(Vec2(0, 0.5));
	mpLable->setPosition(Vec2(320, VISIBLE_SIZE.height - 28));
	addChild(mpLable);

	message = Label::createWithTTF(ttfConfig, StringUtils::format("Message"));
	message->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2 - 30));
	message->setVisible(false);
	addChild(message);

	return true;
}


/*当前对象被加入到父类节点上会调用该方法*/
void JoyStick::onEnter()
{
	/*首先调用父类的onEnter方法*/
	Layer::onEnter();

	/*开启单点触摸的监听, 可以用auto*/
	listener = EventListenerTouchOneByOne::create();

	/*没有使用lambda，使用回调更便于代码阅读*/
	listener->onTouchBegan = CC_CALLBACK_2(JoyStick::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(JoyStick::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(JoyStick::onTouchEnded, this);

	/*注册监听*/
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

}

/*当前对象从父类上移除时会调用该方法*/
void JoyStick::onExit()
{
	/*从分发中心移除注册的监听*/
	Director::getInstance()->getEventDispatcher()->removeEventListener(listener);

	/*最后调用父类的onExit()方法*/
	Layer::onExit();
}

bool JoyStick::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	Vec2 touch_pos = touch->getLocation();
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	if (this->shootButton->getBoundingBox().containsPoint(touch_pos)) {
		shootButton->setTexture("Button_Shoot-touched.png");
		currentTouch = SHOOT_BUTTON;
		return true;
	}

	if (this->switchButton->getBoundingBox().containsPoint(touch_pos)) {
		currentTouch = SWITCH_BUTTON;
		return true;
	}

	if (this->pauseButton->getBoundingBox().containsPoint(touch_pos)) {
		currentTouch = PAUSE_BUTTON;
		return true;
	}
	

	currentTouch = ROCKER;
	/*当触摸开始的时候， 如果触摸点的位置和我们中心点位置的距离 < 圆的半径 我们才能Move*/

	/*获取圆心点和半径*/
	float radius = rocker_bg->getContentSize().width / 2;
	Vec2 center = rocker_bg->getPosition();

	if (touch->getLocation().distance(center) > radius) {
		return false;
	}
	else {
		rocker->setPosition(Vec2(touch->getLocation()));
		return true;
	}

}

void JoyStick::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{

	if (currentTouch != ROCKER)return;
	/*当触摸移动的时候， 如果触摸点的位置和我们中心点位置的距离 < 圆的半径 */

	/*获取圆心点和半径*/
	float radius = rocker_bg->getContentSize().width / 2;
	Vec2 center = rocker_bg->getPosition();
	/*获取触摸点位置*/
	Vec2 touch_pos = touch->getLocation();
	float dis = touch_pos.distance(center);
	if (dis == 0) { return; }
	angle = acos((touch_pos.x - center.x) / dis);
	if (touch_pos.y > center.y) {
		checkDirection(angle);
	}
	else {
		checkDirection(-angle);
	}

	if (dis <= radius) {
		rocker->setPosition(Vec2(touch_pos));
	}
	else {
		/*如果在上半圆*/
		if (touch_pos.y > center.y) {
			rocker->setPosition(Vec2(center.x + radius * cos(angle), center.y + radius * sin(angle)));
		}
		else {
			rocker->setPosition(Vec2(center.x + radius * cos(angle), center.y - radius * sin(angle)));
		}
	}
}

void JoyStick::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	switch (currentTouch)
	{
	case SHOOT_BUTTON:
		switch (m_player->m_currentWeaponType)
		{
		case HAND_GUN:
			if (m_player->fire()) {
				audio->playEffect("hand_gun.wav", false, 1.0f, 1.0f, 1.0f);
			}
			break;
		case RIFLE_GUN:
			if (m_player->fire()) {
				audio->playEffect("rifle_gun.wav", false, 1.0f, 1.0f, 1.0f);
			}
			break;
		case SHOT_GUN:
			if (m_player->fire()) {
				audio->playEffect("shot_gun.wav", false, 1.0f, 1.0f, 1.0f);
			}
			break;
		case SNIPER_GUN:
			if (m_player->fire()) {
				audio->playEffect("sniper_gun.wav", false, 1.0f, 1.0f, 1.0f);
			}
			break;
		case RPG:
			if (m_player->fire()) {
				audio->playEffect("RPG.wav", false, 1.0f, 1.0f, 1.0f);
			}
			break;
		default:
			break;
		}
		shootButton->setTexture("Button_Shoot-untouch.png");
		
		this->setMp(m_player->getCurWeapon()->getBulletCount());
		currentTouch = ROCKER;
		break;
	case SWITCH_BUTTON:
		audio->playEffect("click2.wav", false, 1.0f, 1.0f, 1.0f);
		log("%s", "Weapon Changed");
		m_player->switchToNextWeapon();
		switch (m_player->m_currentWeaponType)
		{
		case HAND_GUN:
			switchButton->setTexture("Button_Weapon-Gun-untouch.png");
			break;
		case RIFLE_GUN:
			switchButton->setTexture("Button_Weapon-AK-untouch.png");
			break;
		case SHOT_GUN:
			switchButton->setTexture("Button_Weapon-SG-untouch.png");
			break;
		case SNIPER_GUN:
			switchButton->setTexture("Button_Weapon-AWP-untouch.png");
			break;
		case RPG:
			switchButton->setTexture("Button_Weapon-RPG-untouch.png");
			break;
		default:
			break;
		}
		currentTouch = ROCKER;
		this->setMp(m_player->getCurWeapon()->getBulletCount());
		break;
	case PAUSE_BUTTON:
		pauseScene = PauseScene::createScene();
		Director::getInstance()->pushScene(pauseScene);
		break;
	case ROCKER:
		rocker->setPosition(rocker_bg->getPosition());
		dir = STAY;
		break;
	default:
		break;
	}
	
}

// 对方向进行判断
void JoyStick::checkDirection(float angle)
{
	/*右方向*/
	if (angle >= -M_PI / 8.0 && angle <= M_PI / 8.0) {
		dir = RIGHT;
	}
	/*右边走 -八分之派 到 八分之派*/
	if (angle >= -(M_PI / 8.0) && angle <= M_PI / 8.0) {
		dir = RIGHT;
	}
	/*右上方向 八分之派 到 八分之三派*/
	else if (angle >= M_PI / 8.0 && angle < 3 * M_PI / 8.0) {
		dir = R_UP;
	}
	/*上方向 八分之三派 到 八分之五派*/
	else if (angle >= 3 * M_PI / 8.0 && angle <= 5 * M_PI / 8.0) {
		dir = UP;
	}
	/*左上方向 八分之5派 到 八分之七派*/
	else if (angle > 5 * M_PI / 8.0 && angle < 7 * M_PI / 8.0) {
		dir = L_UP;
	}
	/*左方向*/
	else if ((angle >= 7 * M_PI / 8.0 && angle <= M_PI) || (angle <= -7 * M_PI / 8.0 && angle >= -M_PI)) {
		dir = LEFT;
	}
	/*左下方向*/
	else if (angle > -7 * M_PI / 8.0 && angle < -5 * M_PI / 8.0) {
		dir = L_DOWN;
	}
	/*下方向*/
	else if (angle >= -5 * M_PI / 8.0 && angle <= -3 * M_PI / 8.0) {
		dir = DOWN;
	}
	/*右下方向*/
	else if (angle > -3 * M_PI / 8.0 && angle < -M_PI / 8.0) {
		dir = R_DOWN;
	}

}
Sprite* JoyStick::getRocker()
{
	return rocker;
}
Sprite* JoyStick::getRockerBg()
{
	return rocker_bg;
}

float JoyStick::getAngle()
{
	return angle;
}

Direction JoyStick::getDir()
{
	return dir;
}

void JoyStick::setTotalHp(int totalHp)
{
	this->m_totalHp = totalHp;
}

void JoyStick::setHp(int hp)
{
	this->m_hp = hp;
	this->hpLable->setString(StringUtils::format("%d", m_hp));
}

void JoyStick::setTotalMp(int totalMp)
{
	this->m_totalMp = totalMp;
}

void JoyStick::setMp(int mp)
{
	this->m_mp = mp;
	this->mpLable->setString(StringUtils::format("%d", m_mp));
}

void JoyStick::sendMessage(String m)
{
	this->message->setVisible(true);
	this->message->setString(StringUtils::format("%s",m.getCString()));
	if (isScheduled("MessageDelay")) {
		unschedule("MessageDelay");
	}
	scheduleOnce([this](float dt) {
		this->message->setVisible(false);
	}, 2.0f, "MessageDelay");

}