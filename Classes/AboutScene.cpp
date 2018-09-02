#include "AboutScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

Scene* AboutScene::createScene() {
	return AboutScene::create();
}

bool AboutScene::init() {

	// ±³¾°Í¼
	auto background = Sprite::create("Scene_AboutUs.jpg");
	background->setAnchorPoint(Point::ZERO);
	background->setPosition(Point::ZERO);
	background->setScaleX(VISIBLE_SIZE.width / background->getTextureRect().getMaxX());
	background->setScaleY(VISIBLE_SIZE.height / background->getTextureRect().getMaxY());
	addChild(background);

	// ²Ëµ¥
	Vector<MenuItem*> MenuItems;

	// ·µ»Ø°´Å¥
	auto backButton = MenuItemImage::create("Character_ComeBack.png", "Character_ComeBack.png",
		CC_CALLBACK_1(AboutScene::gameBackCallback, this));

	backButton->setAnchorPoint(Vec2(0, 0.5));
	backButton->setPosition(Vec2(100, -150));

	MenuItems.pushBack(backButton);

	auto Menu = Menu::createWithArray(MenuItems);
	this->addChild(Menu, 1, 101);

	return true;
}

void AboutScene::gameBackCallback(cocos2d::Ref* pSender) {
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("click1.wav", false, 1.0f, 1.0f, 1.0f);
	Director::getInstance()->popScene();
}