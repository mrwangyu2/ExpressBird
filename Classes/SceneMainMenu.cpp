#include "SceneMainMenu.h"
#include "SceneGame.h"

//游戏主界面，通过点击开始按钮可以进入游戏场景

Scene* SceneMainMenu::createScene()
{
    auto scene = Scene::create();
    auto layer = SceneMainMenu::create();
    scene->addChild(layer);
    return scene;
}

bool SceneMainMenu::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	this->getVisible();
	this->setBackground("bg.jpg");
	this->setMainMenu();

    return true;
}


void SceneMainMenu::setMainMenu()
{
	auto playItem = MenuItemImage::create("Play Button.png", "Play Button Clicked.png", CC_CALLBACK_1(SceneMainMenu::goToGameScene, this));
	playItem->setPosition(Vec2(this->_visibleSize.width / 2 + this->_visibleOrigin.x, this->_visibleSize.height / 2 + this->_visibleOrigin.y));

	auto menu = Menu::create(playItem, NULL);
	menu->setPosition(Vec2::ZERO);

	this->addChild(menu);
}

void SceneMainMenu::goToGameScene(cocos2d::Ref *sender)
{
    auto scene = SceneGame::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}



