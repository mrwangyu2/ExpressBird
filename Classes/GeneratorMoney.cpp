#include "GeneratorMoney.h"

USING_NS_CC;

GeneratorMoney * GeneratorMoney::_instance = NULL;

GeneratorMoney * GeneratorMoney::getInstance() {
	if (_instance == NULL) {
		_instance = new GeneratorMoney();
	}
	return _instance;
}

GeneratorMoney::~GeneratorMoney() {
	CCLOG("destrocut %d", _moneys.size());
	for (int i = 0; i < _moneys.size();) {
		_moneys.at(i)->removeFromParentAndCleanup(true);
		_moneys.erase(i);
	}
	_instance = NULL;
}

GeneratorMoney::GeneratorMoney() {
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}

Vector<Node*> GeneratorMoney::generateMoney() {
	Vector<Node*> temp;
	if (_moneys.size() > 0) return temp;
	float MoneyWith = 45;
	float MoneyHeight = 45;
    int type = rand()  % 5;

	if (type == 0) {
		this->countMoneyFormation_0(MoneyWith, MoneyHeight);
	}
	else if (type == 1) {
		this->countMomeyFormation_1(MoneyWith, MoneyHeight);
	}
	else if (type == 2) {
		this->countMomeyFormation_2(MoneyWith, MoneyHeight);
	}
	else if (type == 3) {
		this->countMomeyFormation_3(MoneyWith, MoneyHeight);
	}
	else {
		this->countMomeyFormation_4(MoneyWith, MoneyHeight);
	}

	return _moneys;
}

void GeneratorMoney::countMoneyFormation_0(float MoneyWith, float MoneyHeight)
{
	/*
	****
	****
	****
	****
	*/
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			generMoney(visibleSize.width + MoneyWith * (3 - i), visibleSize.height / 2 - MoneyHeight * (2 - j));
		}
	}
}

//生成一个金币，加入到vector中
void GeneratorMoney::generMoney(float x, float y) {
	Sprite* money;
	PhysicsBody* momeyPhysicBody;
	MoveBy* momeyAction; 

	money = Sprite::create("money.png");
	money->setPosition(x, y);
	momeyAction = MoveBy::create(MONEY_MOVEMENT_SPEED * visibleSize.width, Point(-visibleSize.width * 1.5, 0));
	
	money->setTag(MONEY_TAG);

	momeyPhysicBody = PhysicsBody::createCircle(money->getContentSize().width / 2);
	momeyPhysicBody->setDynamic(false);
	momeyPhysicBody->setRotationEnable(false);
	momeyPhysicBody->setAngularVelocityLimit(0);

	momeyPhysicBody->setCategoryBitmask(0x02);
	momeyPhysicBody->setCollisionBitmask(0x00);
	momeyPhysicBody->setContactTestBitmask(0x01);

	money->setPhysicsBody(momeyPhysicBody);

	money->runAction(momeyAction);

	_moneys.pushBack(money);
}

void GeneratorMoney::countMomeyFormation_1(float MoneyWith, float MoneyHeight)
{
	/*
	     ****
	    ****
	   ****
	  ****
	  */
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			generMoney(visibleSize.width + MoneyWith * (3 - i + 3 - j), visibleSize.height / 2 - MoneyHeight * (2 - j));
		}
	}
}

void GeneratorMoney::countMomeyFormation_2(float MoneyWith, float MoneyHeight)
{
	/*
		  ****
		   ****
		    ****
		     ****
		  */
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			generMoney(visibleSize.width + MoneyWith * (3 - i + j), visibleSize.height / 2 - MoneyHeight * (2 - j));
		}
	}
}

void GeneratorMoney::countMomeyFormation_3(float MoneyWith, float MoneyHeight)
{
	/*
		  ****
		 **    **
		**       **
	  **          **
		  */
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			generMoney(visibleSize.width + MoneyWith * (1 - i + 3 - j), visibleSize.height / 2 - MoneyHeight * (2 - j));
		}
	}
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			generMoney(visibleSize.width + MoneyWith * (5 + 1 - i + j), visibleSize.height / 2 - MoneyHeight * (2 - j));
		}
	}
}

void GeneratorMoney::countMomeyFormation_4(float MoneyWith, float MoneyHeight)
{
	/*
	**      **
	 **    **
	  **  **
	   ****
	*/
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			generMoney(visibleSize.width + MoneyWith * (1 - i + j), visibleSize.height / 2 - MoneyHeight * (2 - j));
		}
	}
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			generMoney(visibleSize.width + MoneyWith * (5 + 1 - i + 3 - j), visibleSize.height / 2 - MoneyHeight * (2 - j));
		}
	}
}

//大鸟捡到钱，金币消失
void GeneratorMoney::obtainMoney(Node* mon) 
{
	mon->removeFromParentAndCleanup(true);
	_moneys.eraseObject(mon);
}

//判断金币组合vector是否到了屏幕边缘，是的话就消失
void GeneratorMoney::removeMoney() 
{
	for (int i = 0; i < _moneys.size();) {
		if (_moneys.at(i)->getPosition().x < 20) {
			_moneys.at(i)->removeFromParentAndCleanup(true);
			_moneys.erase(i);
		} else {
			++i;
		}
	}
}
