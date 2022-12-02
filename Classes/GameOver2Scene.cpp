#include "GameOver2Scene.h"
#include "LevelTwoScene.h"
#include "HelloWorldScene.h"


USING_NS_CC;

unsigned int score2;

Scene* GameOver2::createScene(unsigned int tempScore2)
{
    score2 = tempScore2;
    return GameOver2::create(); //Physics

}

// Print useful error message instead of segfaulting when files are not there
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}


// on "init" you need to initialize your instance
bool GameOver2::init()
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
    auto background = Sprite::create("Backgrounds/GameOver.png");

    if (background == nullptr)
    {
        problemLoading("'GameOver.png'"); //HelloWorld.png
    }
    else
    {
        background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        background->setScale(1.01);



        // add the sprite as a child to this layer
        this->addChild(background, 0);
    }



    auto gameover = Label::createWithTTF(" G A M E  O V E R ", "fonts/Marker Felt.ttf", 40);
    gameover->setTextColor(Color4B::BLACK);
    gameover->enableOutline(Color4B::WHITE, 1);
    gameover->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height / 4) * 3 + 30));

   auto scoreLabel = Label::createWithTTF("Score: " + std::to_string(score2), "fonts/Marker Felt.ttf", 25);

    scoreLabel->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height / 4) * 3 - 15));
    scoreLabel->setTextColor(Color4B::BLACK);
    scoreLabel->enableOutline(Color4B::WHITE, 1);


    auto menu_item_1 = MenuItemImage::create("Buttons/retry.png", "Buttons/retry.png", "Buttons/retry.png", CC_CALLBACK_1(GameOver2::Restart, this));
    menu_item_1->setScale(0.5);
    auto menu_item_2 = MenuItemImage::create("Buttons/menu.png", "Buttons/menu.png", "Buttons/menu.png", CC_CALLBACK_1(GameOver2::Menu, this));
    menu_item_2->setScale(0.5);

    menu_item_1->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 4) * 2)); // 4-> 3 items +1
    menu_item_2->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 4) * 1 - 10));

    auto* menu = Menu::create(menu_item_1, menu_item_2, NULL);
    menu->setPosition(Point(0, 0));
    this->addChild(menu, 1);
    this->addChild(gameover, 1);
    this->addChild(scoreLabel, 1);

    //Save high score
    UserDefault* def = UserDefault::getInstance();
    auto highScore = def->getIntegerForKey("HIGHSCORE_AUTUMN", 0);

    if (score2 > highScore)
    {
        highScore = score2;
        def->setIntegerForKey("HIGHSCORE_AUTUMN", highScore);
    }
    def->flush();

    return true;
}


void GameOver2::Restart(cocos2d::Ref* pSender)
{
    CCLOG("Restart");
    auto scene = LevelTwo::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(1.0f, scene));
}

void GameOver2::Menu(cocos2d::Ref* pSender)
{
    CCLOG("Menu");
    auto scene = HelloWorld::createScene();
    Director::getInstance()->pushScene(TransitionFade::create(1.0f, scene));
}

void GameOver2::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    
}

