#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class Player : public Sprite
{
public:
	static const int FlyUpLevel;

	CREATE_FUNC(Player);
	virtual bool init();

	void setPlayerPhysicsBody();


    void fly( );
    
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
};

#endif // __PLAYER_H__
