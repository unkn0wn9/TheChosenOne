#pragma once
#include "cocos2d.h"
#include "Weapon.h"

USING_NS_CC;

class PLAYER :public Sprite
{
public:
	PLAYER();
	~PLAYER();
	CREATE_FUNC(PLAYER);
	bool init();

	CC_SYNTHESIZE(CommonData::Direction, m_direction, Direction);
	CC_SYNTHESIZE(int, m_HP, HP);
	CC_SYNTHESIZE(int, m_score, Score);
	CC_SYNTHESIZE(float, m_step, Step);
	CC_SYNTHESIZE(Scene*, m_gameScene, GameScene);

	BULLET* fire();
	void hit(int);
	void down();

	CommonData::WeaponType switchToNextWeapon();
	void addWeapon(CommonData::WeaponType);
	void grabProperty(CommonData::PropType);
	void updatePosition(CommonData::Direction);
	void stopMove();

	WEAPON *getCurWeapon() { return m_currentWeapon; };

	CommonData::WeaponType m_currentWeaponType;

	void updateAnimation();

private:

	Vector<WEAPON*> m_weapon;

	bool m_isRight;
	bool m_isMoving;

	void render();
	void render(CommonData::Direction);
	
	int m_weaponCount;
	WEAPON* m_currentWeapon;
	int m_currentWeaponIndex;
	//int m_weaponCount;
	CommonData::WeaponType switchWeaponByIndex(int);

};