#ifndef __GAME_OVER_H__
#define __GAME_OVER_H__

#include "cocos2d.h"

class GameOver2 : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();


    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(GameOver2);

    void GotoLevel2(Ref* psender);
    void GoBackToMainMenu(cocos2d::Ref* pSender);




};

#endif // __GAME_OVER_H__

