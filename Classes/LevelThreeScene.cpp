#include "LevelThreeScene.h"
#include "GameOver3Scene.h" //Change to 2
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* LevelThree::createScene()
{
    return LevelThree::create(); //Physics

}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}


// on "init" you need to initialize your instance
bool LevelThree::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::initWithPhysics()) //(!Scene::init())
    {
        return false;
    }

    //physics
    this->getPhysicsWorld()->setGravity(Vect(0, 0));
    //this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    //Event Listener
    auto listener = EventListenerKeyboard().create();
    listener->onKeyPressed = CC_CALLBACK_2(LevelThree::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    //Collisions
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(LevelThree::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);


    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    score = 0;



    _spriteFondo_1 = Sprite::create("Backgrounds/Background_Winter.png");
    _spriteFondo_2 = Sprite::create("Backgrounds/Background_Winter.png");



    // Generate polygon info automatically.
    //auto pinfoChild = AutoPolygon::generatePolygon("Character/run1.png");

    // Create a sprite with polygon info.
    //_spriteChild = Sprite::create(pinfoChild);
    _spriteChild = Sprite::create("Character/run1.png");

    if (_spriteFondo_1 == nullptr)
    {
        problemLoading("'Background_Winter.png'"); //HelloWorld.png
    }
    else
    {
        // position the sprite on the center of the screen
        _spriteFondo_1->setScale(1.49);
        _spriteFondo_1->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(_spriteFondo_1, 0);
    }

    if (_spriteFondo_2 == nullptr)
    {
        problemLoading("'Background_Winter.png'"); //HelloWorld.png
    }
    else
    {
        // position the sprite on the center of the screen
        _spriteFondo_2->setScale(1.49);
        _spriteFondo_2->setPosition(Point(visibleSize.width + visibleSize.width / 2, visibleSize.height / 2 + origin.y));

        this->addChild(_spriteFondo_2, 0);

    }

    auto sprite_action_1 = RepeatForever::create(MoveBy::create(2.0, Vec2(-visibleSize.width / 2, 0)));
    _spriteFondo_1->runAction(sprite_action_1);
    auto sprite_action_2 = RepeatForever::create(MoveBy::create(2.0, Vec2(-visibleSize.width / 2, 0)));
    _spriteFondo_2->runAction(sprite_action_2);

    this->scheduleUpdate();


    if (_spriteChild == nullptr)
    {
        problemLoading("'run1.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        _spriteChild->setScale(1.49);
        _spriteChild->setPosition(Vec2(150, visibleSize.height / 4.5));

        // add the sprite as a child to this layer
        initPhysicsChild(_spriteChild);
        this->addChild(_spriteChild, 1);
    }
    schedule(CC_SCHEDULE_SELECTOR(LevelThree::addObstacles), 3.0f);
    schedule(CC_SCHEDULE_SELECTOR(LevelThree::PointScore), 0.7f);



    auto scoreLab = Label::createWithTTF("Score: ", "fonts/Marker Felt.ttf", 16);
    _scoreLabel = Label::createWithTTF(std::to_string(score), "fonts/Marker Felt.ttf", 16);

    scoreLab->setPosition(Vec2(50, visibleSize.height - 20));
    _scoreLabel->setPosition(Vec2(scoreLab->getPosition().x + 40, visibleSize.height - 20));

    _scoreLabel->setTextColor(Color4B::BLACK);
    _scoreLabel->enableOutline(Color4B::WHITE, 1);
    scoreLab->setTextColor(Color4B::BLACK);
    scoreLab->enableOutline(Color4B::WHITE, 1);

    auto myLabel = Label::createWithTTF("W I N T E R", "fonts/Marker Felt.ttf", 20);
    myLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 20));

    // shadow effect is supported by all Label types
    myLabel->enableShadow();

    //Barrera
    auto border = Sprite::create("Obstacles/border.png");
    border->setAnchorPoint(Vec2::ZERO);
    border->setPosition(Point(0, visibleSize.height / 8 - 15));
    initPhysicsBorder(border);
    this->addChild(border, 1);

    this->addChild(_scoreLabel, 1);
    this->addChild(scoreLab, 1);
    this->addChild(myLabel, 1);

    return true;
}


