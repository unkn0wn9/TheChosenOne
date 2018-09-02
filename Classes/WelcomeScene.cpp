#include "WelcomeScene.h"
#include "CommonData.h"
#include "SimpleAudioEngine.h"
#include "BattleScene.h"
#include "AboutScene.h"

USING_NS_CC;

//Tag:
//100 title
//101 主菜单
//102 设置菜单
//103 音量

Scene* WelcomeScene::createScene()
{
	return WelcomeScene::create();
}

bool WelcomeScene::init()
{
	if (!Scene::init()) {
		return false;
	}

	// 载入缓存
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("character.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("weapon.plist");
	auto aniPlayerHitLeft = Animation::create();
	aniPlayerHitLeft->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_left_hit1.png"));
	aniPlayerHitLeft->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_left2.png"));
	aniPlayerHitLeft->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_left_hit2.png"));
	aniPlayerHitLeft->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_left1.png"));
	aniPlayerHitLeft->setDelayPerUnit(0.5f);
	aniPlayerHitLeft->setLoops(2);
	AnimationCache::getInstance()->addAnimation(aniPlayerHitLeft, ANI_PLAYER_HIT_LEFT);


	auto aniPlayerHitRight = Animation::create();
	aniPlayerHitRight->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_right_hit1.png"));
	aniPlayerHitRight->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_right2.png"));
	aniPlayerHitRight->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_right_hit2.png"));
	aniPlayerHitRight->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_right1.png"));
	aniPlayerHitRight->setDelayPerUnit(0.5f);
	aniPlayerHitRight->setLoops(2);
	AnimationCache::getInstance()->addAnimation(aniPlayerHitRight, ANI_PLAYER_HIT_RIGHT);

	auto aniPlayerLeft = Animation::create();
	aniPlayerLeft->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_left1.png"));
	aniPlayerLeft->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_left2.png"));
	aniPlayerLeft->setDelayPerUnit(0.2f);
	aniPlayerLeft->setLoops(-1);
	AnimationCache::getInstance()->addAnimation(aniPlayerLeft, ANI_PLAYER_WALK_LEFT);

	auto aniPlayerRight = Animation::create();
	aniPlayerRight->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_right1.png"));
	aniPlayerRight->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_right2.png"));
	aniPlayerRight->setDelayPerUnit(0.2f);
	aniPlayerRight->setLoops(-1);
	AnimationCache::getInstance()->addAnimation(aniPlayerRight, ANI_PLAYER_WALK_RIGHT);



	auto aniBoss = Animation::create();
	aniBoss->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("boss_1.png"));
	aniBoss->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("boss_2.png"));
	aniBoss->setDelayPerUnit(0.2f);
	aniBoss->setLoops(-1);
	AnimationCache::getInstance()->addAnimation(aniBoss, ANI_BOSS_WALK);

	auto aniMEnemyLeft = Animation::create();
	aniMEnemyLeft->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mEnemy_left1.png"));
	aniMEnemyLeft->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mEnemy_left2.png"));
	aniMEnemyLeft->setDelayPerUnit(0.2f);
	aniMEnemyLeft->setLoops(-1);
	AnimationCache::getInstance()->addAnimation(aniMEnemyLeft, ANI_M_ENEMY_LEFT);

	auto aniMEnemyRight = Animation::create();
	aniMEnemyRight->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mEnemy_right1.png"));
	aniMEnemyRight->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mEnemy_right2.png"));
	aniMEnemyRight->setDelayPerUnit(0.2f);
	aniMEnemyRight->setLoops(-1);
	AnimationCache::getInstance()->addAnimation(aniMEnemyRight, ANI_M_ENEMY_RIGHT);

	auto aniSEnemyLeft = Animation::create();
	aniSEnemyLeft->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sEnemy_left1.png"));
	aniSEnemyLeft->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sEnemy_left2.png"));
	aniSEnemyLeft->setDelayPerUnit(0.2f);
	aniSEnemyLeft->setLoops(-1);
	AnimationCache::getInstance()->addAnimation(aniSEnemyLeft, ANI_S_ENEMY_LEFT);

	auto aniSEnemyRight = Animation::create();
	aniSEnemyRight->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sEnemy_right1.png"));
	aniSEnemyRight->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("sEnemy_right2.png"));
	aniSEnemyRight->setDelayPerUnit(0.2f);
	aniSEnemyRight->setLoops(-1);
	AnimationCache::getInstance()->addAnimation(aniSEnemyRight, ANI_S_ENEMY_RIGHT);

	auto aniEnemyHit = Animation::create();
	aniEnemyHit->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hit1.png"));
	aniEnemyHit->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hit2.png"));
	aniEnemyHit->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hit3.png"));
	aniEnemyHit->setDelayPerUnit(0.3f);
	aniEnemyHit->setLoops(1);
	AnimationCache::getInstance()->addAnimation(aniEnemyHit, ANI_ENEMY_HIT);


	// 标签字体配置
	TTFConfig ttfConfig;
	ttfConfig.fontFilePath = "Satans Minions.ttf"; 
	ttfConfig.fontSize = 20;

	// 背景图
	auto background = Sprite::create("Background_WelcomeScene.jpg");
	background->setAnchorPoint(Point::ZERO);
	background->setPosition(Point::ZERO);
	background->setScaleX(VISIBLE_SIZE.width / background->getTextureRect().getMaxX());
	background->setScaleY(VISIBLE_SIZE.height / background->getTextureRect().getMaxY());
	addChild(background);

	// 背景音乐
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("begin.mp3", true);

	// 主标题
	title = Sprite::create("Character_TheChosenOne.png");
	title->setPosition(VISIBLE_SIZE.width / 2 - 160, VISIBLE_SIZE.height / 2 + 50);
	title->setScale(0.76);
	addChild(title,0,100);

	// 菜单
	Vector<MenuItem*> mainMenuItems;
	Vector<MenuItem*> optionMenuItems;

	// 开始按钮
	auto beginButton = MenuItemImage::create("Character_StartGame.png", "Character_StartGame.png",
		CC_CALLBACK_1(WelcomeScene::gameBeginCallback, this));

	beginButton->setAnchorPoint(Vec2(1, 0.5));
	beginButton->setPosition(Vec2(260, -50));

	mainMenuItems.pushBack(beginButton);

	// 设置按钮
	auto optionButton = MenuItemImage::create("Character_Opinions.png", "Character_Opinions.png",
		CC_CALLBACK_1(WelcomeScene::gameOptionCallback, this));

	optionButton->setAnchorPoint(Vec2(1, 0.5));
	optionButton->setPosition(Vec2(260, -100));

	mainMenuItems.pushBack(optionButton);


	// 退出按钮
	auto quitButton = MenuItemImage::create("Character_QuitGame.png", "Character_QuitGame.png",
		CC_CALLBACK_1(WelcomeScene::gameQuitCallback, this));


	quitButton->setAnchorPoint(Vec2(1, 0.5));
	quitButton->setPosition(Vec2(260, -150));

	mainMenuItems.pushBack(quitButton);

	// 关于按钮
	auto aboutButton = MenuItemImage::create("Character_AboutUs.png", "Character_AboutUs.png",
		CC_CALLBACK_1(WelcomeScene::gameAboutCallback, this));

	aboutButton->setAnchorPoint(Vec2(0, 0.5));
	aboutButton->setPosition(Vec2(50, 0));

	optionMenuItems.pushBack(aboutButton);

	// 音量按钮
	auto volumeButton = MenuItemImage::create("Character_Volume.png","Character_Volume.png");

	volumeButton->setAnchorPoint(Vec2(0, 0.5));
	volumeButton->setPosition(Vec2(50, -50));

	optionMenuItems.pushBack(volumeButton);

	// 音量显示
	int currentVolume = UserDefault::getInstance()->getIntegerForKey("Volume");
	if (UserDefault::getInstance()->getIntegerForKey("Volume") == NULL) {
		UserDefault::getInstance()->setIntegerForKey("Volume", 10);
	}
	//audio->setBackgroundMusicVolume(float(currentVolume) / 10.0f);
	log("%f", audio->getBackgroundMusicVolume());
	volumeLabel = Label::createWithTTF(ttfConfig, StringUtils::format("%d", currentVolume));
	volumeLabel->setPosition(Vec2(600, 135));
	volumeLabel->setVisible(false);
	addChild(volumeLabel);

	// 音量加按钮
	auto volumeAddButton = MenuItemImage::create("Character_Plus.png", "Character_Plus.png",
		CC_CALLBACK_1(WelcomeScene::gameVolumeAddCallback, this));

	volumeAddButton->setAnchorPoint(Vec2(0, 0.5));
	volumeAddButton->setPosition(Vec2(300, -50));

	optionMenuItems.pushBack(volumeAddButton);

	// 音量减按钮
	auto volumeMinusButton = MenuItemImage::create("Character_Minus.png", "Character_Minus.png",
		CC_CALLBACK_1(WelcomeScene::gameVolumeMinusCallback, this));

	volumeMinusButton->setAnchorPoint(Vec2(0, 0.5));
	volumeMinusButton->setPosition(Vec2(250, -50));

	optionMenuItems.pushBack(volumeMinusButton);

	// 难度按钮
	auto levelButton = MenuItemImage::create("Character_Level.png", "Character_Level.png",
		CC_CALLBACK_1(WelcomeScene::gameLevelCallback, this));

	levelButton->setAnchorPoint(Vec2(0, 0.5));
	levelButton->setPosition(Vec2(50, -100));

	optionMenuItems.pushBack(levelButton);

	// 难度显示
	int currentLevel = UserDefault::getInstance()->getIntegerForKey("Level");
	levelLabel = Label::createWithTTF(ttfConfig, StringUtils::format("%d", currentVolume));
	switch (currentLevel)
	{
	case 1:
		levelLabel->setString("Easy");
		break;
	case 2:
		levelLabel->setString("Normal");
		break;
	case 3:
		levelLabel->setString("Hard");
		break;
	default:
		UserDefault::getInstance()->setIntegerForKey("Level", 1);
		levelLabel->setString("Easy");
		break;
	}
	levelLabel->setPosition(Vec2(600, 85));
	levelLabel->setVisible(false);
	addChild(levelLabel);

	// 返回主菜单按钮
	auto backButton = MenuItemImage::create("Character_ComeBack.png", "Character_ComeBack.png",
		CC_CALLBACK_1(WelcomeScene::gameBackCallback, this));

	backButton->setAnchorPoint(Vec2(0, 0.5));
	backButton->setPosition(Vec2(50, -150));

	optionMenuItems.pushBack(backButton);


	/* repeat for as many menu items as needed */

	auto mainMenu = Menu::createWithArray(mainMenuItems);
	this->addChild(mainMenu, 1,101);

	auto optionMenu = Menu::createWithArray(optionMenuItems);
	this->addChild(optionMenu, 1, 102);
	optionMenu->setVisible(false);

	return true;
}

