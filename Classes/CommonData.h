#pragma once
#include "cocos2d.h"

#define PLAYER_INITIAL_IMG "hero_right1.png"

#define PLAYER_HP 100

#define SMALL_ENEMY_STEP 100
#define SMALL_ENEMY_HP 10
#define SMALL_ENEMY_HIT 5
#define SMALL_ENEMY_SCORE 5

#define MIDDLE_ENEMY_STEP 120
#define MIDDLE_ENEMY_HP 20
#define MIDDLE_ENEMY_HIT 10
#define MIDDLE_ENEMY_SCORE 10

#define BIG_ENEMY_STEP 150
#define BIG_ENEMY_HP 50
#define BIG_ENEMY_HIT 20
#define BIG_ENEMY_SCORE 30

#define HAND_GUN_BULLET_CD 0.0f
#define RIFLE_GUN_BULLET_CD 0.0f
#define SHOT_GUN_BULLET_CD 0.0f
#define SNIPER_GUN_BULLET_CD 0.5f
#define RPG_BULLET_CD 1.0f


#define HAND_GUN_BULLET_STEP 300.0f
#define RIFLE_GUN_BULLET_STEP 400.0f
#define SHOT_GUN_BULLET_STEP 300.0f
#define SNIPER_GUN_BULLET_STEP 600.0f
#define RPG_BULLET_STEP 250.0f

#define HAND_GUN_BULLET_DAMAGE 3
#define RIFLE_GUN_BULLET_DAMAGE 8
#define SHOT_GUN_BULLET_DAMAGE 6
#define SNIPER_GUN_BULLET_DAMAGE 10
#define RPG_BULLET_DAMAGE 25

#define HAND_GUN_BULLET_RANGE 300.0f
#define RIFLE_GUN_BULLET_RANGE 600.0f
#define SHOT_GUN_BULLET_RANGE 300.0f
#define SNIPER_GUN_BULLET_RANGE 1000.0f
#define RPG_BULLET_RANGE 1000.0f

#define HAND_GUN_BULLET_COUNT 10000
#define RIFLE_GUN_BULLET_COUNT 100
#define SHOT_GUN_BULLET_COUNT 50
#define SNIPER_GUN_BULLET_COUNT 30
#define RPG_BULLET_COUNT 5


#define RIFLE_GUN_PR 0.3f
#define SHOT_GUN_PR 0.3f
#define SNIPER_GUN_PR 0.2f
#define RPG_PR 0.2f

#define MEDKIT_ADD_HP 20



#define VISIBLE_SIZE Director::getInstance()->getVisibleSize()
#define ORIGIN Director::getInstance()->getVisibleOrigin()

namespace CommonData
{
	enum Direction
	{
		STAY,
		UP,  //上
		DOWN,  //下
		LEFT,  //左
		RIGHT,  //右
		R_UP,  //右上
		R_DOWN,  //右下
		L_UP,  //左上
		L_DOWN //左下
	};

	enum EnemyType
	{
		SMALL_ENEMY,
		MIDDLE_ENEMY,
		BIG_ENEMY
	};

	enum WeaponType
	{
		HAND_GUN,
		RIFLE_GUN,
		SHOT_GUN,
		SNIPER_GUN,
		RPG
	};

	enum PropType
	{
		MEDKIT_PROP,
		GUN_PROP
	};

	enum BulletType
	{
		GUN_BULLET,
		RPG_BULLET
	};
};





// =============== 2018/08/28 ===============

#define PLAYER_TAG 200
#define ENEMY_TAG 199
#define BULLET_TAG 198
#define PROP_TAG 197
#define OBS_TAG 201
#define EDGE_TAG 155


#define PLAYER_CAT_BITMASK 0x01  // 00000001
#define ENEMY_CAT_BITMASK  0x02	 // 00000010
#define BULLET_CAT_BITMASK 0x04	 // 00000100
#define PROP_CAT_BITMASK   0x08	 // 00001000
#define OBS_CAT_BITMASK	   0x10	 // 00010000
#define EDGE_CAT_BITMASK   0x20  // 00100000

#define PLAYER_COL_BITMASK 0x1a  // 00011010
#define ENEMY_COL_BITMASK  0x37	 // 00110111
#define BULLET_COL_BITMASK 0x32	 // 00110010
#define PROP_COL_BITMASK   0x39	 // 00111001
#define OBS_COL_BITMASK    0x2f  // 00101111
#define EDGE_COL_BITMASK   0x3e  // 00111110

#define PLAYER_CON_BITMASK 0x1a  // 00011010
#define ENEMY_CON_BITMASK  0x05  // 00000101
#define BULLET_CON_BITMASK 0x32  // 00110010
#define PROP_CON_BITMASK   0x01  // 00000001
#define OBS_CON_BITMASK    0x05  // 00000101
#define EDGE_CON_BITMASK   0x04  // 00000100


#define ANI_PLAYER_WALK_RIGHT "playerwalkright"
#define ANI_PLAYER_WALK_LEFT "playerwalkleft"


#define ANI_M_ENEMY_LEFT "MENEMY_ANI_LEFT"
#define ANI_M_ENEMY_RIGHT "MENEMY_ANI_RIGHT"

#define ANI_S_ENEMY_LEFT "SENEMY_ANI_LEFT"
#define ANI_S_ENEMY_RIGHT "SENEMY_ANI_RIGHT"

#define ANI_BOSS_WALK "ANI_BOSS_WALK"

#define ANI_ENEMY_HIT "ANI_ENEMY_HIT"

#define ANI_PLAYER_HIT_LEFT "ANI_PLAYER_HIT_left"
#define ANI_PLAYER_HIT_RIGHT "ANI_PLAYER_HIT_RIGHT"

//#define IMG_PLAYER_STAY_RIGHT "hero_right1.png"
#define IMG_PLAYER_STAY_RIGHT "hero_right1.png"
#define IMG_PLAYER_STAY_LEFT "hero_left1.png"

#define IMG_HAND_GUN_LEFT "handGun_left.png"
#define IMG_HAND_GUN_RIGHT "handGun_right.png"

#define IMG_RIFLE_GUN_LEFT "rifleGun_left.png"
#define IMG_RIFLE_GUN_RIGHT "rifleGun_right.png"

#define IMG_SHOT_GUN_LEFT "shotGun_left.png"
#define IMG_SHOT_GUN_RIGHT "shotGun_right.png"

#define IMG_SNIPER_GUN_LEFT "sniperGun_left.png"
#define IMG_SNIPER_GUN_RIGHT "sniperGun_right.png"

#define IMG_RPG_LEFT "RPG_left.png"
#define IMG_RPG_RIGHT "RPG_right.png"



#define WEAPON_ZORDER 100
#define ANIMATION_ZORDER 99
#define PLAYER_ZORDER 200


#define ENEMY_BOSS_NUMBER 1
#define ENEMY_S_NUMBER 20
#define ENEMY_M_NUMBER 8

#define PROP_BOX_NUMBER 35