#pragma once
#include "cocos2d.h"
#include "Bullet.h"
#include "CommonData.h"

USING_NS_CC;

class WEAPON : public Sprite
{
public:
	WEAPON();
	~WEAPON();
	static WEAPON* create(CommonData::WeaponType = CommonData::WeaponType::HAND_GUN);
	bool init(CommonData::WeaponType = CommonData::WeaponType::HAND_GUN);

	BULLET* toggle(); //play the toggle animation and create a bullet

	CC_SYNTHESIZE(CommonData::Direction, m_direction, Direction);
	CC_SYNTHESIZE(CommonData::WeaponType, m_type, Type);
	CC_SYNTHESIZE(CommonData::BulletType, m_bulletType, BulletType);
	CC_SYNTHESIZE(float, m_step, Step);
	CC_SYNTHESIZE(float, m_bulletSpeed, BulletSpeed);
	CC_SYNTHESIZE(float, m_bulletRange, BulletRange);
	CC_SYNTHESIZE(int, m_bulletDamage, BulletDamage);
	CC_SYNTHESIZE(int, m_bulletCount, BulletCount);

private:
	BULLET* createBullet();

	bool m_fireLock;
	float m_cd;
};