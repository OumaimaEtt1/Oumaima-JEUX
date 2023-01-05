#include "Level3.h"
#include "Definition.h"
#include "GameOver3.h"
#include "Win.h"
#include "CCEventKeyboard.h"
#include <map>

USING_NS_CC;


int isJumping3 = 0;
int isMoving3 = 0;
float scale3 = -1;

Scene* Level3::createScene()
{
    return Level3::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Level3::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //Ajout du Physics World

    initWithPhysics();
    sceneWorld = getPhysicsWorld();
    sceneWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);

    //Gravité
    sceneWorld->setGravity(Vec2(0, -170));


    //Ajouter Tile Map + Positionnement
    map_level3 = TMXTiledMap::create("Level3.tmx");

    float XX = map_level3->getPosition().x;
    float YY = map_level3->getPosition().y;

    cocos2d::TMXLayer* _background3;

    //Ajouter les calques

    _background3 = map_level3->getLayer("Calque de Tuiles 1");
    piege = map_level3->getLayer("piege");
    obstacles = map_level3->getLayer("obstacles");
    key = map_level3->getLayer("key");
    addChild(map_level3);

    //L'affichage du joueur sur la map

    TMXObjectGroup* objects = map_level3->getObjectGroup("Object-player");
    auto playerShowUpPoint = objects->getObject("PlayerShowUpPoint");

    X = playerShowUpPoint["x"].asFloat();
    Y = playerShowUpPoint["y"].asFloat();

    _player = Sprite::create("player2.png");
    _player->setPosition(Vec2(X, Y));

    //The Physic Material is used to adjust frictionand bouncing effects of colliding objects.
    player_body3 = PhysicsBody::createBox(_player->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.7f));

    player_body3->setDynamic(true);
    player_body3->setRotationEnable(false);
    player_body3->addMass(10);
    _player->setPosition(X, Y);
    _player->setPhysicsBody(player_body3);

    addChild(_player);

    //The speed limit module is used to set the speed of the particles to gradually slow down over the life cycle.
    float limit = player_body3->getVelocityLimit();


    //ajouter un corps physique (Box) pour chaque Tile  
    PhysicsBody* tilePhysics;

    //Largeur de la map
    for (int x = 0; x < 70; x++)
    {
        //Hauteur de la map
        for (int y = 0; y < 40; y++)
        {
            auto spriteTile = _background3->getTileAt(Vec2(x, y));
            if (spriteTile != NULL)
            {
                tilePhysics = PhysicsBody::createBox(Size(24, 24), PhysicsMaterial(0.0f, 0.0f, 2.0f));
                tilePhysics->setDynamic(false);
                tilePhysics->setGravityEnable(false);
                tilePhysics->addMass(100);
                spriteTile->setPhysicsBody(tilePhysics);
            }
        }
    }

    //Ajout d'un un Box dans la partie où il y a le piège

   //Largeur de la map
    for (int x = 0; x < 70; x++)
    {
        //Hauteur de la map
        for (int y = 0; y < 40; y++)
        {
            auto spriteTile = piege->getTileAt(Vec2(x, y));
            if (spriteTile != NULL)
            {
                tilePhysics = PhysicsBody::createBox(Size(5, 5), PhysicsMaterial(0.0f, 0.0f, 2.0f));
                tilePhysics->setDynamic(false); //static is good enough for wall
                tilePhysics->setGravityEnable(false);
                tilePhysics->addMass(100);
                spriteTile->setPhysicsBody(tilePhysics);
            }
        }
    }

    //Ajout d'un un Box dans la partie où il y a les obstacles

  //Largeur de la map
    for (int x = 0; x < 70; x++)
    {
        //Hauteur de la map
        for (int y = 0; y < 40; y++)
        {
            auto spriteTile = obstacles->getTileAt(Vec2(x, y));
            if (spriteTile != NULL)
            {
                tilePhysics = PhysicsBody::createBox(Size(10, 10), PhysicsMaterial(0.0f, 0.0f, 2.0f));
                tilePhysics->setDynamic(false); //static is good enough for wall
                tilePhysics->setGravityEnable(false);
                tilePhysics->addMass(100);
                spriteTile->setPhysicsBody(tilePhysics);
            }
        }
    }


    //Setting keyboard
    auto eventListener3 = EventListenerKeyboard::create();

    eventListener3->onKeyPressed = CC_CALLBACK_2(Level3::onKeyPressed, this);
    eventListener3->onKeyReleased = CC_CALLBACK_2(Level3::onKeyReleased, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener3, this);

    this->scheduleUpdate();


    return true;
}

