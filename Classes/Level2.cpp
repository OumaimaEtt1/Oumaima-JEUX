#include "Level2.h"
#include "Definition.h"
#include "GameOver2.h"
#include "Win.h"
#include <map>
#include "CCEventKeyboard.h"
#include <iostream>

USING_NS_CC;

int isJumping2 = 0;
int isMoving2 = 0;
float scale2 = -1;

Scene* Level2::createScene()
{
    return Level2::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Level2::init()
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
    map_level2 = TMXTiledMap::create("level two.tmx");

 
    //Ajout des calques

    _background2 = map_level2->getLayer("Calque de Tuiles 1");
    piege = map_level2->getLayer("piege");
    obstacles = map_level2->getLayer("obstacles");
    key = map_level2->getLayer("key");
    indications = map_level2->getLayer("indications");


    addChild(map_level2);


    //L'affichage du joueur sur la map

    TMXObjectGroup* objects = map_level2->getObjectGroup("Object-player");
    auto playerShowUpPoint = objects->getObject("PlayerShowUpPoint");

    X= playerShowUpPoint["x"].asFloat();
    Y= playerShowUpPoint["y"].asFloat();

    _player = Sprite::create("player2.png");
    _player->setPosition(Vec2(X, Y));


    //Introduction de PhysicsBody au joueur

   

    //The Physic Material is used to adjust frictionand bouncing effects of colliding objects.
    player_body2 = PhysicsBody::createBox(_player->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.7f));

    player_body2->setDynamic(true);
    player_body2->setRotationEnable(false);
    player_body2->addMass(10);
    _player->setPosition(X, Y);
    _player->setPhysicsBody(player_body2);

    this->addChild(_player);

    //The speed limit module is used to set the speed of the particles to gradually slow down over the life cycle.
    float limit = player_body2->getVelocityLimit();


    //ajouter un corps physique (Box) pour chaque Tile  
    PhysicsBody* tilePhysics;

    //Largeur de la map
    for (int x = 0; x < 70; x++)
    {
        //Hauteur de la map
        for (int y = 0; y < 40; y++)
        {
            auto spriteTile = _background2->getTileAt(Vec2(x, y));
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
    auto eventListener = EventListenerKeyboard::create();

    eventListener->onKeyPressed = CC_CALLBACK_2(Level2::onKeyPressed, this);
    eventListener->onKeyReleased = CC_CALLBACK_2(Level2::onKeyReleased, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);

    this->scheduleUpdate();


  
    return true;
}



void Level2::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    keys[keyCode] = true;
}

void Level2::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    keys[keyCode] = false;
}

void Level2::update(float dt)
{
    X = _player->getPosition().x;
    Y = _player->getPosition().y;
    float translate = 100.0 * dt;

    if (keys[EventKeyboard::KeyCode::KEY_LEFT_ARROW] == true ||
        keys[EventKeyboard::KeyCode::KEY_A] == true)
    {
        _player->setScaleX(scale2);
        _player->getPhysicsBody()->setVelocityLimit(70);
        _player->getPhysicsBody()->applyImpulse(Vec2(-145, 0));
    }

    else if (keys[EventKeyboard::KeyCode::KEY_RIGHT_ARROW] == true ||
             keys[EventKeyboard::KeyCode::KEY_D] == true)
         {
            _player->setScaleX(scale2 * -1);
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
           if (isJumping2 == 0) {

               _player->getPhysicsBody()->applyImpulse(Vec2(0, 3500));
               isJumping2 = 1;
               if (isJumping2 == 1) {
                  _player->getPhysicsBody()->setVelocityLimit(70);
                  _player->getPhysicsBody()->applyImpulse(Vec2(0, 3500));
                   auto dalayJump = DelayTime::create(0.5);
                   auto funcCallback1 = CallFunc::create([&]() {Level2::changeGravity(); });
                   this->runAction(Sequence::create(dalayJump, funcCallback1, NULL));

                   auto delayAction = DelayTime::create(1.0);
                   auto funcCallback = CallFunc::create([&]() {Level2::changeIsJumping(); });
                   this->runAction(Sequence::create(delayAction, funcCallback, NULL));
               }
           }
         }

    //Suivre le joueur lors de son mouvement

    Rect mapsize = map_level2->getBoundingBox();
    auto followplayer = Follow::create(_player, mapsize);
    this->runAction(followplayer);


    //collision entre le piège et le joueur

    for (int x = 0; x < 70; x++)
    {
        for (int y = 0; y < 40; y++)
        {
            auto spriteTilePiege = piege->getTileAt(Vec2(x, y));

            if (spriteTilePiege != NULL)
            {

                //En cas de contact avec le piège---->GameOverScene
                if (spriteTilePiege->getBoundingBox().intersectsRect(_player->getBoundingBox())) {
                    auto scene = GameOver2::create();
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

void Level2::changeIsJumping()
{
    isJumping2 = 0;
    getPhysicsWorld()->setGravity(Vec2(0, -60));
}

void Level2::changeGravity()
{
    getPhysicsWorld()->setGravity(Vec2(0, -20000));
}

