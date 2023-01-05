
#include "MainMenu.h"
#include "LevelsMenu.h"
#include "AudioEngine.h"
#include "Definition.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
    return MainMenu::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    //Création du background du jeu + son positionnement 

    auto background = Sprite::create("PICO PARK WALLPAPER.jpg");
    background->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y));
    this->addChild(background);

    
    float rX = visibleSize.width / background->getContentSize().width;
    float rY = visibleSize.height / background->getContentSize().height;

    background->setScaleX(rX);
    background->setScaleY(rY);

    
    //Création des boutons PLAY et EXIT

    auto menu_item_1 = MenuItemImage::create("start.png", "start.png", CC_CALLBACK_1(MainMenu::GotToLevelsMenu, this));
    auto menu_item_2 = MenuItemImage::create("exit.png", "exit.png", CC_CALLBACK_1(MainMenu::menuCloseCallback, this));

    menu_item_1->setPosition(Vec2(405, 63));
    menu_item_2->setPosition(Vec2(70, 65));

    auto* menu = Menu::create(menu_item_1, menu_item_2, NULL);
    menu->setPosition(Point(0, 0));
    this->addChild(menu);

    return true;

}

//clic sur PLAY -> LevelsMenu

void MainMenu::GotToLevelsMenu(cocos2d::Ref* pSender)
{
    auto scene = LevelsMenu::create();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}


//clic sur EXIT -> Quitter le jeu

void MainMenu::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////