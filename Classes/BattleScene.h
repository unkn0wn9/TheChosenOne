#ifndef _BATTLE_SCENE_H_
#define _BATTLE_SCENE_H_

#include "cocos2d.h"
#include "Player.h"
#include "Enemy.h"
#include "Prop.h"

class JoyStick;

class BattleScene : public cocos2d::Scene {
	cocos2d::TMXTiledMap* _tileMap;
	cocos2d::TMXLayer* _blocks;
	PLAYER* _player;
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(BattleScene);

	void schedulePos(float dt);
	void setViewpointCenter(cocos2d::Point position);
	bool checkBlock(Vec2 point);
	cocos2d::Point tileCoordFromPosition(Point pos);
	cocos2d::Point positionCoordFromTile(Point pos);

private:
	JoyStick* rocker;
	void initEnemy();

	virtual void onEnter();
	
	bool ContactBegin(PhysicsContact &contact);
	bool ContactPost(PhysicsContact &contact);
	bool ContactSeparate(PhysicsContact &contact);

	void updateProp();
	void updateEnemyDirection(float);
	void createEnemyByPoint(Vec2);

	cocos2d::Vector <ENEMY *> m_enemies;
	cocos2d::Vector <PROP *> m_openedProps;
};

#endif // !_BATTLE_SCENE_H_