void WelcomeScene::gameBeginCallback(Ref* pSender)
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("click1.wav", false, 1.0f, 1.0f, 1.0f);
	audio->pauseBackgroundMusic();
	auto battleScene = BattleScene::createScene();
	Director::getInstance()->replaceScene(battleScene);

}
void WelcomeScene::gameOptionCallback(Ref* pSender)
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("click1.wav", false, 1.0f, 1.0f, 1.0f);
	auto mainMenu = getChildByTag(101);
	mainMenu->setVisible(false);
	auto optionMenu = getChildByTag(102);
	optionMenu->setVisible(true);
	volumeLabel->setVisible(true);
	levelLabel->setVisible(true);
	title->setTexture("Character_GameOpinions.png");
}

void WelcomeScene::gameQuitCallback(Ref* pSender)
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("click1.wav", false, 1.0f, 1.0f, 1.0f);
	Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void WelcomeScene::gameVolumeAddCallback(Ref* pSender)
{
	int currentVolume = UserDefault::getInstance()->getIntegerForKey("Volume");
	currentVolume += 1;
	if (currentVolume >= 10) {
		currentVolume = 10;
	}
	UserDefault::getInstance()->setIntegerForKey("Volume", currentVolume);
	volumeLabel->setString(StringUtils::format("%d", currentVolume));
	// 调整音量
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	//audio->setBackgroundMusicVolume(float(currentVolume) / 10.0f);
}

