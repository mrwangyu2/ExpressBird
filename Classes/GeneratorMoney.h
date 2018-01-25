#ifndef __MONEY_H__
#define __MONEY_H__

#include "Definitions.h"
#include "cocos2d.h"

USING_NS_CC;

class GeneratorMoney {
public:
	static GeneratorMoney * _instance;
	static GeneratorMoney * getInstance();

	~GeneratorMoney();

	Vector<Node*> generateMoney();
	void removeMoney();
	void obtainMoney(Node* mon);

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	Vector<Node*> _moneys;

	GeneratorMoney();

	void generMoney(float x, float y);
	void countMomeyFormation_4(float MoneyWith, float MoneyHeight);
	void countMomeyFormation_3(float MoneyWith, float MoneyHeight);
	void countMomeyFormation_2(float MoneyWith, float MoneyHeight);
	void countMomeyFormation_1(float MoneyWith, float MoneyHeight);
	void countMoneyFormation_0(float MoneyWith, float MoneyHeight);

};

#endif // __MONEY_H__
