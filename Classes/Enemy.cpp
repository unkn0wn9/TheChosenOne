#include "Enemy.h"

using namespace CommonData;

ENEMY::ENEMY() 
	:m_type(SMALL_ENEMY),
	m_HP(1),
	m_score(1),
	m_damage(1),
	m_direction(Direction::STAY),
	m_attackLock(true)
{
	//默认是0血的小僵尸
}

ENEMY::~ENEMY()
{
}



ENEMY* ENEMY::create(EnemyType t)
{
	auto enemy = new ENEMY();
	if (enemy && enemy->init(t))
	{
		enemy->autorelease();
		return enemy;
	}
	delete enemy;
	enemy = nullptr;
	return nullptr;

}

bool ENEMY::init(EnemyType type) 
{
	PhysicsBody *physicsBody = nullptr;
	this->m_type = type;
	m_direction = RIGHT;
	switch (type) 
	{
	case SMALL_ENEMY:
		this->m_HP = SMALL_ENEMY_HP;
		this->m_damage = SMALL_ENEMY_HIT;
		this->m_score = SMALL_ENEMY_SCORE;
		this->m_speed = SMALL_ENEMY_STEP;
		cocos2d::Sprite::initWithSpriteFrameName("sEnemy_left1.png"); 
		physicsBody = PhysicsBody::createBox(this->getBoundingBox().size, PhysicsMaterial(0.1f, 1.0f, 0.0f));
		physicsBody->setVelocityLimit(m_speed);
		
		{
			auto ani = AnimationCache::getInstance()->getAnimation(ANI_S_ENEMY_RIGHT);
			auto animator = Animate::create(ani);
			this->stopAllActions();
			this->runAction(animator);
		}

		break;
	case  MIDDLE_ENEMY:
		this->m_HP = MIDDLE_ENEMY_HP;
		this->m_damage = MIDDLE_ENEMY_HIT;
		this->m_score = MIDDLE_ENEMY_SCORE;
		this->m_speed = MIDDLE_ENEMY_STEP;
		cocos2d::Sprite::initWithSpriteFrameName("mEnemy_left1.png");
		physicsBody = PhysicsBody::createBox(this->getBoundingBox().size, PhysicsMaterial(0.1f, 1.0f, 0.0f));
		physicsBody->setVelocityLimit(m_speed);
		{
			auto ani = AnimationCache::getInstance()->getAnimation(ANI_M_ENEMY_RIGHT);
			auto animator = Animate::create(ani);
			this->stopAllActions();
			this->runAction(animator);
		}
		break;
	case  BIG_ENEMY:
		this->m_HP = MIDDLE_ENEMY_HP;
		this->m_damage = MIDDLE_ENEMY_HIT;
		this->m_score = MIDDLE_ENEMY_SCORE;
		this->m_speed = MIDDLE_ENEMY_STEP;
		cocos2d::Sprite::initWithSpriteFrameName("boss_1.png");
		physicsBody = PhysicsBody::createBox(this->getBoundingBox().size, PhysicsMaterial(0.1f, 1.0f, 0.0f));
		physicsBody->setVelocityLimit(m_speed);
		{//大僵尸的动画
			Animation* animation;
			animation = AnimationCache::getInstance()->getAnimation(ANI_BOSS_WALK);
			this->runAction(Animate::create(animation));
		}
		break;
	default:
		break;
	}

	physicsBody->setDynamic(true);
	physicsBody->setGravityEnable(false);
	physicsBody->setRotationEnable(false);

	physicsBody->setCategoryBitmask(ENEMY_CAT_BITMASK);
	physicsBody->setCollisionBitmask(ENEMY_COL_BITMASK);
	physicsBody->setContactTestBitmask(ENEMY_CON_BITMASK);

	this->addComponent(physicsBody);
	this->setTag(ENEMY_TAG);

	this->setDirection(RIGHT);

	return true;
}


void ENEMY::down() {

	this->getPhysicsBody()->setVelocity(Vec2::ZERO);

	this->stopAllActions();
	this->getPhysicsBody()->setCategoryBitmask(0x00);

	switch (this->m_type) 
	{
	case SMALL_ENEMY:
		this->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sEnemy_dead.png"));
		break;
	case MIDDLE_ENEMY:
		this->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mEnemy_dead.png"));
		break;
	case BIG_ENEMY:
		this->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("boss_dead.png"));
		break;
	default:
		break;
	}
}

