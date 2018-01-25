#ifndef __GAME_OVER_SCENE_H__
#define __GAME_OVER_SCENE_H__

#include "SceneBase.h"

class SceneGameOver : public SceneBase
{
public:
    static Scene* createScene(unsigned int score, int moneyCount);

    virtual bool init();

	void handleScoreAndMoneyCount();

	void setMenu();
	void setScore(unsigned int score);
	void setMoneyCount(int moneyCount);

	CREATE_FUNC(SceneGameOver);
    
private:
	unsigned int _score;
	int _money;
	//SceneGameOver* _layer;

	void goToMainMenuScene(Ref *sender);
	void goToGameScene(Ref *sender);
};

#endif // __GAME_OVER_SCENE_H__
