#include "GameOverScene.h"
#include "CommonData.h"
#include "BattleScene.h"
#include "WelcomeScene.h"

USING_NS_CC;

Scene* GameOverScene::createScene(int totalScore) {
	return GameOverScene::create(totalScore);
}

bool GameOverScene::init(int totalScore)
{
	// 停止游戏背景音乐
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->stopBackgroundMusic();

	// 背景图
	auto background = Sprite::create("Background_GameOverScene.jpg");
	background->getTexture()->setAliasTexParameters();
	background->setAnchorPoint(Point::ZERO);
	background->setPosition(Point::ZERO);
	background->setScaleX(VISIBLE_SIZE.width / background->getTextureRect().getMaxX());
	background->setScaleY(VISIBLE_SIZE.height / background->getTextureRect().getMaxY());
	this->addChild(background, 0);

	// 标题
	auto title = Sprite::create("Character_GameOver.png");
	title->setAnchorPoint(Point::ZERO);
	title->setPosition(110, VISIBLE_SIZE.height/2 + 30);
	title->getTexture()->setAliasTexParameters();
	this->addChild(title, 0);

	// 分数标题
	auto scoreSprite = Sprite::create("Character_YourScore.png");
	scoreSprite->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	scoreSprite->setPosition(110, VISIBLE_SIZE.height / 2 - 5);
	scoreSprite->getTexture()->setAliasTexParameters();
	this->addChild(scoreSprite, 0);

	// 分数
	auto scoreLabel = Label::createWithBMFont("fonts/font.fnt", StringUtils::format("%d", totalScore));
	scoreLabel->setPosition(390, VISIBLE_SIZE.height / 2 - 5);
	scoreLabel->setScale(1.5);
	scoreLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	scoreLabel->setColor(Color3B::WHITE);
	this->addChild(scoreLabel, 0);


	// 菜单
	Vector<MenuItem*> MenuItems;

	// 重新开始
	auto restart = Sprite::create("Character_RestartGame.png");
	auto menuItemRestart= MenuItemSprite::create(restart, restart, [audio](Ref *) {
		//auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
		audio->playEffect("click1.wav", false, 1.0f, 1.0f, 1.0f);
		auto scene = BattleScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});
	menuItemRestart->setPosition(Vec2(170, -50));
	MenuItems.pushBack(menuItemRestart);

	// 回到主页面
	auto back = Sprite::create("Character_BacktoHomepage.png");
	auto menuItemBack = MenuItemSprite::create(back, back, [audio](Ref *) {
		audio->playEffect("click1.wav", false, 1.0f, 1.0f, 1.0f);
		auto scene = WelcomeScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});
	menuItemBack->setPosition(Vec2(120, -100));
	MenuItems.pushBack(menuItemBack);

	// 结束游戏
	auto end = Sprite::create("Character_QuitGame.png");
	auto menuItemEnd = MenuItemSprite::create(end, end, [audio](Ref *) {
		audio->playEffect("click1.wav", false, 1.0f, 1.0f, 1.0f);
		Director::getInstance()->end();
	});
	menuItemEnd->setPosition(Vec2(200, -150));
	MenuItems.pushBack(menuItemEnd);

	auto menu = Menu::createWithArray(MenuItems);
	this->addChild(menu, 1);

	return true;
}

GameOverScene* GameOverScene::create(int totalScore)
{
	auto gameOver = new GameOverScene();
	if (gameOver&&gameOver->init(totalScore)) {
		gameOver->autorelease();
		return gameOver;
	}
	delete gameOver;
	gameOver = NULL;
	return NULL;
}