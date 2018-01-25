#include "GeneratorEnemy.h"
#include "Definitions.h"

USING_NS_CC;

// 单例模式
GeneratorEnemy * GeneratorEnemy::_instance = NULL;

GeneratorEnemy * GeneratorEnemy::getInstance()
{
	if (_instance == NULL) {
		_instance = new GeneratorEnemy();
	}
	return _instance;
}

GeneratorEnemy::GeneratorEnemy()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}

GeneratorEnemy::~GeneratorEnemy()
{
	CCLOG("destrocut enemy %d", _enemys.size());
	for (int i = 0; i < _enemys.size(); i++)
	{
		_enemys.at(i)->removeFromParentAndCleanup(true);
		_enemys.erase(i);
	}
	_instance = NULL;
}

cocos2d::Sprite * GeneratorEnemy::GenerateEnemy()
{
	CCLOG("SPAWN MONSTER");

	Sprite* enemy;
	PhysicsBody* enemyPhysicsBody;
	Action* enemyAction;
	int type = rand() % 4; // 0 云 1 山 2 鸟 3 飞机

	if (type == 0)
	{
		this->createCloud(enemy, enemyAction, enemyPhysicsBody);
	}
	else if (type == 1)
	{
		this->createMountain(enemy, enemyAction, enemyPhysicsBody);
	}
	else if (type == 2)
	{
		this->createEnemyBird(enemy, enemyAction, enemyPhysicsBody);
	}
	else if (type == 3)
	{
		createPlane(enemy, enemyAction, enemyPhysicsBody);
	}

	enemy->setTag(ENEMY_TAG);

	enemyPhysicsBody->setDynamic(false);

	enemyPhysicsBody->setCategoryBitmask(0x02);
	enemyPhysicsBody->setCollisionBitmask(0x01);
	enemyPhysicsBody->setContactTestBitmask(0x01);

	enemy->setPhysicsBody(enemyPhysicsBody);

	enemy->runAction(enemyAction);

	_enemys.pushBack(enemy);
	CCLOG("enemys %d", _enemys.size());
	return enemy;

}

void GeneratorEnemy::createCloud(Sprite* &cloud, Action* &mAction, PhysicsBody* &cloudPhysicsBody)
{
	cloud = Sprite::create("cloud.png");
	cloud->setPosition(visibleSize.width + cloud->getContentSize().width, visibleSize.height - rand() % 50);
	double rand_speed = 2 / (rand() % 2 + 2);
	mAction = MoveBy::create(rand_speed* CLOUD_MOVEMENT_SPEED * visibleSize.width, Point(-visibleSize.width - 2 * cloud->getContentSize().width, 0));

	Vec2 shape0[5];
	shape0[0].setPoint(-70, 0);
	shape0[1].setPoint(0, 70);
	shape0[2].setPoint(70, 0);
	shape0[3].setPoint(70, -20);
	shape0[4].setPoint(20, -20);

	Vec2 shape1[3];
	shape1[0].setPoint(-20, 0);
	shape1[1].setPoint(20, 0);
	shape1[2].setPoint(0, -80);

	cloudPhysicsBody = PhysicsBody::create();
	// 为刚体添加Shape实现精确碰撞
	cloudPhysicsBody->addShape(PhysicsShapePolygon::create(shape0, 5));
	cloudPhysicsBody->addShape(PhysicsShapePolygon::create(shape1, 3));
}

void GeneratorEnemy::createMountain(Sprite* &mountain, Action* &mAction, PhysicsBody* &mountainPhysicBody)
{
	double rand_size = rand() % 2 + 2;
	mountain = Sprite::create("mountain.png");
	mountain->setPosition(visibleSize.width + mountain->getContentSize().width, mountain->getContentSize().height*(1 / rand_size) / 2 - 20);
	mountain->setScale(1 / rand_size);
	mAction = MoveBy::create(MOUNT_MOVEMENT_SPEED * visibleSize.width, Point(-visibleSize.width - mountain->getContentSize().width * 2, 0));

	Vec2 shape0[3];
	shape0[0].setPoint(-550, -300);
	shape0[1].setPoint(-50, 200);
	shape0[2].setPoint(450, -300);

	Vec2 shape1[3];
	shape1[0].setPoint(-420, -300);
	shape1[1].setPoint(80, 200);
	shape1[2].setPoint(580, -300);
	mountainPhysicBody = PhysicsBody::create();
	// 为刚体添加Shape实现精确碰撞
	mountainPhysicBody->addShape(PhysicsShapePolygon::create(shape0, 3));
	mountainPhysicBody->addShape(PhysicsShapePolygon::create(shape1, 3));
}

void GeneratorEnemy::createEnemyBird(Sprite* &enemyBird, Action* &mAction, PhysicsBody* &enemyBirdPhysicBody)
{
	enemyBird = Sprite::create("mmbird.png");
	enemyBird->setPosition(visibleSize.width + enemyBird->getContentSize().width, rand() % (int)visibleSize.height);
	double rand_speed = rand() % 4 + 2;

	int rand_case = rand() % 2;
	// 按bezier曲线运动
	ccBezierConfig bezier;
	bezier.controlPoint_1 = Point(0, enemyBird->getPositionY());
	if (rand_case == 0)
	{
		bezier.controlPoint_2 = Point(visibleSize.width, enemyBird->getPositionY() + 200);
		bezier.endPosition = Point(-50, enemyBird->getPositionY() + 200);
	}
	else {
		bezier.controlPoint_2 = Point(visibleSize.width, enemyBird->getPositionY() - 200);
		bezier.endPosition = Point(-50, enemyBird->getPositionY() - 200);
	}
	mAction = BezierTo::create(rand_speed, bezier);

	enemyBirdPhysicBody = PhysicsBody::createBox(enemyBird->getContentSize());
}

void GeneratorEnemy::createPlane(Sprite* &plane, Action* &mAction, PhysicsBody* &planePhysicsBody)
{
	plane = Sprite::create("plane.png");
	plane->setPosition(visibleSize.width + plane->getContentSize().width, rand() % (int)visibleSize.height);
	double rand_speed = 2 / (rand() % 3 + 2);
	mAction = MoveBy::create(rand_speed* MBIRD_MOVEMENT_SPEED * visibleSize.width, Point(-visibleSize.width - 2 * plane->getContentSize().width, 0));

	planePhysicsBody = PhysicsBody::createBox(Size(plane->getContentSize().width - 10, plane->getContentSize().height / 2));
}

void GeneratorEnemy::removeEnemys()
{
	for (int i = 0; i < _enemys.size(); i++)
	{
		if (_enemys.at(i)->getPosition().x < _enemys.at(i)->getBoundingBox().size.width / 2)
		{
			_enemys.at(i)->removeFromParentAndCleanup(true);
			_enemys.erase(i);
		}
		else
		{
			++i;
		}
	}
	CCLOG("remove enemys %d", _enemys.size());
}





//
// 检查Sprite是否超出边界 超出则移除
//void EnemyGenerator::removeEnemys()
//for (int i = 0; i < enemys.size(); i++) 
//{
//	//if (enemys.at(i)->getPosition().x <-enemys.at(i)->getBoundingBox().size.width / 2) 
//	if (enemys.at(i)->getPosition().x < enemys.at(i)->getBoundingBox().size.width / 2) 
//	{
//		enemys.at(i)->removeFromParentAndCleanup(true);
//		enemys.erase(i);
//	}
//	else 
//	{
//		++i;
//	}
//}
//CCLOG("remove enemys %d", enemys.size());
