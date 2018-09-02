#include "Weapon.h"

using namespace CommonData;
WEAPON::WEAPON()
	:m_bulletType(GUN_BULLET),
	m_bulletRange(0),
	m_bulletSpeed(0),
	m_step(0),
	m_type(HAND_GUN)
{
	m_direction = RIGHT;
	m_fireLock = false;
	m_cd = 0;
}

WEAPON::~WEAPON()
{

}
BULLET* WEAPON::createBullet()
{
	BULLET *bullet = nullptr;
	if (this->m_bulletCount <= 0)
	{
		return bullet;
	}
	else
	{
		if(!this->m_type == HAND_GUN)
			this->m_bulletCount--;
		bullet = BULLET::create(this->m_bulletType);
		bullet->setPosition(this->getPosition());
		bullet->setRange(this->m_bulletRange);
		bullet->setDirection(this->m_direction);
		bullet->setSpeed(this->m_bulletSpeed);
		return bullet;
	}
}

WEAPON* WEAPON::create(WeaponType wType)
{
	auto weapon = new WEAPON();
	if (weapon && weapon->init(wType)) 
	{
		weapon->autorelease();
		return weapon;
	}
	delete weapon;
	weapon = NULL;
	return NULL;
}

bool WEAPON::init(WeaponType type)
{
	this->setVisible(false);
	this->m_type = type;
	switch (type)
	{
	case HAND_GUN:
		this->m_cd = HAND_GUN_BULLET_CD;
		this->m_bulletType = GUN_BULLET;
		this->m_bulletRange = HAND_GUN_BULLET_RANGE;
		this->m_bulletSpeed = HAND_GUN_BULLET_STEP;
		this->m_bulletDamage = HAND_GUN_BULLET_DAMAGE;
		this->m_bulletCount = HAND_GUN_BULLET_COUNT;
		Sprite::initWithSpriteFrameName(IMG_HAND_GUN_RIGHT);
		//this->setScale(1.6f);
		break;
	case RIFLE_GUN:
		this->m_cd = RIFLE_GUN_BULLET_CD;
		this->m_bulletType = GUN_BULLET;
		this->m_bulletRange = RIFLE_GUN_BULLET_RANGE;
		this->m_bulletSpeed = RIFLE_GUN_BULLET_STEP;
		this->m_bulletDamage = RIFLE_GUN_BULLET_DAMAGE;
		this->m_bulletCount = RIFLE_GUN_BULLET_COUNT;
		Sprite::initWithSpriteFrameName(IMG_RIFLE_GUN_RIGHT);
		break;

	case SHOT_GUN:
		this->m_cd = SHOT_GUN_BULLET_CD;
		this->m_bulletType = GUN_BULLET;
		this->m_bulletRange = SHOT_GUN_BULLET_RANGE;
		this->m_bulletSpeed = SHOT_GUN_BULLET_STEP;
		this->m_bulletDamage = SHOT_GUN_BULLET_DAMAGE;
		this->m_bulletCount = SHOT_GUN_BULLET_COUNT;
		Sprite::initWithSpriteFrameName(IMG_SHOT_GUN_RIGHT);
		break;

	case SNIPER_GUN:
		this->m_cd = SNIPER_GUN_BULLET_CD;
		this->m_bulletType = GUN_BULLET;
		this->m_bulletRange = SNIPER_GUN_BULLET_RANGE;
		this->m_bulletSpeed = SNIPER_GUN_BULLET_STEP;
		this->m_bulletDamage = SNIPER_GUN_BULLET_DAMAGE;
		this->m_bulletCount = SNIPER_GUN_BULLET_COUNT;
		Sprite::initWithSpriteFrameName(IMG_SNIPER_GUN_RIGHT);
		break;

	case RPG:
		this->m_cd = RPG_BULLET_CD;
		this->m_bulletType = RPG_BULLET;
		this->m_bulletRange = RPG_BULLET_RANGE;
		this->m_bulletSpeed = RPG_BULLET_STEP;
		this->m_bulletDamage = RPG_BULLET_DAMAGE;
		this->m_bulletCount = RPG_BULLET_COUNT;
		Sprite::initWithSpriteFrameName(IMG_RPG_RIGHT);
		break;

	default:
		break;
	}
	this->setZOrder(WEAPON_ZORDER);
	return true;
}

BULLET* WEAPON::toggle()
{
	if (m_fireLock == true) {
		return nullptr;
	}
	else {
		
		if (m_cd != 0) {
			m_fireLock = true;

			scheduleOnce([this](float dt) {
				this->m_fireLock = false;
			}, m_cd, "weaponCD");
		}

		return this->createBullet();
	}
}