void ENEMY::attackLock()
{
	m_attackLock = false;
}

void ENEMY::attackUnLock()
{
	m_attackLock = true;
}

void ENEMY::updateVel(Vec2 _player_position)
{
	auto _vec = _player_position - this->getPosition();

	/*if (abs(_vec.x) < 40 && abs(_vec.y) < 40) {
		_vec *= 2;
	}*/

	if (_vec.x < 0 && m_direction != LEFT) {

		m_direction = LEFT;

		switch (m_type)
		{
		case SMALL_ENEMY:
		{
			auto ani = AnimationCache::getInstance()->getAnimation(ANI_S_ENEMY_LEFT);
			auto animator = Animate::create(ani);
			this->stopAllActions();
			this->runAction(animator);
		}
			break;
		case MIDDLE_ENEMY:
		{
			auto ani = AnimationCache::getInstance()->getAnimation(ANI_M_ENEMY_LEFT);
			auto animator = Animate::create(ani);
			this->stopAllActions();
			this->runAction(animator);
		}
		default:
			break;
		}
		
	}
	else if (_vec.x > 0 && m_direction != RIGHT) {
		m_direction = RIGHT;

		switch (m_type)
		{
		case SMALL_ENEMY:
		{
			auto ani = AnimationCache::getInstance()->getAnimation(ANI_S_ENEMY_RIGHT);
			auto animator = Animate::create(ani);
			this->stopAllActions();
			this->runAction(animator);
		}
		break;
		case MIDDLE_ENEMY:
		{
			auto ani = AnimationCache::getInstance()->getAnimation(ANI_M_ENEMY_RIGHT);
			auto animator = Animate::create(ani);
			this->stopAllActions();
			this->runAction(animator);
		}
		default:
			break;
		}

	}


	auto enemyVec = m_speed / abs(_vec.getLength()) * _vec;


	this->getPhysicsBody()->setVelocity(enemyVec);

}

void ENEMY::setDirection(CommonData::Direction direction)
{
	m_direction = direction;

	float x = 0, y = 0;

	switch (m_direction)
	{
	case STAY: break;
	case UP:
		y = m_speed;
		break;
	case DOWN:
		y = -m_speed;
		break;
	case LEFT:
		x = -m_speed;
		break;
	case RIGHT:
		y = m_speed;
		break;
	case R_UP:
		x = m_speed * 0.7071;
		y = x;
		break;
	case R_DOWN:
		x = m_speed * 0.7071;
		y = -x;
		break;
	case L_UP:
		y = m_speed * 0.7071;
		x = -y;
		break;
	case L_DOWN:
		x = -m_speed * 0.7071;
		y = x;
		break;
	default:
		break;
	}

	this->getPhysicsBody()->setVelocity(Vec2(x, y));

}


bool ENEMY::hit(int hit_HP)
{
	this->m_HP -= hit_HP;
	
	if (m_HP <= 0) {
		down();
		return true;
	}

	//auto ani = AnimationCache::getInstance()->getAnimation(ANI_ENEMY_HIT);
	//this->runAction(Animate::create(ani));

	return false;
	/*switch (this->m_type)
	{
	case MIDDLE_ENEMY:
		animation = AnimationCache::getInstance()->getAnimation("MiddleEnemyHit");
		break;
	case BIG_ENEMY:
		animation = AnimationCache::getInstance()->getAnimation("BigEnemyHit");

		break;
	default:
		break;
	}*/

	
}

