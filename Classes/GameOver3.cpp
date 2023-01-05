#include "GameOver3.h"
#include "Definition.h"
#include "Level3.h"
#include "MainMenu.h"


USING_NS_CC;

Scene* GameOver3::createScene()
{
    return GameOver3::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameOver3::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    //Création de la scène GameOver + positionnement

    auto background = Sprite::create("Gameover.jpg");
    background->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y));
    this->addChild(background);


    float rX = visibleSize.width / background->getContentSize().width;
    float rY = visibleSize.height / background->getContentSize().height;

    background->setScaleX(rX);
    background->setScaleY(rY);

    //Création du bouton try again pour permettre au joueur de rejouer + bouton home

    auto tryagain = MenuItemImage::create("try again.png", "try again.png", CC_CALLBACK_1(GameOver3::GotoLevel3, this));
    tryagain->setScale(0.4);
    tryagain->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y));
    auto home = MenuItemImage::create("home.png", "home.png", CC_CALLBACK_1(GameOver3::GoBackToMainMenu, this));

    tryagain->setPosition(Vec2(140, 140));
    home->setPosition(Vec2(450, 270));

    auto menu = Menu::create(tryagain, home, NULL);
    menu->setPosition(Point(0, 0));
    this->addChild(menu);


    return true;
}

void GameOver3::GoBackToMainMenu(Ref* pSender)
{
    auto scene1 = MainMenu::create();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene1));
}

void GameOver3::GotoLevel3(Ref* pSender)
{
    auto sceneLevel3 = Level3::create();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, sceneLevel3));
}

