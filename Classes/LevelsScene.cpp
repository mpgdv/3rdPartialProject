#include "LevelsScene.h"
#include "LevelOneScene.h"
#include "LevelTwoScene.h"
#include "LevelThreeScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* Levels::createScene()
{
    return Levels::create(); //Physics

}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}


// on "init" you need to initialize your instance
bool Levels::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init()) //(!Scene::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    //Background
    auto background = Sprite::create("Backgrounds/menu.png");

    if (background == nullptr)
    {
        problemLoading("'menu.png'"); //HelloWorld.png
    }
    else
    {
        background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        background->setScale(1.35);



        // add the sprite as a child to this layer
        this->addChild(background, 0);
    }



    auto menu_item_1 = MenuItemImage::create("Buttons/spring.png", "Buttons/spring.png", "Buttons/spring.png", CC_CALLBACK_1(Levels::Spring, this));
    auto menu_item_2 = MenuItemImage::create("Buttons/autumn.png", "Buttons/autumn.png", "Buttons/autumn.png", CC_CALLBACK_1(Levels::Autumn, this));
    auto menu_item_3 = MenuItemImage::create("Buttons/winter.png", "Buttons/winter.png", "Buttons/winter.png", CC_CALLBACK_1(Levels::Winter, this));
    auto return_item = MenuItemImage::create("Buttons/return.png", "Buttons/return.png", "Buttons/return.png", CC_CALLBACK_1(Levels::Return, this));
    menu_item_1->setScale(0.5);
    menu_item_2->setScale(0.5);
    menu_item_3->setScale(0.5);
    return_item->setScale(0.3);

    //menu_item_1->setFontName("fonts/Marker Felt.ttf");


    menu_item_1->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 4) * 3 + 10)); // 4-> 3 items +1
    menu_item_2->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 4) * 2));
    menu_item_3->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 4) * 1 - 10));
    return_item->setPosition(Point(visibleSize.width / 7 - 20, visibleSize.height / 7));

    auto* menu = Menu::create(menu_item_1, menu_item_2, menu_item_3,return_item, NULL);
    menu->setPosition(Point(0, 0));
    this->addChild(menu);

    return true;
}


void Levels::Spring(cocos2d::Ref* pSender)
{
    CCLOG("Spring");
    auto scene = LevelOne::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(1.0f, scene));
}

void Levels::Autumn(cocos2d::Ref* pSender)
{
    CCLOG("Autumn");
    auto scene = LevelTwo::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(1.0f, scene));

}

void Levels::Winter(cocos2d::Ref* pSender)
{
    CCLOG("Winter");
    auto scene = LevelThree::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(1.0f, scene));
}

void Levels::Return(cocos2d::Ref* pSender)
{
    CCLOG("Return");
    auto scene = HelloWorld::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(1.0f, scene));
}