void LevelThree::update(float delta)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    if (_spriteFondo_1->getPosition().x <= -visibleSize.width / 2)
    {
        _spriteFondo_1->setPosition(Vec2(visibleSize.width + visibleSize.width / 2 - 2, visibleSize.height / 2 + origin.y));
    }

    if (_spriteFondo_2->getPosition().x <= -visibleSize.width / 2)
    {
        _spriteFondo_2->setPosition(Vec2(visibleSize.width + visibleSize.width / 2 - 2, visibleSize.height / 2 + origin.y));
    }

    //score++;
    //_scoreLabel->setString(std::to_string(score));
}


void LevelThree::PointScore(float delta)
{
    score++;
    _scoreLabel->setString(std::to_string(score));
}


//Jump

void LevelThree::onKeyPressed(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event)
{

    auto visibleSize = Director::getInstance()->getVisibleSize();

    if (key == EventKeyboard::KeyCode::KEY_SPACE)
    {
        auto jump1 = MoveTo::create(0.5, Vec2(150, visibleSize.height / 3 + 20));
        auto landing = MoveTo::create(0.5, Vec2(150, visibleSize.height / 4.5));

        auto seq = Sequence::create(jump1, landing, nullptr);
        _spriteChild->runAction(seq);

    }

}

bool LevelThree::onContactBegin(cocos2d::PhysicsContact& contact)
{
    PhysicsBody* a = contact.getShapeA()->getBody();
    PhysicsBody* b = contact.getShapeB()->getBody();

    //Check if the bodies have collided

    if ((1 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask()) || (2 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()))
    {
        CCLOG("Collision has occured");

        auto scene = GameOver3::createScene(score);
        Director::getInstance()->pushScene(TransitionFade::create(0.2f, scene));

    }
    return true;
}



void LevelThree::addObstacles(float delta)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    char obstacles[6][23]
        = { "Obstacles/banana.png", "Obstacles/garbage.png", "Obstacles/sewer.png","Obstacles/snowball.png","Obstacles/snowman.png","Obstacles/tree.png"};

    Sprite* obstacle = nullptr;
    obstacle = Sprite::create(obstacles[random(0, 5)]);
    obstacle->setScale(1.5);
    obstacle->setPosition(Vec2(visibleSize.width, visibleSize.height / 5.5));

    initPhysics(obstacle);
    obstacle->getPhysicsBody();
    _obstacles.pushBack(obstacle);
    this->addChild(obstacle, 1);

    auto action = Sequence::create(
        MoveBy::create(2.0, Vec2(-visibleSize.width - 10, 0)),
        CallFuncN::create(CC_CALLBACK_1(LevelThree::doRemoveFromParentAndCleanup, this, true)),
        NULL);

    obstacle->runAction(action);


}

void LevelThree::doRemoveFromParentAndCleanup(Node* sender, bool cleanup)
{
    sender->removeFromParentAndCleanup(cleanup);
}

void LevelThree::initPhysics(cocos2d::Sprite* sprite)
{
    auto body = PhysicsBody::createCircle(sprite->getContentSize().width / 4 + 0.5);
    body->setContactTestBitmask(2);
    //
    body->setCollisionBitmask(2);
    body->setDynamic(true);
    sprite->setPhysicsBody(body);

}

void LevelThree::initPhysicsChild(cocos2d::Sprite* sprite)
{
    //auto body = PhysicsBody::createCircle(sprite->getContentSize().width / 4 + 0.5);
    auto body = PhysicsBody::createBox(Size(sprite->getContentSize().width / 2 - 10, sprite->getContentSize().height - 10), PhysicsMaterial(0, 0, 0));
    body->setContactTestBitmask(1);
    //
    body->setCollisionBitmask(1);
    body->setDynamic(true);
    sprite->setPhysicsBody(body);

}


void LevelThree::initPhysicsBorder(cocos2d::Sprite* sprite)
{
    auto spriteBody = PhysicsBody::createBox(sprite->getContentSize(), PhysicsMaterial(0, 0, 0));
    spriteBody->setContactTestBitmask(2);
    spriteBody->setCollisionBitmask(2);

    spriteBody->setDynamic(false);
    sprite->setPhysicsBody(spriteBody);

}