void Level3::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    keys[keyCode] = true;
}

void Level3::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    keys[keyCode] = false;
}

void Level3::update(float dt)
{
    X = _player->getPosition().x;
    Y = _player->getPosition().y;
    float translate = 100.0 * dt;

    if (keys[EventKeyboard::KeyCode::KEY_LEFT_ARROW] == true ||
        keys[EventKeyboard::KeyCode::KEY_A] == true)
    {
        _player->setScaleX(scale3);
        _player->getPhysicsBody()->setVelocityLimit(70);
        _player->getPhysicsBody()->applyImpulse(Vec2(-145, 0));
    }

    else if (keys[EventKeyboard::KeyCode::KEY_RIGHT_ARROW] == true ||
             keys[EventKeyboard::KeyCode::KEY_D] == true)
         {
            _player->setScaleX(scale3 * -1);
            _player->getPhysicsBody()->setVelocityLimit(70);
            _player->getPhysicsBody()->applyImpulse(Vec2(145, 0));

         }

    else if (keys[EventKeyboard::KeyCode::KEY_DOWN_ARROW] == true ||
             keys[EventKeyboard::KeyCode::KEY_S] == true)
         {
            _player->getPhysicsBody()->applyImpulse(Vec2(0, -10));
         }

    else if
           (keys[EventKeyboard::KeyCode::KEY_UP_ARROW] == true ||
            keys[EventKeyboard::KeyCode::KEY_Z] == true ||
            keys[EventKeyboard::KeyCode::KEY_SPACE] == true)

         {
            if (isJumping3 == 0) {

                 _player->getPhysicsBody()->applyImpulse(Vec2(0, 3500));
                 isJumping3 = 1;
                if (isJumping3 == 1) {
                   _player->getPhysicsBody()->setVelocityLimit(70);
                   _player->getPhysicsBody()->applyImpulse(Vec2(0, 3500));
                   auto dalayJump = DelayTime::create(0.5);
                   auto funcCallback1 = CallFunc::create([&]() {Level3::changeGravity(); });
                   this->runAction(Sequence::create(dalayJump, funcCallback1, NULL));

                   auto delayAction = DelayTime::create(1.0);
                   auto funcCallback = CallFunc::create([&]() {Level3::changeIsJumping(); });
                   this->runAction(Sequence::create(delayAction, funcCallback, NULL));
                }
            }
         }


    //Suivre le joueur lors de son mouvement

    Rect mapsize = map_level3->getBoundingBox();
    auto followplayer = Follow::create(_player, mapsize);
    this->runAction(followplayer);



    for (int x = 0; x < 70; x++)
    {
        for (int y = 0; y < 40; y++)
        {
            auto spriteTilePiege = piege->getTileAt(Vec2(x, y));

            if (spriteTilePiege != NULL)
            {

                //En cas de contact avec le piège---->GameOverScene
                if (spriteTilePiege->getBoundingBox().intersectsRect(_player->getBoundingBox())) {
                    auto scene = GameOver3::create();
                    Director::getInstance()->replaceScene(scene);
                }
            }

        }
    }



    //collision entre KEY et le joueur

    for (int x = 0; x < 70; x++)
    {
        for (int y = 0; y < 40; y++)
        {
            auto spriteTilePiege = key->getTileAt(Vec2(x, y));

            if (spriteTilePiege != NULL)
            {

                //En cas de contact avec le piège---->GameOverScene
                if (spriteTilePiege->getBoundingBox().intersectsRect(_player->getBoundingBox())) {
                    auto scene = Win::create();
                    Director::getInstance()->replaceScene(scene);
                }
            }

        }
    }

}

void Level3::changeIsJumping()
{
    isJumping3 = 0;
    getPhysicsWorld()->setGravity(Vec2(0, -60));
}

void Level3::changeGravity()
{
    getPhysicsWorld()->setGravity(Vec2(0, -20000));
}
