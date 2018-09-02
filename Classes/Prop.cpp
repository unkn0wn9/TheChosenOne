#include "Prop.h"
using namespace CommonData;
PROP::PROP()
	:m_type(MEDKIT_PROP),
	m_isOpen(false)
{
}
PROP::~PROP()
{
}
PROP *PROP::create(PropType type) 
{
	auto prop= new PROP();
	if (prop && prop->init(type)) 
	{
		prop->autorelease();
		return prop;
	}
	delete prop;
	prop = nullptr;
	return nullptr;
}

bool PROP::init(PropType type) 
{
	this->m_type = type;

	Sprite::initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("box_close.png"));

	auto physicsBody = PhysicsBody::createBox(this->getBoundingBox().size, PhysicsMaterial(0.1f, 1.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setGravityEnable(false);

	physicsBody->setCategoryBitmask(PROP_CAT_BITMASK);
	physicsBody->setCollisionBitmask(PROP_COL_BITMASK);
	physicsBody->setContactTestBitmask(PROP_CON_BITMASK);

	this->setTag(PROP_TAG);
	this->addComponent(physicsBody);

	/*switch(type)
	{
	case MEDKIT_PROP:
		Sprite::initWithSpriteFrameName("MEDKIT_PROP");
	case GUN_PROP:
		Sprite::initWithSpriteFrameName("GUN_PROP");
	default:
		break;
	}*/
	return true;
}

void PROP::openBox()
{

	this->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("box_open.png"));

}
