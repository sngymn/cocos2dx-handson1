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
  arrangeCards();

  // Touchアクションのイベントリスナー
  auto listener = EventListenerTouchOneByOne::create();

  // タッチ開始時の処理
  listener->onTouchBegan = [this](Touch *touch, Event *event) {
    CCLOG("TouchBegan");
      
    auto loc = touch->getLocation();

    switch (gameState) {
            // 1枚目のカードを選択
        case GameState::OpenFirstCard:
            for (int i = 0; i < cards.size(); i++) {
                // カードがクローズしているかつタッチポイントがカード内に存在する場合
                if (!cards.at(i)->isOpen() && cards.at(i)->inside(loc)) {
                    cards.at(i)->open();
                    selectedFirstCardIndex = i;
                    gameState = GameState::OpenSecondCard;
                    break;
                };
            }
            break;
            // 2枚目のカードを選択
        case GameState::OpenSecondCard:
            for (int i = 0; i < cards.size(); i++) {
                // カードがクローズしているかつタッチポイントがカード内に存在する場合
                if (!cards.at(i)->isOpen() && cards.at(i)->inside(loc)) {
                    cards.at(i)->open();
                    selectedSecondCardIndex = i;
                    gameState = GameState::CheckPair;
                    break;
                };
            }
            break;
            // カードのペアチェック
        case GameState::CheckPair:
            if (cards.at(selectedFirstCardIndex)->getCardNumber() == cards.at(selectedSecondCardIndex)->getCardNumber()) {
                
                cards.at(selectedFirstCardIndex)->invisible();
                cards.at(selectedSecondCardIndex)->invisible();
                
                // 残りのペア数を減らす
                remainingNumberOfPairs--;
            }
            // ペアが成立しなかった場合
            else {
                cards.at(selectedFirstCardIndex)->close();
                cards.at(selectedSecondCardIndex)->close();
            }
            
            // 残りのペアが無くなった場合、ゲームをリセットする
            if (remainingNumberOfPairs == 0) {
                gameState = GameState::ResetGame;
            }
            else {
                gameState = GameState::OpenFirstCard;
            }
            
            break;
            // ゲームをリセットする
        case GameState::ResetGame:
            remainingNumberOfPairs = MAX_CARD_NUMBER;
            
            // カードの状態をリセットする
            for (auto& card : cards) {
                card->visible();
                card->close();
            }
            
            // カードの再配置
            arrangeCards();
            
            // 新しいゲームを開始する
            gameState = GameState::OpenFirstCard;
            break;
    }
      
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
void GameManager::arrangeCards() {
  // カードのシャッフル(簡易版)
  std::shuffle(cards.begin(), cards.end(), std::mt19937());
    
  const Size windowSize = Director::getInstance()->getWinSize();
  const Size cardSize = cards.back()->getCardSize(); // カードサイズは全て同じ
  const Size margin((windowSize.width - cardSize.width * MAX_CARD_ROWS) / (MAX_CARD_ROWS + 1),
                    (windowSize.height - cardSize.height * MAX_CARD_COLS) / (MAX_CARD_COLS + 1));

  int row = 0;
  int col = 0;

  for (auto &card : cards) {
    card->setPosition((cardSize.width + margin.width) * row + margin.width,
                      (cardSize.height + margin.height) * col + margin.height);

    row++;
    if (row % MAX_CARD_ROWS == 0) {
      row = 0;
      col++;
    }
  }
}