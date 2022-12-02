#include "HelloWorldScene.h"
#include "ScoresScene.h"
#include "LevelsScene.h"
#include "SettingsScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create(); //Physics

}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}


// on "init" you need to initialize your instance
bool HelloWorld::init()
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



    auto menu_item_1 = MenuItemImage::create("Buttons/play.png","Buttons/play.png","Buttons/play.png", CC_CALLBACK_1(HelloWorld::Play, this));
    auto menu_item_2 = MenuItemImage::create("Buttons/scores.png", "Buttons/scores.png", "Buttons/scores.png", CC_CALLBACK_1(HelloWorld::Highscores, this));
    auto menu_item_3 = MenuItemImage::create("Buttons/settings.png", "Buttons/settings.png", "Buttons/settings.png", CC_CALLBACK_1(HelloWorld::Settings, this));

    menu_item_1->setScale(0.5);
    menu_item_2->setScale(0.5);
    menu_item_3->setScale(0.5);

    //menu_item_1->setFontName("fonts/Marker Felt.ttf");
    

    menu_item_1->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 4) * 3 + 10)); // 4-> 3 items +1
    menu_item_2->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 4) * 2));
    menu_item_3->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 4) * 1 - 10));

    auto* menu = Menu::create(menu_item_1,menu_item_2,menu_item_3,NULL);
    menu->setPosition(Point(0,0));
    this->addChild(menu);
   
    return true;
}


void HelloWorld::Play(cocos2d::Ref* pSender)
{
    CCLOG("Play");
    auto scene = Levels::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(1.0f,scene));
}

void HelloWorld::Highscores(cocos2d::Ref* pSender)
{
    CCLOG("Highscores");
    auto scene = Scores::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(1.0f, scene));
}

void HelloWorld::Settings(cocos2d::Ref* pSender)
{
    CCLOG("Settings");
    auto scene = Settings::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(1.0f, scene));

}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

