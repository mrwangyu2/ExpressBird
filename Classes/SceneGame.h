#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "SceneBase.h"

class SceneGame : public SceneBase
{
public:
    static Scene* createScene();

	virtual bool init();

	CREATE_FUNC(SceneGame);
    
private:
    PhysicsWorld*_sceneWorld;
    
	Player* _player;
	Sprite* _package;

    Label* _labelScore;
	Label* _labelMoney;
	Label* _labelReady;
    
    unsigned int _score;
	int _moneyCount;
	float _scoreLock;

	void initializeInfomation();
	void addJointToNext(Sprite* previousJointSprite, Sprite* jointSprite);

	void createBirdByPlayer();
	void createPackage();
	void createJoint();
	Sprite* createJointChain(Sprite* previousJointSprite);

	void setReadyStep();
	void setEdge();
	void setMusic();
	inline void setPhysicsWorld(PhysicsWorld *world) { _sceneWorld = world; };


	void preloadMusic();
	void playBackgroundMusic();

	void ready(float dt);

	void registerListener();


    void newEnemy(float dt);
	void newMoney(float dt);
    
    bool onContactBegin(PhysicsContact &contact);

	void contactBetweenEnemyAndPlayer();


	void contactBetweenMoneyAndPlayer(Node* b, Node* a, Node* money);

	bool onTouchBegan(Touch *touch, Event *event);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event);
    
    void update(float dt);

	void countBiredKeepTime(float dt);

};

#endif // __GAME_SCENE_H__
