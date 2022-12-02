#include "HelloWorldScene.h"
#include "ScoresScene.h"
#include "LevelsScene.h"

USING_NS_CC;

Scene* Scores::createScene()
{
    return Scores::create(); //Physics

}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}


// on "init" you need to initialize your instance
bool Scores::init()
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
    auto background = Sprite::create("Backgrounds/highscores.png");

    if (background == nullptr)
    {
        problemLoading("'highscores.png'"); //HelloWorld.png
    }
    else
    {
        background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        background->setScale(1.5);



        // add the sprite as a child to this layer
        this->addChild(background, 0);
    }



   
    auto return_item = MenuItemImage::create("Buttons/return.png", "Buttons/return.png", "Buttons/return.png", CC_CALLBACK_1(Scores::Return, this));
    return_item->setScale(0.3);
    
    auto spring = Sprite::create("Buttons/spring.png");
    auto autumn = Sprite::create("Buttons/autumn.png");
    auto winter = Sprite::create("Buttons/winter.png");
    spring->setScale(0.3);
    autumn->setScale(0.3);
    winter->setScale(0.3);
    
    auto myLabel = Label::createWithTTF("H I G H  S C O R E", "fonts/Marker Felt.ttf", 30);
    myLabel->setTextColor(Color4B::BLACK);
    myLabel->enableOutline(Color4B::WHITE, 1);
    myLabel->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height / 6) * 5 + 15));

    spring->setPosition(Vec2(visibleSize.width / 6, (visibleSize.height / 4) * 3 -15)); // 4-> 3 items +1
    autumn->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height / 4) *3 -15));
    winter->setPosition(Vec2(visibleSize.width / 6 * 5, (visibleSize.height / 4) * 3-15));
    return_item->setPosition(Point(visibleSize.width / 7 - 20, visibleSize.height / 7));

    auto* menu = Menu::create(return_item,NULL);
    menu->setPosition(Point(0,0));
    this->addChild(menu,2);
    this->addChild(spring, 1);
    this->addChild(autumn, 1);
    this->addChild(winter, 1);
    this->addChild(myLabel);

    
    UserDefault* def = UserDefault::getInstance();
    auto highScore_Spring = def->getIntegerForKey("HIGHSCORE_SPRING"); 
    auto highScore_Autumn = def->getIntegerForKey("HIGHSCORE_AUTUMN");
    auto highScore_Winter = def->getIntegerForKey("HIGHSCORE_WINTER");


    auto scoreSpring = Label::createWithTTF(std::to_string(highScore_Spring), "fonts/Marker Felt.ttf", 30);
    scoreSpring->setTextColor(Color4B::BLACK);
    scoreSpring->enableOutline(Color4B::WHITE, 1);
    scoreSpring->setPosition(Vec2(visibleSize.width/6, (visibleSize.height/4)*2 -15));
    this->addChild(scoreSpring, 1);

    auto scoreAutumn = Label::createWithTTF(std::to_string(highScore_Autumn), "fonts/Marker Felt.ttf", 30);
    scoreAutumn->setTextColor(Color4B::BLACK);
    scoreAutumn->enableOutline(Color4B::WHITE, 1);
    scoreAutumn->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height / 4) * 2 - 15));
    this->addChild(scoreAutumn, 1);

    auto scoreWinter = Label::createWithTTF(std::to_string(highScore_Winter), "fonts/Marker Felt.ttf", 30);
    scoreWinter->setTextColor(Color4B::BLACK);
    scoreWinter->enableOutline(Color4B::WHITE, 1);
    scoreWinter->setPosition(Vec2(visibleSize.width / 6 * 5, (visibleSize.height / 4) * 2 - 15));
    this->addChild(scoreWinter, 1);
   
    return true;
}


void Scores::Play(cocos2d::Ref* pSender)
{
    CCLOG("Play");
    auto scene = Levels::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(1.0f,scene));
}

void Scores::Highscores(cocos2d::Ref* pSender)
{
    CCLOG("Highscores");
   // auto scene = Highscore::createScene();
   // Director::getInstance()->pushScene(TransitionFade::create(1.0f, scene));
}

void Scores::Settings(cocos2d::Ref* pSender)
{
    CCLOG("Settings");
}

void Scores::Return(cocos2d::Ref* pSender)
{
    CCLOG("Return");
    auto scene = HelloWorld::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(1.0f, scene));
}

void Scores::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

