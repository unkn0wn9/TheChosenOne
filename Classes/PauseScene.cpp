#include "PauseScene.h"
#include "SimpleAudioEngine.h"
#include "WelcomeScene.h"
USING_NS_CC;

Scene* PauseScene::createScene() {
	return PauseScene::create();
}

bool PauseScene::init() {

	// 背景图
	auto background = Sprite::create("Background_WelcomeScene-Bak.jpg");
	background->setAnchorPoint(Point::ZERO);
	background->setPosition(Point::ZERO);
	background->setScaleX(VISIBLE_SIZE.width / background->getTextureRect().getMaxX());
	background->setScaleY(VISIBLE_SIZE.height / background->getTextureRect().getMaxY());
	addChild(background);

	// 主标题
	auto title = Sprite::create("Character_GamePause.png");
	title->setPosition(VISIBLE_SIZE.width / 2 - 160, VISIBLE_SIZE.height / 2 + 50);
	title->setScale(0.76);
	addChild(title, 0, 100);

	// 菜单
	Vector<MenuItem*> MenuItems;

	// 返回按钮
	auto backButton = MenuItemImage::create("Character_Resume.png", "Character_Resume.png",
		CC_CALLBACK_1(PauseScene::gameBackCallback, this));

	backButton->setAnchorPoint(Vec2(0, 0.5));
	backButton->setPosition(Vec2(100, -50));

	MenuItems.pushBack(backButton);

	//退出
	auto quitButton = MenuItemImage::create("Character_QuitGame.png", "Character_QuitGame.png",
		CC_CALLBACK_1(PauseScene::gameQuitCallback, this));


	quitButton->setAnchorPoint(Vec2(0, 0.5));
	quitButton->setPosition(Vec2(100, -100));

	MenuItems.pushBack(quitButton);

	auto Menu = Menu::createWithArray(MenuItems);
	this->addChild(Menu, 1, 101);

	return true;
}

void PauseScene::gameBackCallback(cocos2d::Ref* pSender) {
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("click1.wav", false, 1.0f, 1.0f, 1.0f);
	Director::getInstance()->popScene();
}

void PauseScene::gameQuitCallback(cocos2d::Ref * pSender)
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("click1.wav", false, 1.0f, 1.0f, 1.0f);
	auto welcomeScene = WelcomeScene::createScene();
	Director::getInstance()->replaceScene(welcomeScene);
}
