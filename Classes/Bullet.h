#pragma once
#include "cocos2d.h"
#include "CommonData.h"

USING_NS_CC;

class BULLET :public Sprite
{
public:
	BULLET();
	~BULLET();
	static BULLET* create(CommonData::BulletType = CommonData::BulletType::GUN_BULLET);
	bool init(CommonData::BulletType = CommonData::BulletType::GUN_BULLET);

	CC_SYNTHESIZE(CommonData::Direction, m_direction, Direction);
	CC_SYNTHESIZE(int, m_damage, Damage);
	CC_SYNTHESIZE(CommonData::BulletType, m_type, Type);
	CC_SYNTHESIZE(float, m_range, Range);
	CC_SYNTHESIZE(float, m_distance, Distance);

	inline float getSpeed() const { return this->m_speed; };
	void setSpeed(float);

	//void render();
private:
	Point m_startPosition;
	float m_speed;
};
