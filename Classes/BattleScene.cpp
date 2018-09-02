#include "BattleScene.h"
#include "JoyStick.h"
#include "CommonData.h"
#include "SimpleAudioEngine.h"
#include "GameOverScene.h"

USING_NS_CC;
using namespace CommonData;

Scene* BattleScene::createScene() 
{
	return BattleScene::create();
}

bool BattleScene::init()
{
	if (!Scene::initWithPhysics()) {
		return false;
	}

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("character.plist");

	// 背景音乐
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("game.wav", true);

	// 加载瓦片地图
	_tileMap = TMXTiledMap::create("map/snow.tmx");
	_blocks = _tileMap->getLayer("blocks");
	for (int i = 0; i <= _tileMap->getMapSize().width-1; i++)
		for (int j = 0; j <= _tileMap->getMapSize().height-1; j++)
		{
			if (_blocks->getTileGIDAt(Point(i, j)) > 0) {

				auto tilesp = _blocks->getTileAt(Point(i, j));

				auto phsicsBody = PhysicsBody::createBox(tilesp->getBoundingBox().size, PhysicsMaterial(0.1f, 0.1f, 0.0f));

				phsicsBody->setDynamic(false);
				phsicsBody->setGravityEnable(false);
				phsicsBody->setCategoryBitmask(OBS_CAT_BITMASK);
				phsicsBody->setCollisionBitmask(OBS_COL_BITMASK);
				phsicsBody->setContactTestBitmask(OBS_CON_BITMASK);

				tilesp->setTag(OBS_TAG);

				tilesp->addComponent(phsicsBody);
			}
		}
	addChild(_tileMap, 0, 100);


	// 物理外框
	auto phEdge = PhysicsBody::createEdgeBox(_tileMap->getContentSize());
	auto edgeShape = Node::create();
	edgeShape->setPhysicsBody(phEdge);
	edgeShape->setPosition(_tileMap->getContentSize() / 2);
	edgeShape->getPhysicsBody()->setCategoryBitmask(EDGE_CAT_BITMASK);
	edgeShape->getPhysicsBody()->setCollisionBitmask(EDGE_COL_BITMASK);
	edgeShape->getPhysicsBody()->setContactTestBitmask(EDGE_CON_BITMASK);
	edgeShape->setTag(EDGE_TAG);
	addChild(edgeShape);

	_player = PLAYER::create();
	_player->setGameScene(this);
	_player->setAnchorPoint(Vec2(0.5, 0.5));
	_player->setPosition(Point(ORIGIN.x + _tileMap->getContentSize().width, ORIGIN.y + _tileMap->getContentSize().height) / 2);
	addChild(_player, 1, PLAYER_TAG);

	_player->addWeapon(HAND_GUN);
	_player->switchToNextWeapon();

	rocker = JoyStick::create();
	rocker->setPosition(Point(0, 0));
	rocker->m_player = _player;
	this->addChild(rocker);

	initEnemy();
	updateProp();
	//auto enemy = ENEMY::create();
	//enemy->setPosition(Vec2::ZERO);
	//m_enemies.pushBack(enemy);

	auto listener = EventListenerCustom::create(AnimationFrameDisplayedNotification,
		[this](EventCustom *event)
	{
		//log("++++EventListenerCustom++++");
		AnimationFrame::DisplayedEventInfo * info = static_cast<AnimationFrame::DisplayedEventInfo*>(event->getUserData());
		info->target->setLocalZOrder(info->userInfo->at("zorder").asInt());
	});

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	/*开启摇杆检查调度*/
	schedule(CC_CALLBACK_1(BattleScene::schedulePos, this), "POS");

	schedule(schedule_selector(BattleScene::updateEnemyDirection), 1.0f);

	return true;
}



