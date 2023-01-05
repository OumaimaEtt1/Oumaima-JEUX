#include "Win.h"
#include "Definition.h"
#include "MainMenu.h"
#include "LevelsMenu.h"
#include "Level1.h"



USING_NS_CC;

Scene* Win::createScene()
{
    return Win::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Win::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //Création de la scène Win + positionnement

    auto background = Sprite::create("win.png");
    background->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y));
    this->addChild(background);


    float rX = visibleSize.width / background->getContentSize().width;
    float rY = visibleSize.height / background->getContentSize().height;

    background->setScaleX(rX);
    background->setScaleY(rY);


    //Création des boutons home et menu 

    auto home = MenuItemImage::create("home.png", "home.png", CC_CALLBACK_1(Win::GoBackToMainMenu, this));
    auto levelmenu = MenuItemImage::create("menu.png", "menu.png", CC_CALLBACK_1(Win::GotToLevelsMenu, this));
    levelmenu->setScale(1);
    levelmenu->setPosition(Vec2(170, 170));

    home->setPosition(Vec2(450, 270));

    auto menu = Menu::create(levelmenu, home, NULL);
    menu->setPosition(Point(0, 0));

    this->addChild(menu);

    return true;
}


//Clic sur Home
void Win::GoBackToMainMenu(Ref* pSender)
{
    auto scene1 = MainMenu::create();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene1));
}

//Clic sur Menu
void Win::GotToLevelsMenu(cocos2d::Ref* pSender)
{
    auto scene = LevelsMenu::create();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
