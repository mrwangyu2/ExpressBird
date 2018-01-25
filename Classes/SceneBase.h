#ifndef __SCENE_BASE_H__
#define __SCENE_BASE_H__

#include<string>

#include "cocos2d.h"
#include "GeneratorMoney.h"
#include "SimpleAudioEngine.h"
#include "GeneratorEnemy.h"
#include "Definitions.h"
#include "Player.h"

using namespace CocosDenshion;
USING_NS_CC;

class SceneBase : public Layer
{
public:
	SceneBase();
	~SceneBase();

protected:
	Size _visibleSize;
	Vec2 _visibleOrigin;

	void setBackground(const std::string& pictureName);
	void getVisible();
};


#endif