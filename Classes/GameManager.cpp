#include "GameManager.h"

USING_NS_CC;

Scene* GameManager::createScene()
{
    auto scene = Scene::create();
    auto layer = GameManager::create();
    scene->addChild(layer);

    return scene;
}

bool GameManager::init()
{
    if (!Layer::init()) {
        return false;
    }

    // Touchアクションのイベントリスナー
    auto listener = EventListenerTouchOneByOne::create();

    // タッチ開始時の処理
    listener->onTouchBegan = [this](Touch* touch, Event* event) {
        CCLOG("TouchBegan");

        return true;
    };

    // タッチイベントの登録
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

// カードをロードする関数
void GameManager::loadCards()
{
}

// カードを配置する関数
void GameManager::arrangeCards()
{
}