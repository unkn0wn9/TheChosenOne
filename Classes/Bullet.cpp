#include "Bullet.h"

using namespace CommonData;
BULLET::BULLET()
	:m_damage(1),
	m_type(BulletType::GUN_BULLET),
	m_speed(0),
	m_range(0),
	m_direction(Direction::STAY),
	m_distance(0)
{
}
BULLET::~BULLET()
{

}
BULLET* BULLET::create(BulletType type)
{
	auto bullet = new BULLET();
	if (bullet && bullet->init(type))
	{
		bullet->autorelease();
		return bullet;
	}
	delete bullet;
	bullet = nullptr;
	return nullptr;
}

bool BULLET::init(BulletType type)
{
	this->m_type = type;
	switch (this->m_type)
	{
	case GUN_BULLET:
		Sprite::initWithSpriteFrameName("gunBullet .png");
		break;
	case RPG_BULLET:
		Sprite::initWithSpriteFrameName("RPGBbullet.png");
		break;
	default:
		break;
	}


	auto physicsBody = PhysicsBody::createBox(this->getBoundingBox().size, PhysicsMaterial(0.2f, 1.0f, 0.0f));
	physicsBody->setDynamic(true);
	physicsBody->setGravityEnable(false);

	physicsBody->setCategoryBitmask(BULLET_CAT_BITMASK);
	physicsBody->setCollisionBitmask(BULLET_COL_BITMASK);
	physicsBody->setContactTestBitmask(BULLET_CON_BITMASK);

	this->setTag(BULLET_TAG);

	this->addComponent(physicsBody);


	return true;
}


void BULLET::setSpeed(float speed)
{
	m_speed = speed;

	float x = 0, y = 0;

	switch (m_direction)
	{
	case STAY: break;
	case UP: 
		this->setRotation(-90);
		y = m_speed;
		break;
	case DOWN:
		this->setRotation(90);
		y = -m_speed;
		break;
	case LEFT:
		this->setRotation(180);
		x = -m_speed;
		break;
	case RIGHT:
		this->setRotation(0);
		x = m_speed;
		break;
	case R_UP:
		this->setRotation(-45);
		x = m_speed * 0.7071;
		y = x;
		break;
	case R_DOWN:
		this->setRotation(45);
		x = m_speed * 0.7071;
		y = -x;
		break;
	case L_UP:
		this->setRotation(-135);
		y = m_speed * 0.7071;
		x = -y;
		break;
	case L_DOWN:
		this->setRotation(135);
		x = - m_speed * 0.7071;
		y = x;
		break;
	default:
		break;
	}

	this->getPhysicsBody()->setVelocity(Vec2(x, y));

}

/*
void BULLET::render()
{
	//if (m_startPosition.getDistance(this->getPosition()) >= m_distance)
	//{
	//	return;
	//}

	switch (this->m_direction)
	{
	case UP:
		this->setRotation(0);
		this->setPositionY(this->getPositionY() + this->m_step);
		break;
	case R_UP:
		this->setRotation(45);
		this->setPosition(this->getPosition() + Point(this->m_step, this->m_step));
		break;
	case RIGHT:
		this->setRotation(90);
		this->setPositionX(this->getPositionX() + this->m_step);
		break;
	case R_DOWN:
		this->setRotation(135);
		this->setPosition(this->getPosition() + Point(this->m_step, -this->m_step));
		break;
	case DOWN:
		this->setRotation(180);
		this->setPositionY(this->getPositionY() - this->m_step);
		break;
	case L_DOWN:
		this->setRotation(225);
		this->setPosition(this->getPosition() + Point(-this->m_step, -this->m_step));
		break;
	case LEFT:
		this->setRotation(270);
		this->setPositionX(this->getPositionX() - this->m_step);
		break;
	case L_UP:
		this->setRotation(315);
		this->setPosition(this->getPosition() + Point(-this->m_step, this->m_step));
		break;
	default: 
		this->setRotation(0);
		break;
	}
}
*/