#ifndef __LEVELS_SCENE_H__
#define __LEVELS_SCENE_H__

#include "cocos2d.h"

class Levels : public cocos2d::Scene
{
    public:
        static cocos2d::Scene* createScene();

        virtual bool init();

        // implement the "static create()" method manually
        CREATE_FUNC(Levels);


        void Spring(Ref* pSpender);
        void Autumn(Ref* pSender);
        void Winter(Ref* pSender);
        void Return(Ref* pSender);

};

#endif