#ifndef __ENEMYGENERATOR_H__
#define __ENEMYGENERATOR_H__

#include "cocos2d.h"
#include <stdlib.h>

USING_NS_CC;

class GeneratorEnemy
{
public:
	static GeneratorEnemy * _instance;
	static GeneratorEnemy * getInstance();

	GeneratorEnemy();
	~GeneratorEnemy();

	cocos2d::Sprite * GenerateEnemy();

	void createPlane(Sprite* &m, Action* &mAction, PhysicsBody* &mb);


	void createEnemyBird(Sprite* &m, Action* &mAction, PhysicsBody* &mb);


	void createMountain(Sprite* &m, Action* &mAction, PhysicsBody* &mb);


	void createCloud(Sprite* &m, Action* &mAction, PhysicsBody* &mb);

	void removeEnemys();
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    
	Vector<Sprite*> _enemys;
};

#endif // __ENEMYGENERATOR_H__
