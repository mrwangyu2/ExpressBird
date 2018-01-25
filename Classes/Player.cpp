#include "Player.h"
#include "Definitions.h"

USING_NS_CC;

const int Player::FlyUpLevel = 400;

bool Player::init() {
	if (!Sprite::init()) {
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	setTag(PLAYER_TAG);

	setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	this->setPlayerPhysicsBody();

	runAction(Animate::create(AnimationCache::getInstance()->getAnimation("flying_bird")));

	return true;
}

void Player::setPlayerPhysicsBody()
{
	auto flappyPhysicsBody = PhysicsBody::createCircle(18);
	flappyPhysicsBody->setPositionOffset(Vec2(15, 12));
	flappyPhysicsBody->setRotationEnable(false);
	flappyPhysicsBody->setAngularVelocityLimit(0);
	flappyPhysicsBody->setMass(PLAYER_MASS);

	flappyPhysicsBody->setCategoryBitmask(0x05);
	flappyPhysicsBody->setCollisionBitmask(0x06);
	flappyPhysicsBody->setContactTestBitmask(0x02);

	setAnchorPoint(Vec2(1, 1));
	setPhysicsBody(flappyPhysicsBody);
}

//´óÄñÏòÉÏ·É
void Player::fly()
{
	getPhysicsBody()->setVelocity(Vec2(0, FlyUpLevel));
}

