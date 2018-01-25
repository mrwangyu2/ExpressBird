#include "SceneGame.h"
#include "SceneGameOver.h"

Scene* SceneGame::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0, -WORLD_GRAVITY));

	auto layer = SceneGame::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());

	layer->createJoint();

	scene->addChild(layer);
	return scene;
}

bool SceneGame::init()
{
	if (!Layer::init())
	{
		return false;
	}

	this->getVisible();

	this->setMusic();
	this->setBackground("bg.jpg");
	this->setEdge();
	this->setReadyStep();

	this->createBirdByPlayer();
	this->createPackage();

	this->initializeInfomation();

	this->scheduleUpdate();

	return true;
}

void SceneGame::setMusic()
{
	this->preloadMusic();
	this->playBackgroundMusic();
}

void SceneGame::preloadMusic() {
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/bgm.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/Point.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/Wing.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music/Hit.mp3");
}

void SceneGame::playBackgroundMusic() {
	SimpleAudioEngine::getInstance()->playBackgroundMusic("music/bgm.mp3", true);
}

void SceneGame::setEdge()
{
	auto edgeBody = PhysicsBody::createEdgeBox(this->_visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	edgeBody->setCollisionBitmask(ENEMY_SPAWN_FREQUENCY);
	edgeBody->setContactTestBitmask(true);

	// 屏幕边界
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(this->_visibleSize.width / 2 + this->_visibleOrigin.x, this->_visibleSize.height / 2 + this->_visibleOrigin.y));

	edgeNode->setPhysicsBody(edgeBody);

	this->addChild(edgeNode);
}

void SceneGame::setReadyStep()
{
	scheduleOnce(schedule_selector(SceneGame::ready), 5.0f);
	this->ready(1.0f);

	_labelReady = Label::createWithTTF("Ready", "fonts/Marker Felt.ttf", 50);
	//readyLabel = Label::createWithTTF(FontToUTF8("准备颜色条等等d说东方闪电第三方第三方的说的范德萨发大水第三方第三方"), "fonts/Msyh.ttf", 13);
	_labelReady->setTextColor(Color4B::BLACK);
	_labelReady->setPosition(-100, this->_visibleSize.height - 100);

	addChild(_labelReady);

	_labelReady->runAction(MoveTo::create(1.0f, Vec2(this->_visibleSize.width / 2, this->_visibleSize.height - 100)));
}

void SceneGame::ready(float dt)
{
	//监听器注册
	this->registerListener();

	//随机出现各种阻碍物
	this->schedule(schedule_selector(SceneGame::newEnemy), ENEMY_SPAWN_FREQUENCY * this->_visibleSize.width);

	//每隔3秒随机出现金币
	this->schedule(schedule_selector(SceneGame::newMoney), MONEY_SPAWN_FREQUENCY);

}

