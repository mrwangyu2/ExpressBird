//#include "stdafx.h"
#include "SceneBase.h"

SceneBase::SceneBase()
{
}

SceneBase::~SceneBase()
{
}

void SceneBase::setBackground(const std::string& pictureName)
{
	auto backgroundSprite = Sprite::create(pictureName);
	//backgroundSprite->setPosition(Vec2(this->_visibleSize.width / 2 + this->_visibleOrigin.x, this->_visibleSize.height / 2 + this->_visibleOrigin.y));
	Size size = Director::getInstance()->getWinSize();
	backgroundSprite->setPosition(Vec2(size.width / 2, size.height / 2));
	float winw = size.width;
	float winh = size.height;

	float spx = backgroundSprite->getTextureRect().getMaxX();
	float spy = backgroundSprite->getTextureRect().getMaxY();

	backgroundSprite->setScaleX(winw / spx); //设置精灵宽度缩放比例
	backgroundSprite->setScaleY(winh / spy);

	this->addChild(backgroundSprite);
}

void SceneBase::getVisible()
{
	this->_visibleSize = Director::getInstance()->getVisibleSize();
	this->_visibleOrigin = Director::getInstance()->getVisibleOrigin();
}
