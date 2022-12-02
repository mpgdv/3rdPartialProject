#include "SettingsScene.h"
#include "HelloWorldScene.h"
#include "ScoresScene.h"

USING_NS_CC;

Scene* Settings::createScene()
{
    return Settings::create(); //Physics

}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}


// on "init" you need to initialize your instance
bool Settings::init()
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



    //auto menu_item_1 = MenuItemImage::create("Buttons/spring.png", "Buttons/spring.png", "Buttons/spring.png", CC_CALLBACK_1(Settings::Spring, this));
    //auto menu_item_2 = MenuItemImage::create("Buttons/autumn.png", "Buttons/autumn.png", "Buttons/autumn.png", CC_CALLBACK_1(Settings::Autumn, this));
    auto menu_item_3 = MenuItemImage::create("Buttons/reset.png", "Buttons/reset.png", "Buttons/reset.png", CC_CALLBACK_1(Settings::Reset, this));
    auto return_item = MenuItemImage::create("Buttons/return.png", "Buttons/return.png", "Buttons/return.png", CC_CALLBACK_1(Settings::Return, this));
    //menu_item_1->setScale(0.5);
    //menu_item_2->setScale(0.5);
    menu_item_3->setScale(0.5);
    return_item->setScale(0.3);

    

    //menu_item_1->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 4) * 3 + 10)); // 4-> 3 items +1
    //menu_item_2->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 4) * 2));
    menu_item_3->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    return_item->setPosition(Point(visibleSize.width / 7 - 20, visibleSize.height / 7));

    auto* menu = Menu::create(menu_item_3, return_item, NULL);
    menu->setPosition(Point(0, 0));
    this->addChild(menu);

    return true;
}



void Settings::Reset(cocos2d::Ref* pSender)
{
    CCLOG("Reset");

    //deleteValueForKey
    UserDefault* def = UserDefault::getInstance();
    def->deleteValueForKey("HIGHSCORE_SPRING");
    def->deleteValueForKey("HIGHSCORE_AUTUMN");
    def->deleteValueForKey("HIGHSCORE_WINTER");

    auto scene = Scores::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(1.0f, scene));
}

void Settings::Return(cocos2d::Ref* pSender)
{
    CCLOG("Return");
    auto scene = HelloWorld::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(1.0f, scene));
}


