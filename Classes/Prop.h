#pragma once
#include "cocos2d.h"
#include "CommonData.h"

USING_NS_CC;

class PROP : public cocos2d::Sprite
{

public:
	PROP();
	~PROP();
	static PROP* create(CommonData::PropType = CommonData::PropType::MEDKIT_PROP);
	bool init(CommonData::PropType = CommonData::PropType::MEDKIT_PROP);

	bool m_isOpen;

	void openBox();

	CC_SYNTHESIZE(CommonData::PropType, m_type, Type);
};