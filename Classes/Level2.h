#ifndef __LEVEL2_H__
#define __LEVEL2_H__

#include "cocos2d.h"
#include<chrono>

using namespace cocos2d;
class Level2 : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    float X, Y;
    // implement the "static create()" method manually
    CREATE_FUNC(Level2);

    void update(float dt);

    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

   
    //////////////////////////////////////////////////////////////////
    void changeIsJumping();
    void changeGravity();

    std::map<EventKeyboard::KeyCode, bool> keys;

 


private:


    cocos2d::TMXTiledMap* map_level2;
    cocos2d::TMXLayer* _background2;
    cocos2d::TMXLayer* piege;
    cocos2d::TMXLayer* indications;
    cocos2d::TMXLayer* key;
    cocos2d::TMXLayer* obstacles;
    cocos2d::Sprite* _player;
    cocos2d::PhysicsWorld* sceneWorld;
    PhysicsBody* player_body2;

};

#endif // __LEVEL2_H__
