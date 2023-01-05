#ifndef __LEVEL3_H__
#define __LEVEL3_H__

#include "cocos2d.h"
#include<chrono>

using namespace cocos2d;

class Level3 : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    float X, Y;
  
    // implement the "static create()" method manually
    CREATE_FUNC(Level3);

    void update(float dt);

    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);


    void changeIsJumping();
    void changeGravity();

    std::map<EventKeyboard::KeyCode, bool> keys;


private:


    cocos2d::TMXTiledMap* map_level3;
    cocos2d::TMXLayer* _background3;
    cocos2d::TMXLayer* piege;
    cocos2d::TMXLayer* indications;
    cocos2d::TMXLayer* key;
    cocos2d::TMXLayer* obstacles;
    cocos2d::Sprite* _player;
    cocos2d::PhysicsWorld* sceneWorld;
    PhysicsBody* player_body3;


};

#endif // __MAIN_MENU_H__