void ENEMY::attack(PLAYER* player) 
{
//	//三个僵尸八个方向
//	Animation* animation;
//	switch (this->m_direction)
//	{
//	case LEFT:
//		switch (this->m_type) 
//		{
//		case SMALL_ENEMY:
//			animation = AnimationCache::getInstance()->getAnimation("SmallEnemyDown");
//			break;
//		case MIDDLE_ENEMY:
//			animation = AnimationCache::getInstance()->getAnimation("MiddleEnemyDown");
//			break;
//		case BIG_ENEMY:
//			animation = AnimationCache::getInstance()->getAnimation("BigEnemyDown");
//			break;
//		default:
//			break;
//		}
//		break;
//
//	case L_UP:
//		switch (this->m_type) 
//		{
//		case SMALL_ENEMY:
//			animation = AnimationCache::getInstance()->getAnimation("SmallEnemyDown");
//			break;
//		case MIDDLE_ENEMY:
//			animation = AnimationCache::getInstance()->getAnimation("MiddleEnemyDown");
//			break;
//		case BIG_ENEMY:
//			animation = AnimationCache::getInstance()->getAnimation("BigEnemyDown");
//			break;
//		default:
//			break;
//		}
//		break;
//
//
//	case UP:
//		switch (this->m_type)
//		{
//		case SMALL_ENEMY:
//			animation = AnimationCache::getInstance()->getAnimation("SmallEnemyDown");
//			break;
//		case MIDDLE_ENEMY:
//			animation = AnimationCache::getInstance()->getAnimation("MiddleEnemyDown");
//			break;
//		case BIG_ENEMY:
//			animation = AnimationCache::getInstance()->getAnimation("BigEnemyDown");
//			break;
//		default:
//			break;
//		}
//		break;
//
//
//
//	case R_UP:
//		switch (this->m_type) 
//		{
//		case SMALL_ENEMY:
//			animation = AnimationCache::getInstance()->getAnimation("SmallEnemyDown");
//			break;
//		case MIDDLE_ENEMY:
//			animation = AnimationCache::getInstance()->getAnimation("MiddleEnemyDown");
//			break;
//		case BIG_ENEMY:
//			animation = AnimationCache::getInstance()->getAnimation("BigEnemyDown");
//			break;
//		default:
//			break;
//		}
//		break;
//
//
//
//	case RIGHT:
//		switch (this->m_type)
//		{
//		case SMALL_ENEMY:
//			animation = AnimationCache::getInstance()->getAnimation("SmallEnemyDown");
//			break;
//		case MIDDLE_ENEMY:
//			animation = AnimationCache::getInstance()->getAnimation("MiddleEnemyDown");
//			break;
//		case BIG_ENEMY:
//			animation = AnimationCache::getInstance()->getAnimation("BigEnemyDown");
//			break;
//		default:
//			break;
//		}
//		break;
//
//
//
//	case R_DOWN:
//		switch (this->m_type) 
//		{
//		case SMALL_ENEMY:
//			animation = AnimationCache::getInstance()->getAnimation("SmallEnemyDown");
//			break;
//		case MIDDLE_ENEMY:
//			animation = AnimationCache::getInstance()->getAnimation("MiddleEnemyDown");
//			break;
//		case BIG_ENEMY:
//			animation = AnimationCache::getInstance()->getAnimation("BigEnemyDown");
//			break;
//		default:
//			break;
//		}
//		break;
//
//
//
//
//
//	case DOWN:
//		switch (this->m_type) {
//		case SMALL_ENEMY:
//			animation = AnimationCache::getInstance()->getAnimation("SmallEnemyDown");
//			break;
//		case MIDDLE_ENEMY:
//			animation = AnimationCache::getInstance()->getAnimation("MiddleEnemyDown");
//			break;
//		case BIG_ENEMY:
//			animation = AnimationCache::getInstance()->getAnimation("BigEnemyDown");
//			break;
//		default:
//			break;
//		}
//		break;
//
//
//
//
//
//	case L_DOWN:
//		switch (this->m_type)
//		{
//		case SMALL_ENEMY:
//			animation = AnimationCache::getInstance()->getAnimation("SmallEnemyDown");
//			break;
//		case MIDDLE_ENEMY:
//			animation = AnimationCache::getInstance()->getAnimation("MiddleEnemyDown");
//			break;
//		case BIG_ENEMY:
//			animation = AnimationCache::getInstance()->getAnimation("BigEnemyDown");
//			break;
//		default:
//			break;
//		}
//		break;
//	}
//	
//	//	animation->setDelayPerUnit(0.2);
//	auto animate = cocos2d::Animate::create(animation);
//	//CallFunc是动作，允许我们的代码作为动作执行
//	//Sequence是动作，作用是将多个动作按顺序依次执行
//	auto callFuncN = cocos2d::CallFuncN::create([](Node* node) {
//		//Node参数是这个动作的执行者
//		//将自己从父容器删除并清除(定时器，动作)
//		node->removeFromParentAndCleanup(true);
//	});
//
//	this->runAction(cocos2d::Sequence::create(animate, callFuncN, NULL));
}