#ifndef __LEVELS_MENU_H__
#define __LEVELS_MENU_H__

#include "cocos2d.h"

class LevelsMenu : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(LevelsMenu);
    

    void GoToLevel1(cocos2d::Ref* pSender);
    void GoToLevel2(cocos2d::Ref* pSender);
    void GoToLevel3(cocos2d::Ref* pSender);
    void GoBackToMainMenu(cocos2d::Ref* pSender);
};
#endif // __LEVELS_MENUH__