/*让我们的精灵按照摇杆的力度移动距离*/
void BattleScene::schedulePos(float dt)
{
	/*获取摇杆到圆点的位置*/
	auto dis = rocker->getRocker()->getPosition().distance(rocker->getRockerBg()->getPosition());
	dis /= 20.0;
	auto hero = (PLAYER *)getChildByTag(PLAYER_TAG);
	float angle = rocker->getAngle();
	auto mapSize = _tileMap->getContentSize();
	auto aimPoint = hero->getPosition();

	if (hero->getHP() <= 0) {

		hero->stopAllActions();
		hero->setRotation(-90);

		auto gameOverScene = GameOverScene::createScene(_player->getScore());
		Director::getInstance()->replaceScene(gameOverScene);

	}


	switch (rocker->getDir()) 
	{
	case Direction::UP:
		aimPoint.y = MIN(hero->getPositionY() + dis, mapSize.height);
		break;
	case Direction::DOWN:
		aimPoint.y = MAX(hero->getPositionY() - dis, 0);
		break;
	case Direction::LEFT:
		aimPoint.x = MAX(hero->getPositionX() - dis, 0);
		break;
	case Direction::RIGHT:
		aimPoint.x = MIN(hero->getPositionX() + dis, mapSize.width);
		break;
	case Direction::L_UP:
		aimPoint = hero->getPosition() + Vec2(dis*cos(angle), dis*sin(angle));
		aimPoint.x = MAX(aimPoint.x, 0);
		aimPoint.y = MIN(aimPoint.y, mapSize.height);
		break;
	case Direction::R_UP:
		aimPoint = hero->getPosition() + Vec2(dis*cos(angle), dis*sin(angle));
		aimPoint.x = MIN(aimPoint.x, mapSize.width);
		aimPoint.y = MIN(aimPoint.y, mapSize.height);
		break;
	case Direction::L_DOWN:
		aimPoint = hero->getPosition() + Vec2(dis*cos(angle), -dis * sin(angle));
		aimPoint.x = MAX(aimPoint.x, 0);
		aimPoint.y = MAX(aimPoint.y, 0);
		break;
	case Direction::R_DOWN:
		aimPoint = hero->getPosition() + Vec2(dis*cos(angle), -dis * sin(angle));
		aimPoint.x = MIN(aimPoint.x, mapSize.width);
		aimPoint.y = MAX(aimPoint.y, 0);
		break;
	case Direction::STAY:
		hero->stopMove();
		break;
	default:
		break;
	}
	if (!checkBlock(aimPoint)) {
		hero->setPosition(aimPoint);
		if (rocker->getDir() != STAY) {
			hero->updatePosition(rocker->getDir());
		}
	}
	setViewpointCenter(hero->getPosition());
}


void BattleScene::setViewpointCenter(Point position)
{
	//如果精灵在屏幕中央的左边或者右边，x的值就是精灵当前的x值，否则x的值就是屏幕宽度的一半。
	int x = MAX(position.x, VISIBLE_SIZE.width / 2);
	int y = MAX(position.y, VISIBLE_SIZE.height / 2);

	//获取整个地图的尺寸
	Size mapSize = _tileMap->getContentSize();

	//获取每一个图块的宽高
	Size tileSize = _tileMap->getTileSize();

	//mapSize.width是地图的x轴方向上有多少个瓦片
	//mapSize.height是地图的y轴方向上有多少个瓦片

	//重新规划x的值。
	x = MIN(x, mapSize.width - VISIBLE_SIZE.width / 2);
	y = MIN(y, mapSize.height - VISIBLE_SIZE.height / 2);

	//获取屏幕中心点的位置
	Point centerPoint = Point(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2);

	//重新规划的位置
	Point actualPoint = Point(x + ORIGIN.x, y + ORIGIN.y);

	//地图最终要移动到的位置
	Point viewPoint = centerPoint - actualPoint;

	rocker->setPosition(actualPoint - centerPoint);

	//重新规划当前视图的位置。
	this->setPosition(viewPoint);
}

bool BattleScene::checkBlock(Vec2 point)
{
	auto tilePoint = tileCoordFromPosition(point);
	auto tileGid = _blocks->getTileGIDAt(tilePoint);
	if (tileGid > 0) {
		log("true World: %f %f", point.x, point.y);
		log("true Tile: %f %f", tilePoint.x, tilePoint.y);
		return true;
	}
	else {
		log("false World: %f %f", point.x, point.y);
		log("false Tile: %f %f", tilePoint.x, tilePoint.y);
		return false;
	}
}


Point BattleScene::tileCoordFromPosition(Point pos)
{
	int x = pos.x / (_tileMap->getContentSize().width / _tileMap->getMapSize().width);
	int y = (_tileMap->getContentSize().height - pos.y) / (_tileMap->getContentSize().height / _tileMap->getMapSize().height);
	if (x >= _tileMap->getMapSize().width) x = _tileMap->getMapSize().width - 1;
	if (x < 0) x = 0;
	if (y >= _tileMap->getMapSize().height) y = _tileMap->getMapSize().height - 1;
	if (y < 0) y = 0;
	return Point(x, y);
}

