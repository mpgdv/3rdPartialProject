#ifndef __GAMEOVER1_SCENE_H__
#define __GAMEOVER1_SCENE_H__

#include "cocos2d.h"

class GameOver1 : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene(unsigned int tempScore);

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(GameOver1);


    void Restart(Ref* pSpender);
    void Menu(Ref* pSender);

};

#endif // __HELLOWORLD_SCENE_H__