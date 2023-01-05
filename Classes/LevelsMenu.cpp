#include "LevelsMenu.h"
#include "MainMenu.h"
#include "Definition.h"
#include "Win.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"

USING_NS_CC;
using namespace ui;

Scene* LevelsMenu::createScene()
{
    return LevelsMenu::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool LevelsMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
  
   //insertion du background et ajustement de sa taille pour prendre l'intégralité de l'écran

    auto backgroundlevel = Sprite::create("levels background.jpg");
    backgroundlevel->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y));
    this->addChild(backgroundlevel);

    float rX = visibleSize.width / backgroundlevel->getContentSize().width;
    float rY = visibleSize.height / backgroundlevel->getContentSize().height;

    backgroundlevel->setScaleX(rX);
    backgroundlevel->setScaleY(rY);

 
  //Ajout des boutons des levels 1, 2 et 3 + leurs positionnement

    auto menuitem_Level1 = MenuItemImage::create("lvl1.png", "Lvl1.png", CC_CALLBACK_1(LevelsMenu::GoToLevel1, this));
    auto menuitem_Level2 = MenuItemImage::create("lvl2.png", "lvl2.png", CC_CALLBACK_1(LevelsMenu::GoToLevel2, this));
    auto menuitem_Level3 = MenuItemImage::create("lvl3.png", "lvl3.png", CC_CALLBACK_1(LevelsMenu::GoToLevel3, this));

    auto Home_button = MenuItemImage::create("home.png", "home.png", CC_CALLBACK_1(LevelsMenu::GoBackToMainMenu, this));

    menuitem_Level1->setPosition(Vec2(130, 160));
    menuitem_Level2->setPosition(Vec2(240, 160));
    menuitem_Level3->setPosition(Vec2(340, 160));

    Home_button->setPosition(Vec2(450, 270));

    auto* level_menu = Menu::create(menuitem_Level1, menuitem_Level2, menuitem_Level3, Home_button, NULL);
    level_menu->setPosition(Point(0, 0));
    this->addChild(level_menu);
    
    return true;
}

//Redirection vers une autre page selon le choix de l'utilisateur

void LevelsMenu::GoBackToMainMenu(Ref* pSender)
{
    auto scene1 = MainMenu::create();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME,scene1));
}
void LevelsMenu::GoToLevel1(Ref* pSender)
{
    auto sceneLevel1 = Level1::create();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, sceneLevel1));
}
void LevelsMenu::GoToLevel2(Ref* pSender)
{
    auto sceneLevel2 = Level2::create();

    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, sceneLevel2));
}
void LevelsMenu::GoToLevel3(Ref* pSender)
{
    auto sceneLevel3 = Level3::create();

    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, sceneLevel3));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////