#ifndef __SPLASH_SCENE_H__
#define __SPLASH_SCENE_H__

#include "SceneBase.h"

class SceneSplash : public SceneBase
{
public:
    static Scene* createScene();

    virtual bool init();

	CREATE_FUNC(SceneSplash);
    
private:
    void goToMainMenuScene(float dt);
    
};

#endif // __SPLASH_SCENE_H__
