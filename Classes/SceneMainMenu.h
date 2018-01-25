#ifndef __MAIN_MENU_SCENE_H__
#define __MAIN_MENU_SCENE_H__

#include "SceneBase.h"

class SceneMainMenu : public SceneBase 
{
public:
    static Scene* createScene();

    virtual bool init();

	CREATE_FUNC(SceneMainMenu);
    
private:
	void setMainMenu();
    void goToGameScene(Ref *sender );
    
};

#endif // __MAIN_MENU_SCENE_H__
