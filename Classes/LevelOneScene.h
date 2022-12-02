
#ifndef __LEVELONE_SCENE_H__
#define __LEVELONE_SCENE_H__

#include "cocos2d.h"

class LevelOne : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    //void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(LevelOne);

    cocos2d::Sprite* _spriteFondo_1;
    cocos2d::Sprite* _spriteFondo_2;

    cocos2d::Sprite* _spriteChild;
    //obstaculos
    cocos2d::Vector<cocos2d::Sprite*> _obstacles;
    unsigned int score;
    cocos2d::Label* _scoreLabel;



    void onKeyPressed(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event);


    void update(float);
    //Obstaculos
    void addObstacles(float);
    void PointScore(float);
    void doRemoveFromParentAndCleanup(Node* sender, bool cleanup);

    //Sound


    //Physics
    void initPhysics(cocos2d::Sprite* sprite);
    void initPhysicsChild(cocos2d::Sprite* sprite);
    void initPhysicsBorder(cocos2d::Sprite* sprite);

    bool onContactBegin(cocos2d::PhysicsContact& contact);


};

#endif // __HELLOWORLD_SCENE_H__
