#ifndef __LEVEL1_H__
#define __LEVEL1_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include <chrono>

#define PTM_RATIO 32.0
using namespace cocos2d;

class Level1 : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();


    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(Level1);

    void setViewPointCenter(cocos2d::Point position);
    void update(float dt );
    
     void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
     void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    //////////////////////////////////////////////////////////////////

    std::map<EventKeyboard::KeyCode, bool> keys;

    float X, Y;

    Point tileCoordForPosition(Vec2 position);
    void setPlayerPosition(Vec2 position);
    void changeIsJumping();
    void changeGravity();

    //////////////////////////////////////////////////////////////////////////////


void updatePhysics(float dt);

private:

    cocos2d::PhysicsBody* tilePhysics;
    cocos2d::TMXTiledMap* map_level1;
    cocos2d::TMXLayer* piege;
    cocos2d::TMXLayer* obstacle;
    cocos2d::TMXLayer* key;
    cocos2d::TMXLayer* theme;
    cocos2d::TMXLayer *_background1;
    cocos2d::TMXLayer* _blockage;
    cocos2d::Sprite* _player;
    cocos2d::PhysicsWorld* sceneWorld;
    int isJumping = 0;
    Rect sizeEnd;
};

#endif // __LEVEL1_H__