void WelcomeScene::gameVolumeMinusCallback(Ref* pSender)
{
	int currentVolume = UserDefault::getInstance()->getIntegerForKey("Volume");
	currentVolume -= 1;
	if (currentVolume <= 0) {
		currentVolume = 0;
	}
	UserDefault::getInstance()->setIntegerForKey("Volume", currentVolume);
	volumeLabel->setString(StringUtils::format("%d", currentVolume));
	// 调整音量
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	//audio->setBackgroundMusicVolume(float(currentVolume) / 10.0f);
}


void WelcomeScene::gameLevelCallback(Ref* pSender)
{
	int currentLevel = UserDefault::getInstance()->getIntegerForKey("Level");
	switch (currentLevel)
	{
	case 1:
		currentLevel += 1;
		levelLabel->setString("Normal");
		break;
	case 2:
		currentLevel += 1;
		levelLabel->setString("Hard");
		break;
	case 3:
		currentLevel = 1;
		levelLabel->setString("Easy");
		break;
	default:
		currentLevel = 1;
		levelLabel->setString("Easy");
		break;
	}
	UserDefault::getInstance()->setIntegerForKey("Level", currentLevel);
	log("%s", "Change Level");
}
void WelcomeScene::gameBackCallback(Ref* pSender)
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("click1.wav", false, 1.0f, 1.0f, 1.0f);
	auto optionMenu = getChildByTag(102);
	optionMenu->setVisible(false);
	volumeLabel->setVisible(false);
	levelLabel->setVisible(false);
	auto mainMenu = getChildByTag(101);
	mainMenu->setVisible(true);
	title->setTexture("Character_TheChosenOne.png");
}

void WelcomeScene::gameAboutCallback(Ref* pSender)
{
	auto aboutScene = AboutScene::createScene();
	Director::getInstance()->pushScene(aboutScene);
}