#include <iostream>
#include <map>
#include "CCEventKeyboard.h"
#include "Level1.h"
#include "Definition.h"
#include "GameOver.h"
#include "Win.h"

USING_NS_CC;
using namespace std;

int isJumping = 0;
int isMoving = 0;
float scale = -1;

#define __FLT_EPSILON__ 1.19209290e-07F
float _filteredUpdateDelta;

Scene* Level1::createScene()
{
    return Level1::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Level1::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
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
  
    //Ajout de Tile Map + Positionnement
    map_level1 = TMXTiledMap::create("Level1test.tmx");

    float XX = map_level1->getPosition().x;
    float YY = map_level1->getPosition().y;

    //Ajouter les calques
    _background1 = map_level1->getLayer("Level1");
    theme = map_level1->getLayer("theme");
    piege = map_level1->getLayer("piège");
    obstacle = map_level1->getLayer("obstacle");
    key = map_level1->getLayer("key");
    addChild(map_level1);
    
    
    //L'affichage du joueur sur la map

    TMXObjectGroup* objects = map_level1->getObjectGroup("Object-player");
    auto playerShowUpPoint = objects->getObject("PlayerShowUpPoint");
    
    float x = playerShowUpPoint["x"].asFloat();
    float y = playerShowUpPoint["y"].asFloat();

    _player = Sprite::create("player2.png");
    

    //Introduction de PhysicsBody au joueur
    PhysicsBody* player_body;

    //The Physic Material is used to adjust frictionand bouncing effects of colliding objects.
    player_body = PhysicsBody::createBox(_player->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.7f)); 

    player_body->setDynamic(true);
    player_body->setRotationEnable(false);         
    player_body->addMass(10);
    _player->setPosition(x, y);
    _player->setPhysicsBody(player_body);
  
    this->addChild(_player);

    //The speed limit module is used to set the speed of the particles to gradually slow down over the life cycle.
    float limit = player_body->getVelocityLimit();


    //Ajout d'un corps physique (Box) pour chaque Tile  

    PhysicsBody* tilePhysics;

    //Largeur de la map
    for (int x = 0; x < 70; x++)       
    {
        //Hauteur de la map
        for (int y = 0; y < 32; y++)   
        {
            auto spriteTile = _background1->getTileAt(Vec2(x, y));
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
        for (int y = 0; y < 32; y++)   
        {
            auto spriteTile = piege->getTileAt(Vec2(x, y));
            if (spriteTile != NULL)
            {
                tilePhysics = PhysicsBody::createBox(Size(5, 5), PhysicsMaterial(0.0f, 0.0f, 2.0f));
                tilePhysics->setDynamic(false); 
                tilePhysics->setGravityEnable(false);
                tilePhysics->addMass(100);
                spriteTile->setPhysicsBody(tilePhysics);
            }
        }
    }

   //Setting keyboard
    auto eventListener = EventListenerKeyboard::create();

    eventListener->onKeyPressed = CC_CALLBACK_2(Level1::onKeyPressed, this);
    eventListener->onKeyReleased = CC_CALLBACK_2(Level1::onKeyReleased, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);

    auto eventlistener1 = EventListenerKeyboard::create();


    this->scheduleUpdate();

    return true;
}

void Level1::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    keys[keyCode] = true;
}

void Level1::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    keys[keyCode] = false;
}

void Level1::update(float dt)
{
    X = _player->getPosition().x;
    Y = _player->getPosition().y;
    float translate = 100.0 * dt;

    if (keys[EventKeyboard::KeyCode::KEY_LEFT_ARROW] == true ||
        keys[EventKeyboard::KeyCode::KEY_A] == true)
    {
        _player->setScaleX(scale);
        _player->getPhysicsBody()->setVelocityLimit(70);
        _player->getPhysicsBody()->applyImpulse(Vec2(-145, 0));
    }

    else if (keys[EventKeyboard::KeyCode::KEY_RIGHT_ARROW] == true ||
            keys[EventKeyboard::KeyCode::KEY_D] ==  true)
         {
            _player->setScaleX(scale * -1);
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
              keys[EventKeyboard::KeyCode::KEY_SPACE] == true )

          {
            if (isJumping == 0) {
      
               _player->getPhysicsBody()->applyImpulse(Vec2(0 , 3500));
               isJumping = 1;
               if (isJumping == 1) {
                  _player->getPhysicsBody()->setVelocityLimit(70);
                  _player->getPhysicsBody()->applyImpulse(Vec2(0, 3500));
                  auto dalayJump = DelayTime::create(0.5);
                  auto funcCallback1 = CallFunc::create([&]() {Level1::changeGravity(); });
                  this->runAction(Sequence::create(dalayJump, funcCallback1, NULL));

                  auto delayAction = DelayTime::create(1);
                  auto funcCallback = CallFunc::create([&]() {Level1::changeIsJumping(); });
                  this->runAction(Sequence::create(delayAction, funcCallback, NULL));
               }
            }
          }

   //Suivre le joueur lors de son mouvement

   Rect mapsize = map_level1->getBoundingBox();
   auto followplayer = Follow::create(_player, mapsize);
   this->runAction(followplayer);


   //collision entre le piège et le joueur

   for (int x = 0; x < 70; x++)      
   {
       for (int y = 0; y < 32; y++)   
       {
           auto spriteTilePiege = piege->getTileAt(Vec2(x, y));
           if (spriteTilePiege != NULL)
           {

            //En cas de contact avec le piège---->GameOverScene
               if (spriteTilePiege->getBoundingBox().intersectsRect(_player->getBoundingBox())) {
                   auto scene = GameOver::create();
                   Director::getInstance()->replaceScene( scene);
               }
           }
           
       }
   }

   //collision entre key et le joueur

   for (int x = 0; x < 70; x++)     
   {
       for (int y = 0; y < 32; y++)   
       {
           auto spriteTileKey = key->getTileAt(Vec2(x, y));
           if (spriteTileKey != NULL)
           {
               //En cas de contact avec KEY---->WinScene
               if (spriteTileKey->getBoundingBox().intersectsRect(_player->getBoundingBox())) {
                   auto scene = Win::create();
                   Director::getInstance()->replaceScene(scene);
               }
           }
       }
   }

}


void Level1::changeIsJumping()
{
    isJumping = 0;
    getPhysicsWorld()->setGravity(Vec2(0, -110));
}

void Level1::changeGravity()
{
    getPhysicsWorld()->setGravity(Vec2(0, -20000));
}









