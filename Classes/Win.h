#ifndef __WIN_H__
#define __WIN_H__

#include "cocos2d.h"

class Win : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();


    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(Win);
    void GoBackToMainMenu(Ref* psender);

    void GotToLevelsMenu(Ref* psender);

};

#endif // __GAME_OVER_H__