void SceneGame::registerListener()
{
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(SceneGame::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(SceneGame::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(SceneGame::onKeyPressed, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void SceneGame::createBirdByPlayer()
{
	_player = Player::create();
	addChild(_player);
}

void SceneGame::createPackage()
{
	_package = Sprite::create("package.png");
	_package->setPosition(_player->getPosition() - Vec2(15, 112));
	_package->setPhysicsBody(PhysicsBody::createBox(_package->getContentSize()));
	_package->getPhysicsBody()->setMass(PACKAGE_MASS);
	_package->getPhysicsBody()->setRotationEnable(false);
	_package->setScale(0.5);

	_package->getPhysicsBody()->setCategoryBitmask(0x05);
	_package->getPhysicsBody()->setCollisionBitmask(0x06);
	_package->getPhysicsBody()->setContactTestBitmask(0x00);

	// 初始化受力
	_player->getPhysicsBody()->applyForce(Vec2(INTERACTION_FORCE, (PLAYER_MASS + PACKAGE_MASS)*WORLD_GRAVITY + 5000));
	_package->getPhysicsBody()->applyForce(Vec2(-INTERACTION_FORCE, 0));

	addChild(_package);
}

void SceneGame::initializeInfomation()
{
	//大鸟的持久时间
	_score = 0;
	_scoreLock = 10;

	TTFConfig ttfConfig;
	ttfConfig.fontFilePath = "fonts/Marker Felt.ttf";
	ttfConfig.fontSize = 36;

	_labelScore = Label::createWithTTF(ttfConfig, "0");
	_labelScore->setColor(Color3B::WHITE);
	_labelScore->setPosition(Point(this->_visibleSize.width / 2 + this->_visibleOrigin.x, this->_visibleSize.height * 0.9 + this->_visibleOrigin.y));

	this->addChild(_labelScore, 10000);

	//大鸟捡到的钱数
	_moneyCount = 0;
	_labelMoney = Label::createWithTTF(ttfConfig, "0");
	_labelMoney->setPosition(Vec2(this->_visibleOrigin.x + this->_visibleSize.width / 2 + 100, this->_visibleSize.height * 0.9 + this->_visibleOrigin.y));
	addChild(_labelMoney, 10000);
}

void SceneGame::createJoint()
{
	Sprite* previousJointSprite = NULL;

	for (int i = 0; i < JOINT_AMOUNT; i++)
	{
		Sprite* jointSprite = NULL;

		if (i == 0)
		{
			jointSprite = createJointChain(this->_player);
		}
		else
		{
			jointSprite = createJointChain(previousJointSprite);
		}

		previousJointSprite = jointSprite;

		if (i == (JOINT_AMOUNT - 1))
		{
			this->addJointToNext(jointSprite, this->_package);
		}
	}
}

Sprite* SceneGame::createJointChain(Sprite* previousJointSprite)
{
	Sprite* jointSprite = NULL;
	PhysicsBody* jointPhysicBody = NULL;

	jointSprite = Sprite::create();
	jointSprite->setTextureRect(Rect(0, 0, 10, 10));
	jointPhysicBody = PhysicsBody::createCircle(jointSprite->getContentSize().width / 2, PhysicsMaterial(1.0f, 0.0f, 0.0f));
	jointPhysicBody->setRotationEnable(false);
	jointPhysicBody->setMass(1);
	jointSprite->setPhysicsBody(jointPhysicBody);

	jointSprite->setPosition(previousJointSprite->getPositionX(), previousJointSprite->getPositionY() - 10);
	this->addChild(jointSprite);

	this->addJointToNext(previousJointSprite, jointSprite);

	return jointSprite;
}

void SceneGame::addJointToNext(Sprite* previousJointSprite, Sprite* jointSprite)
{
	auto joint = PhysicsJointDistance::construct(previousJointSprite->getPhysicsBody(), jointSprite->getPhysicsBody(), Point::ZERO, Point::ZERO);
	this->_sceneWorld->addJoint(joint);
}

void SceneGame::newMoney(float dt) {
	Vector<Node*> moneys = GeneratorMoney::getInstance()->generateMoney();
	for (int i = 0; i < moneys.size(); i++) {
		this->addChild(moneys.at(i));
	}
}

void SceneGame::newEnemy(float dt)
{
	this->addChild(GeneratorEnemy::getInstance()->GenerateEnemy());
}

bool SceneGame::onContactBegin(cocos2d::PhysicsContact &contact)
{
	Node * a = contact.getShapeA()->getBody()->getNode();
	Node * b = contact.getShapeB()->getBody()->getNode();

	if (nullptr == a || nullptr == b) return true;

	if (a->getTag() == ENEMY_TAG && b->getTag() == PLAYER_TAG || b->getTag() == ENEMY_TAG && a->getTag() == PLAYER_TAG)
	{
		contactBetweenEnemyAndPlayer();
	}
	else if (a->getTag() == MONEY_TAG && b->getTag() == PLAYER_TAG)
	{
		this->contactBetweenMoneyAndPlayer(b, a, a);
	}
	else if (b->getTag() == MONEY_TAG && a->getTag() == PLAYER_TAG)
	{
		this->contactBetweenMoneyAndPlayer(b, a, b);
	}

	return true;
}

void SceneGame::contactBetweenEnemyAndPlayer()
{
	SimpleAudioEngine::getInstance()->playEffect("music/Hit.mp3");
	this->unscheduleAllSelectors();
	delete GeneratorMoney::getInstance();
	delete GeneratorEnemy::getInstance();
	auto scene = SceneGameOver::createScene(_score, _moneyCount);
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void SceneGame::contactBetweenMoneyAndPlayer(Node* b, Node* a, Node* money)
{
	SimpleAudioEngine::getInstance()->playEffect("music/Point.mp3");

	auto ps = ParticleSystemQuad::create("explode.plist");
	ps->setPosition(b->getPosition());
	this->addChild(ps);

	GeneratorMoney::getInstance()->obtainMoney(money);
	_moneyCount++;
	_labelMoney->setString(Value(_moneyCount).asString());
}

bool SceneGame::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	SimpleAudioEngine::getInstance()->playEffect("music/Wing.mp3");
	_player->fly();
	return true;
}

void SceneGame::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW
		|| keyCode == EventKeyboard::KeyCode::KEY_ENTER
		|| keyCode == EventKeyboard::KeyCode::KEY_SPACE) {

		SimpleAudioEngine::getInstance()->playEffect("music/Wing.mp3");
		_player->fly();
	}
}

//定时器来每帧进行控制
void SceneGame::update(float dt)
{
	this->countBiredKeepTime(dt);

	//每帧判断障碍物和金币 是否移动到屏幕之外，是就移除
	GeneratorEnemy::getInstance()->removeEnemys();
	GeneratorMoney::getInstance()->removeMoney();

	// 自动修正鸟儿位置
	if (_player->getPositionX() < this->_visibleSize.width / 2 - 10)
	{
		_player->setPositionX(_player->getPositionX() + 5);
	}
	else if (_player->getPositionX() > this->_visibleSize.width / 2 + 10)
	{
		_player->setPositionX(_player->getPositionX() - 5);
	}

	// 快递包裹位置修复
	if (_package->getPositionY() > _player->getPositionY())
	{
		_package->setPositionX(_package->getPositionX() - 1);
	}

	//如果大鸟位置在屏幕边缘之外，也就是掉地，就要挂
	if (_player->getPosition().y < -10 || _player->getPosition().y > this->_visibleSize.height + 50) {
		this->unscheduleAllSelectors();
		delete GeneratorMoney::getInstance();
		delete GeneratorEnemy::getInstance();
		auto scene = SceneGameOver::createScene(_score, _moneyCount);
		Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
	}

}

void SceneGame::countBiredKeepTime(float dt)
{
	//定时器来每帧进行计时 考虑dt保证以时间作为度量而非帧数
	if (_scoreLock <= 0) {
		_scoreLock = 10;
		_score += 1;
		_labelScore->setString(String::createWithFormat("%i", _score)->_string);
	}
	else {
		_scoreLock -= dt * 100;
	}

	CCLOG("time %d", dt);
}