void BattleScene::initEnemy()
{
	Vec2 enemyDoor1 = positionCoordFromTile(Vec2(144, 33));
	Vec2 enemyDoor2 = positionCoordFromTile(Vec2(16, 95));
	Vec2 enemyDoor3 = positionCoordFromTile(Vec2(4, 64));
	Vec2 enemyDoor4 = positionCoordFromTile(Vec2(4, 3));

	createEnemyByPoint(enemyDoor1);
	createEnemyByPoint(enemyDoor2);
	createEnemyByPoint(enemyDoor3);
	createEnemyByPoint(enemyDoor4);

}


void BattleScene::createEnemyByPoint(Vec2 createPoint)
{

	for (int i = 0; i < ENEMY_S_NUMBER / 4; i++) {
		auto _enemy = ENEMY::create(SMALL_ENEMY);
		this->addChild(_enemy);
		_enemy->setPosition(createPoint);
		m_enemies.pushBack(_enemy);
	}
	for (int i = 0; i < ENEMY_M_NUMBER / 4; i++) {
		auto _enemy = ENEMY::create(MIDDLE_ENEMY);
		this->addChild(_enemy);
		_enemy->setPosition(createPoint);
		m_enemies.pushBack(_enemy);
	}
	for (int i = 0; i < ENEMY_BOSS_NUMBER; i++) {
		auto _enemy = ENEMY::create(BIG_ENEMY);
		this->addChild(_enemy);
		_enemy->setPosition(createPoint);
		m_enemies.pushBack(_enemy);
	}

}

void BattleScene::updateProp() {

	auto _mapSize = this->_tileMap->getContentSize();

	for (int i = 0; i < PROP_BOX_NUMBER; i++) {
		float _x = CCRANDOM_0_1() * _mapSize.width;
		float _y = CCRANDOM_0_1() * _mapSize.height;

		PROP *_prop = nullptr;

		if (CCRANDOM_0_1() > 0.7) {
			_prop = PROP::create(PropType::MEDKIT_PROP);
		}
		else {
			_prop = PROP::create(PropType::GUN_PROP);
		}

		this->addChild(_prop);
		_prop->setPosition(Vec2(_x + ORIGIN.x, _y + ORIGIN.y));
	}
}

