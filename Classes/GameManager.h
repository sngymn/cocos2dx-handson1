#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

#include "Card.h"
#include "cocos2d.h"

class GameManager : public cocos2d::Layer {

  static constexpr int MAX_CARD_NUMBER = 9;
  static constexpr int MAX_CARD_ROWS = 6;
  static constexpr int MAX_CARD_COLS = 3;

  enum class GameState {
      OpenFirstCard,  // 1枚目のカードを選択
      OpenSecondCard, // 2枚目のカードを選択
      CheckPair,      // カードのマッチングを行う
      ResetGame,      // ゲームをリセットする
  };
    
public:
  static cocos2d::Scene *createScene();

  bool init() override;

  void loadCards();
  void arrangeCards();

  CREATE_FUNC(GameManager);

private:
  // 動的配列を宣言する
  cocos2d::Vector<Card *> cards{};
    
  int selectedFirstCardIndex{ 0 };
  int selectedSecondCardIndex{ 0 };
  int remainingNumberOfPairs{ MAX_CARD_NUMBER };
  GameState gameState{ GameState::OpenFirstCard };
};

#endif // __HELLOWORLD_SCENE_H__
