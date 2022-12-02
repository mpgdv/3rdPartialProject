#ifndef __SCORES_SCENE_H__
#define __SCORES_SCENE_H__

#include "cocos2d.h"

    class Scores : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(Scores);
    

    void Play(Ref* pSpender);
    void Highscores(Ref* pSender);
    void Settings(Ref* pSender);
    void Return(Ref* pSpender);

};

#endif // __HELLOWORLD_SCENE_H__