void BattleScene::onEnter()
{
	Scene::onEnter();

	//添加监听器
	auto contactListener = EventListenerPhysicsContact::create();

	//设置监听器的碰撞开始函数
	contactListener->onContactBegin = CC_CALLBACK_1(BattleScene::ContactBegin, this);
	contactListener->onContactPostSolve = CC_CALLBACK_1(BattleScene::ContactPost, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(BattleScene::ContactSeparate, this);

	//添加到事件分发器中
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

bool BattleScene::ContactBegin(PhysicsContact & contact)
{
	bool ret = true;

	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA && nodeB)
	{
		if (nodeA->getTag() == OBS_TAG && nodeB->getTag() == BULLET_TAG)
		{
			nodeB->removeFromParentAndCleanup(true);
			this->removeChild(nodeB);
			ret = false;
		}
		else if (nodeA->getTag() == BULLET_TAG && nodeB->getTag() == OBS_TAG)
		{
			nodeA->removeFromParentAndCleanup(true);
			this->removeChild(nodeA);
			ret = false;
		}
		else if (nodeA->getTag() == BULLET_TAG && nodeB->getTag() == EDGE_TAG) {
			nodeA->removeFromParentAndCleanup(true);
			this->removeChild(nodeA);
			ret = false;
		}
		else if (nodeA->getTag() == EDGE_TAG && nodeB->getTag() == BULLET_TAG) {
			nodeB->removeFromParentAndCleanup(true);
			this->removeChild(nodeB);
			ret = false;
		}
		else if (nodeA->getTag() == PLAYER_TAG && nodeB->getTag() == PROP_TAG) {

			auto _prop = (PROP *)nodeB;

			if (_prop->m_isOpen == false) {
				_prop->openBox();
				_player->grabProperty(_prop->getType());

				_prop->m_isOpen = true;
				m_openedProps.pushBack(_prop);
				switch (_prop->getType())
				{
				case MEDKIT_PROP:
					this->rocker->sendMessage("Your HP ++");
					this->rocker->setHp(_player->getHP());
					break;
				case GUN_PROP:
					this->rocker->sendMessage("You Got Firearms Supplement");
					break;
				default:
					break;
				}
				
				_prop->getPhysicsBody()->setContactTestBitmask(0x00);
			}
			//ret = false;

		}
		else if (nodeA->getTag() == PROP_TAG && nodeB->getTag() == PLAYER_TAG) {
			auto _prop = (PROP *)nodeA;

			if (_prop->m_isOpen == false) {
				_prop->openBox();
				_player->grabProperty(_prop->getType());

				_prop->m_isOpen = true;
				m_openedProps.pushBack(_prop);
				switch (_prop->getType())
				{
				case MEDKIT_PROP:
					this->rocker->sendMessage("Your HP ++");
					this->rocker->setHp(_player->getHP());
					break;
				case GUN_PROP:
					this->rocker->sendMessage("You Got Firearms Supplement");
					break;
				default:
					break;
				}
				_prop->getPhysicsBody()->setContactTestBitmask(0x00);
			}

			//ret = false;
		}
	}

	return ret;
}

bool BattleScene::ContactPost(PhysicsContact & contact)
{
	bool ret = true;

	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA && nodeB)
	{
		if (nodeA->getTag() == ENEMY_TAG && nodeB->getTag() == BULLET_TAG)
		{
			ret = true;

			auto _enemy = (ENEMY *)nodeA;
			nodeB->removeFromParentAndCleanup(true);
			this->removeChild(nodeB);
			if (_enemy->hit(_player->getCurWeapon()->getBulletDamage())) {
				_player->setScore(_player->getScore() + _enemy->getScore());

				m_enemies.eraseObject(_enemy);

				scheduleOnce([_enemy, this](float dt) {
					_enemy->removeFromParentAndCleanup(true);
					this->removeChild(_enemy);
				}, 1.5f, "ENEMYDIE");

			}
		}
		else if (nodeA->getTag() == BULLET_TAG && nodeB->getTag() == ENEMY_TAG)
		{
			ret = true;

			auto _enemy = (ENEMY *)nodeB;
			nodeA->removeFromParentAndCleanup(true);
			this->removeChild(nodeA);
			if (_enemy->hit(_player->getCurWeapon()->getBulletDamage())) {
				_player->setScore(_player->getScore() + _enemy->getScore());
				m_enemies.eraseObject(_enemy);

				scheduleOnce([_enemy, this](float dt) {
					_enemy->removeFromParentAndCleanup(true);
					this->removeChild(_enemy);
				}, 1.5f, "ENEMYDIE2");

			}
		}
		else if (nodeA->getTag() == PLAYER_TAG && nodeB->getTag() == ENEMY_TAG) {

			ret = true;

			auto _enemy = (ENEMY *)nodeB;

			if (_enemy->getAttackLock() == false) {
				return true;
			}
			else {
				_enemy->attackLock();

				scheduleOnce([_enemy](float dt) {
					_enemy->attackUnLock();
				}, 2.0f, "UNLOCK");

				_player->hit(_enemy->getDamage());
				rocker->setHp(_player->getHP());
			}

		}
		else if (nodeA->getTag() == ENEMY_TAG && nodeB->getTag() == PLAYER_TAG) {

			ret = true;

			auto _enemy = (ENEMY *)nodeA;

			if (_enemy->getAttackLock() == false) {
				return true;
			}
			else {
				_enemy->attackLock();

				scheduleOnce([_enemy](float dt) {
					_enemy->attackUnLock();
				}, 2.0f, "UNLOCK");

				_player->hit(_enemy->getDamage());
				rocker->setHp(_player->getHP());
			}


		}
	}

	return ret;
}

bool BattleScene::ContactSeparate(PhysicsContact & contact)
{




	return true;
}

void BattleScene::updateEnemyDirection(float)
{
	auto _player_position = this->getChildByTag(PLAYER_TAG)->getPosition();


	for (auto enemy : m_enemies) {

		enemy->updateVel(_player_position);

	}


	if (m_enemies.size() < 5) {


		for (auto prop : m_openedProps) {
			this->removeChild(prop);
			prop = nullptr;
		}

		m_openedProps.clear();

		initEnemy();
		
		this->rocker->sendMessage("New Round is Coming!");
	}


}



Point BattleScene::positionCoordFromTile(Point pos)
{
	float x = pos.x * (_tileMap->getContentSize().width / _tileMap->getMapSize().width);
	float y = _tileMap->getContentSize().height - pos.y * (_tileMap->getContentSize().height / _tileMap->getMapSize().height);
	x = MIN(MAX(x,0), _tileMap->getContentSize().width);
	y = MIN(MAX(y, 0), _tileMap->getContentSize().height);
	return Point(x, y);
}