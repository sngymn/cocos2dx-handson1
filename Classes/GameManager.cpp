#include "GameManager.h"

USING_NS_CC;

Scene *GameManager::createScene() {
  auto scene = Scene::create();
  auto layer = GameManager::create();
  scene->addChild(layer);

  return scene;
}

bool GameManager::init() {
  if (!Layer::init()) {
    return false;
  }

  loadCards();

  // Touchアクションのイベントリスナー
  auto listener = EventListenerTouchOneByOne::create();

  // タッチ開始時の処理
  listener->onTouchBegan = [this](Touch *touch, Event *event) {
    CCLOG("TouchBegan");

    return true;
  };

  // タッチイベントの登録
  Director::getInstance()
      ->getEventDispatcher()
      ->addEventListenerWithSceneGraphPriority(listener, this);

  return true;
}

// カードをロードする関数
void GameManager::loadCards() {
  for (int i = 1; i <= MAX_CARD_NUMBER; i++) {

    // ハート柄のカードをロードする
    auto heart =
        Card::create(i, StringUtils::format("h%d.png", i), "back_red.png");
    heart->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    addChild(heart);

    // 動的配列へ追加
    cards.pushBack(heart);

    // ダイヤ柄のカードをロードする
    auto diamond =
        Card::create(i, StringUtils::format("d%d.png", i), "back_red.png");
    diamond->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    addChild(diamond);

    // 動的配列へ追加
    cards.pushBack(diamond);
  }
}

// カードを配置する関数
void GameManager::arrangeCards() {}