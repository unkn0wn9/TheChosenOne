#pragma once
#include "cocos2d.h"
#include "Player.h"
#include "CommonData.h"

USING_NS_CC;
class ENEMY : public Sprite
{
public:
	ENEMY();
	~ENEMY();
	static ENEMY* create(CommonData::EnemyType = CommonData::EnemyType::SMALL_ENEMY);
	bool init(CommonData::EnemyType = CommonData::EnemyType::SMALL_ENEMY);
	void attack(PLAYER*);
	bool hit(int);
	void down();

	void attackLock();
	void attackUnLock();
	bool getAttackLock() { return m_attackLock; };

	void updateVel(Vec2);

	void setDirection(CommonData::Direction);
	inline CommonData::Direction getDirection() const{ return this->m_direction; };

	CC_SYNTHESIZE(CommonData::EnemyType, m_type, Type);
	CC_SYNTHESIZE(int, m_HP, HP);
	CC_SYNTHESIZE(int, m_score, Score);
	CC_SYNTHESIZE(float, m_speed, Speed);
	CC_SYNTHESIZE(int, m_damage, Damage);

private:

	bool m_attackLock;

	CommonData::Direction m_direction;
};