#include "Player.h"
using namespace CommonData;

PLAYER::PLAYER()
{
	this->m_HP = 100;
	this->m_score = 0;
	this->m_step = 10;
	this->m_currentWeapon = nullptr;
	this->m_currentWeaponType = HAND_GUN;
	this->m_currentWeaponIndex = 0;
	this->m_direction = Direction::STAY;
	this->m_isMoving = false;
	this->m_weaponCount = 0;
	this->m_isRight = true;
}

PLAYER::~PLAYER()
{
}

bool PLAYER::init()
{
	Sprite::initWithSpriteFrameName(PLAYER_INITIAL_IMG);
	this->setPosition(Point(VISIBLE_SIZE / 2));
	this->getTexture()->setAliasTexParameters();
	this->setZOrder(PLAYER_ZORDER);

	auto physicsBody = PhysicsBody::createBox(this->getBoundingBox().size, PhysicsMaterial(10.0f, 1.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setGravityEnable(false);

	physicsBody->setCategoryBitmask(PLAYER_CAT_BITMASK);
	physicsBody->setCollisionBitmask(PLAYER_COL_BITMASK);
	physicsBody->setContactTestBitmask(PLAYER_CON_BITMASK);

	physicsBody->setTag(PLAYER_TAG);

	this->addComponent(physicsBody);

	return true;
}

BULLET* PLAYER::fire()
{
	//this->m_currentWeapon->setDirection(this->m_direction);
	auto bul = this->m_currentWeapon->toggle();
	if(bul == nullptr)
	{
		return nullptr;
	}
	else 
	{
		m_gameScene->addChild(bul);
		return bul;
	}
}

void PLAYER::hit(int damage)
{
	log("+++++++++++++ PLAYER HIT ++++++++++++++++");

	if (this->m_HP > damage)
	{
		this->m_HP -= damage;
		//this->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("PLAYER_HIT")));

	}
	else
	{
		this->m_HP = 0;
		this->down();
	}

	log("PLAYER HP: %d", m_HP);
}

void PLAYER::down()
{

	log("+++++++++++++++ HERO DOWN +++++++++++++");
	/*auto animation = Animate::create(
		AnimationCache::getInstance()->getAnimation("PLAYER_Down"));
	auto callFunc = CallFuncN::create([this](Node *node) 
	{
		for (auto item : this->m_weapon)
		{
			item->removeFromParentAndCleanup(true);
		}
		m_weapon.clear();
		node->removeFromParentAndCleanup(true);
	});*/
}

CommonData::WeaponType PLAYER::switchToNextWeapon()
{
	switchWeaponByIndex((m_currentWeaponIndex + 1) % (m_weaponCount));
	return m_currentWeaponType;
}

void PLAYER::addWeapon(WeaponType type)
{
	bool isEquiped = false;
	for (auto item : this->m_weapon)
	{
		if (item->getType() == type)
		{
			int bcount = 0;
			switch (type)
			{
			case HAND_GUN:
				bcount = HAND_GUN_BULLET_COUNT;
				break;
			case RIFLE_GUN:
				bcount = RIFLE_GUN_BULLET_COUNT;
				break;
			case SHOT_GUN:
				bcount = SHOT_GUN_BULLET_COUNT;
				break;
			case SNIPER_GUN:
				bcount = SNIPER_GUN_BULLET_COUNT;
				break;
			case RPG:
				bcount = RPG_BULLET_COUNT;
				break;
			default:
				break;
			}
			item->setBulletCount(item->getBulletCount() + bcount);
			isEquiped = true;
		}
	}
	if (!isEquiped)
	{
		auto newWeapon = WEAPON::create(type);
		m_gameScene->addChild(newWeapon);
		newWeapon->setVisible(false);		
		m_weaponCount += 1;
		//m_currentWeapon = newWeapon;
		m_weapon.pushBack(newWeapon);
		int bcount = 0;
		switch (type)
		{
		case HAND_GUN:
			bcount = HAND_GUN_BULLET_COUNT;
			break;
		case RIFLE_GUN:
			bcount = RIFLE_GUN_BULLET_COUNT;
			break;
		case SHOT_GUN:
			bcount = SHOT_GUN_BULLET_COUNT;
			break;
		case SNIPER_GUN:
			bcount = SNIPER_GUN_BULLET_COUNT;
			break;
		case RPG:
			bcount = RPG_BULLET_COUNT;
			break;
		default:
			break;
		}
		newWeapon->setBulletCount(bcount);
	}
}

void PLAYER::grabProperty(PropType type)
{
	switch (type)
	{
	case MEDKIT_PROP:
		this->m_HP += MEDKIT_ADD_HP;
		if (this->m_HP > PLAYER_HP) this->m_HP = PLAYER_HP;
		break;
	case GUN_PROP:
	{
		float random = CCRANDOM_0_1();
		if (0 <= random < RIFLE_GUN_PR)
		{
			this->addWeapon(RIFLE_GUN);
		}
		else if (RIFLE_GUN_PR <= random < RIFLE_GUN_PR + SHOT_GUN_PR)
		{
			this->addWeapon(SHOT_GUN);
		}
		else if (RIFLE_GUN_PR + SHOT_GUN_PR <= random < 1 - SNIPER_GUN_PR - RPG_PR)
		{
			this->addWeapon(SNIPER_GUN);
		}
		else
		{
			this->addWeapon(RPG);
		}
	}
	default:
		break;
	}
}

void PLAYER::render()
{
	this->m_currentWeapon->setPosition(this->getPosition());

	switch (this->m_direction)
	{
	case UP:
		if (m_isMoving == false) {
			m_isMoving = true;
			updateAnimation();
		}
		if (m_isRight) {
			this->m_currentWeapon->setFlippedX(false);
			this->m_currentWeapon->setRotation(-90);
		}
		else {
			this->m_currentWeapon->setFlippedX(true);
			this->m_currentWeapon->setRotation(90);
		}
		break;
	case R_UP:
		if (m_isMoving == false || m_isRight == false) 
		{
			if (m_isMoving == false) 
			{
				m_isMoving = true;
			}
			if (m_isRight == false) 
			{
				m_isRight = true;
				this->setSpriteFrame(IMG_PLAYER_STAY_RIGHT);
			}
			updateAnimation();
		}
		this->m_currentWeapon->setFlippedX(false);
		this->m_currentWeapon->setRotation(-45);
		break;
	case RIGHT:
		if (m_isMoving == false || m_isRight == false)
		{
			if (m_isMoving == false)
			{
				m_isMoving = true;
			}
			if (m_isRight == false)
			{
				m_isRight = true;
				this->setSpriteFrame(IMG_PLAYER_STAY_RIGHT);
			}
			updateAnimation();
		}
		this->m_currentWeapon->setFlippedX(false);
		this->m_currentWeapon->setRotation(0);
		break;
	case R_DOWN:
		if (m_isMoving == false || m_isRight == false)
		{
			if (m_isMoving == false)
			{
				m_isMoving = true;
			}
			if (m_isRight == false)
			{
				m_isRight = true;
				this->setSpriteFrame(IMG_PLAYER_STAY_RIGHT);
			}
			updateAnimation();
		}
		this->m_currentWeapon->setFlippedX(false);
		this->m_currentWeapon->setRotation(45);
		break;
	case DOWN:
		if (m_isMoving == false) {
			m_isMoving = true;
			updateAnimation();
		}
		if (m_isRight) {
			this->m_currentWeapon->setFlippedX(false);
			this->m_currentWeapon->setRotation(90);
		}
		else {
			this->m_currentWeapon->setFlippedX(true);
			this->m_currentWeapon->setRotation(-90);
		}
		
		break;
	case L_DOWN:
		if (m_isMoving == false || m_isRight == true)
		{
			if (m_isMoving == false)
			{
				m_isMoving = true;
			}
			if (m_isRight == true)
			{
				m_isRight = false;
				this->setSpriteFrame(IMG_PLAYER_STAY_LEFT);
			}
			updateAnimation();
		}
		this->m_currentWeapon->setFlippedX(true);
		this->m_currentWeapon->setRotation(-45);
		break;
	case LEFT:
		if (m_isMoving == false || m_isRight == true)
		{
			if (m_isMoving == false)
			{
				m_isMoving = true;
			}
			if (m_isRight == true)
			{
				m_isRight = false;
				this->setSpriteFrame(IMG_PLAYER_STAY_LEFT);
			}
			updateAnimation();
		}
		this->m_currentWeapon->setFlippedX(true);
		this->m_currentWeapon->setRotation(0);
		break;
	case L_UP:
		if (m_isMoving == false || m_isRight == true)
		{
			if (m_isMoving == false)
			{
				m_isMoving = true;
			}
			if (m_isRight == true)
			{
				m_isRight = false;
				this->setSpriteFrame(IMG_PLAYER_STAY_LEFT);
			}
			updateAnimation();
		}
		this->m_currentWeapon->setFlippedX(true);
		this->m_currentWeapon->setRotation(45);
		break;
	default:
	 /* this->m_currentWeapon->setRotation(0);
		this->setSpriteFrame(IMG_PLAYER_STAY_RIGHT);*/
		break;
	}
}

void PLAYER::render(CommonData::Direction _direction)
{

	this->m_currentWeapon->setPosition(this->getPosition());

	switch (_direction)
	{
	case UP:
		if (m_isRight) {
			this->m_currentWeapon->setFlippedX(false);
			this->m_currentWeapon->setRotation(-90);
		}
		else {
			this->m_currentWeapon->setFlippedX(true);
			this->m_currentWeapon->setRotation(90);
		}
		break;
	case R_UP:
		this->m_currentWeapon->setFlippedX(false);
		this->m_currentWeapon->setRotation(-45);
		break;
	case RIGHT:

		this->m_currentWeapon->setFlippedX(false);
		this->m_currentWeapon->setRotation(0);
		break;
	case R_DOWN:

		this->m_currentWeapon->setFlippedX(false);
		this->m_currentWeapon->setRotation(45);
		break;
	case DOWN:

		if (m_isRight) {
			this->m_currentWeapon->setFlippedX(false);
			this->m_currentWeapon->setRotation(90);
		}
		else {
			this->m_currentWeapon->setFlippedX(true);
			this->m_currentWeapon->setRotation(-90);
		}

		break;
	case L_DOWN:

		this->m_currentWeapon->setFlippedX(true);
		this->m_currentWeapon->setRotation(-45);
		break;
	case LEFT:

		this->m_currentWeapon->setFlippedX(true);
		this->m_currentWeapon->setRotation(0);
		break;
	case L_UP:
		this->m_currentWeapon->setFlippedX(true);
		this->m_currentWeapon->setRotation(45);
		break;
	default:
		this->m_currentWeapon->setRotation(0);
		this->setSpriteFrame(IMG_PLAYER_STAY_RIGHT);
		break;
	}


}

void PLAYER::updatePosition(Direction direction)
{
	//Point offset = nextPosition - this->getPosition();
	//Direction _direction = STAY;
	/*if (offset.x > 0)
	{
		if (offset.y > 0)
		{
			_direction = R_UP;
		}
		else if (offset.y < 0)
		{
			_direction = R_DOWN;
		}
		else if (offset.y == 0)
		{
			_direction = RIGHT;
		}
	}
	else if (offset.x < 0)
	{
		if (offset.y > 0)
		{
			_direction = L_UP;
		}
		else if (offset.y < 0)
		{
			_direction = L_DOWN;
		}
		else if (offset.y == 0)
		{
			_direction = LEFT;
		}
	}
	else if (offset.x == 0 && offset.y == 0)
	{
		_direction = STAY;
	}*/


	this->m_direction = direction;
	this->m_currentWeapon->setDirection(direction);

	
	this->render();
}

void PLAYER::updateAnimation()
{
	if (this->m_isRight == true) {
		auto ani = AnimationCache::getInstance()->getAnimation(ANI_PLAYER_WALK_RIGHT);
		auto animator = Animate::create(ani);
		this->stopAllActions();
		this->runAction(animator);
	}
	else {
		auto ani = AnimationCache::getInstance()->getAnimation(ANI_PLAYER_WALK_LEFT);
		auto animator = Animate::create(ani);
		this->stopAllActions();
		this->runAction(animator);
	}

}

void PLAYER::stopMove()
{
	m_isMoving = false;
	this->stopAllActions();
	this->m_direction = STAY;

}

CommonData::WeaponType  PLAYER::switchWeaponByIndex(int index)
{
	auto _weaponDir = this->getDirection();

	if (m_currentWeapon != nullptr)
	{
		m_currentWeapon->setVisible(false);
		_weaponDir = RIGHT;
	}

	if (index >= 0 && index < m_weaponCount && index != m_currentWeaponIndex)
	{
		_weaponDir = m_currentWeapon->getDirection();
		m_currentWeaponIndex = index;
		m_currentWeapon = m_weapon.at(index);
	}
	else
	{
		if (m_currentWeapon != nullptr) {
			_weaponDir = m_currentWeapon->getDirection();
		}
		m_currentWeaponIndex = 0;
		m_currentWeapon = m_weapon.at(0);
	}

	m_currentWeaponType = m_currentWeapon->getType();
	m_currentWeapon->setVisible(true);
	m_currentWeapon->setDirection(_weaponDir);
	render(_weaponDir);
	return m_currentWeaponType;
}
